#ifndef NMTOOLS_ARRAY_VIEW_UFUNC_REDUCE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNC_REDUCE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/ref.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/slice.hpp"
#include "nmtools/array/view/flatten.hpp"
#include "nmtools/array/view/broadcast_arrays.hpp"
#include "nmtools/array/index/outer.hpp"
#include "nmtools/array/index/remove_dims.hpp"
#include "nmtools/array/index/where.hpp"
#include "nmtools/array/index/sum.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/dtypes.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/eval.hpp"
#include "nmtools/constants.hpp"

#include "nmtools/array/view/ufunc/detail.hpp"

namespace nmtools::view::detail
{
    template <typename indices_t, typename array_type, typename axis_type, typename keepdims_type>
    constexpr auto make_reduction_slices(const indices_t& indices_, const array_type& array, const axis_type& axis, keepdims_type keepdims)
    {
        // for now, assume axis is int and array is fixed_dim
        // TODO: support reduce on dynamic dim array
        using array_t = meta::remove_cvref_pointer_t<array_type>;
        using axis_t  = meta::remove_cvref_pointer_t<axis_type>;
        constexpr auto DIM = meta::fixed_dim_v<array_t>;
        [[maybe_unused]] const auto dim = detail::dim(array);
        // type for slicing is DIMx2 where 2 represent start and stop
        constexpr auto slices_vtype = [=](){
            using slice_type = nmtools_array<size_t,2>;
            if constexpr (meta::is_fixed_dim_ndarray_v<array_t>) {
                using slices_type = nmtools_array<slice_type,DIM>;
                return meta::as_value_v<slices_type>;
            } else {
                using slices_type = nmtools_list<slice_type>;
                return meta::as_value_v<slices_type>;
            }
        }();
        using slices_type = meta::type_t<decltype(slices_vtype)>;
        auto slices = slices_type {};
        auto shape_ = detail::shape(array);
        if constexpr (meta::is_resizeable_v<slices_type>) {
            slices.resize(dim);
        }

        // helper lambda to check if axis i is in the specified axis for reduction
        auto in_axis = [&](auto i){
            if constexpr (meta::is_index_v<axis_t> && meta::is_pointer_v<axis_type>) {
                return i==*axis;
            } else if constexpr (meta::is_index_v<axis_t>) {
                using common_t = meta::promote_index_t<axis_t,decltype(i)>;
                return (common_t)i==(common_t)axis;
            } else {
                auto f_predicate = [i](auto axis){
                    using common_t = meta::promote_index_t<decltype(i),decltype(axis)>;
                    return (common_t)i==(common_t)axis;
                };
                // axis is index array (reducing on multiple axes),
                // axis may be pointer, but can't provide convenience function
                // since may decay bounded array to pointer
                if constexpr (meta::is_pointer_v<axis_type>) {
                    auto found = index::where(f_predicate, *axis);
                    return static_cast<bool>(len(found));
                } else {
                    auto found = index::where(f_predicate, axis);
                    return static_cast<bool>(len(found));
                }
            }
        };

        // use the same type as axis_t for loop index
        constexpr auto idx_vtype = [](){
            if constexpr (meta::is_constant_index_array_v<axis_t>) {
                // shortcut for now, just use int
                return meta::as_value_v<int>;
            } else if constexpr (meta::is_index_array_v<axis_t>) {
                using type = meta::get_element_type_t<axis_t>;
                return meta::as_value_v<type>;
            } else if constexpr (meta::is_integer_v<axis_t>) {
                return meta::as_value_v<axis_t>;
            } else {
                return meta::as_value_v<size_t>;
            }
        }();
        using index_t = meta::get_index_type_t<array_t>;
        using idx_t   = meta::type_t<meta::promote_index<index_t,meta::type_t<decltype(idx_vtype)>>>;

        // indices and the referenced array may have different dim,
        // this variable track index for indices_
        auto ii = idx_t{0};
        if constexpr (meta::is_fixed_dim_ndarray_v<array_t>) {
            // here, len(slices) already matched the dimension of source array
            meta::template_for<DIM>([&](auto index){
                constexpr auto i = decltype(index)::value;
                // take all elements at given axis
                if (in_axis(i)) {
                    // note that shape_ maybe constant index array
                    at(slices,i) = {static_cast<idx_t>(0),at(shape_,meta::ct_v<i>)};
                    // if keepdims is true, also increment indices index
                    if (keepdims)
                        ii++;
                }
                // use indices otherwise, just slice with index:index+1
                else {
                    auto s = at(indices_,ii++);
                    at(slices,i) = {s,s+1};
                }
            });
        } else {
            for (size_t i=0; i<dim; i++) {
                // take all elements at given axis
                if (in_axis(i)) {
                    // note that shape_ maybe constant index array
                    at(slices,i) = {static_cast<idx_t>(0),at(shape_,i)};
                    // if keepdims is true, also increment indices index
                    if (keepdims)
                        ii++;
                }
                // use indices otherwise, just slice with index:index+1
                else {
                    auto s = at(indices_,ii++);
                    at(slices,i) = {s,s+1};
                }
            }
        }
        return slices;
    } // make_reduction_slices
}

namespace nmtools::view
{
    namespace error
    {
        struct INVALID_NUM_REDUCE : meta::detail::fail_t {};
    } // namespace error
    
    /**
     * @brief Type constructor to reduce single array given op.
     * 
     * @tparam op_t 
     */
    template <typename op_t>
    struct reducer_t
    {
        using op_type = op_t;

        op_type op;

        /**
         * @brief Perform reduction on single 1D array.
         * 
         * @tparam result_t 
         * @tparam array_t 
         * @param array 
         * @return constexpr auto 
         */
        template <typename result_t, typename array_t>
        constexpr auto operator()(const array_t& array) const
        {
            using index_t = size_t;
            auto initial = static_cast<result_t>(at(array,0));
            auto size = len(array);
            for (index_t i=1; i<(index_t)size; i++)
                initial = op(initial,at(array,i));
            return initial;
        } // operator()

        /**
         * @brief perform reduction on single 1D array with given initial value
         * 
         * @tparam result_t 
         * @tparam array_t 
         * @tparam initial_t 
         * @param array 
         * @param init 
         * @return constexpr auto 
         */
        template <typename result_t, typename array_t, typename initial_t>
        constexpr auto operator()(const array_t& array, initial_t init) const
        {
            auto initial = static_cast<result_t>(init);
            auto size = len(array);
            for (size_t i=0; i<size; i++)
                initial = op(initial,at(array,i));
            return initial;
        } // operator()
    }; // reducer_t

    /**
     * @brief Type constructor for reduction ufuncs, given op, axis and initial value.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     */
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct reduce_t
    {
        // if given array is a view, just use value instead of reference
        using operands_type = resolve_array_type_t<array_t>;
        using array_type    = operands_type;
        using axis_type     = resolve_array_type_t<axis_t>;
        using op_type       = op_t;
        using initial_type  = initial_t;
        using reducer_type  = reducer_t<op_t>;
        using element_type  = meta::get_element_type_t<array_t>;
        using keepdims_type = keepdims_t;

        using result_type = meta::type_t<detail::get_result_type<element_type,op_type>>;

        op_type       op;
        array_type    array;
        axis_type     axis;
        initial_type  initial;
        reducer_type  reducer;
        keepdims_type keepdims;

        constexpr reduce_t(op_type op, const array_t& array, const axis_t& axis, initial_type initial, keepdims_type keepdims)
            : op(op), array(initialize<array_type>(array))
            , axis(initialize<axis_type>(axis))
            , initial(initial)
            , reducer{op} // TODO: recurse to scalar reduce ufunc instead of using reducer
            , keepdims(keepdims) {}

        constexpr auto shape() const
        {
            auto shape_ = detail::shape(array);
            // NOTE: can't provide convenience function
            // without causing bounded array to decay to pointer
            if constexpr (meta::is_pointer_v<axis_type>) {
                return index::remove_dims(shape_,*axis,keepdims);
            } else {
                return index::remove_dims(shape_,axis,keepdims);
            }
        } // shape

        constexpr auto dim() const
        {
            // assume arrays is already broadcasted together
            return len(shape());
        } // dim

        /**
         * @brief compute element at given indices, effectively perform reduction.
         * 
         * Computing element (at given indices) only available if not reducing the whole array
         * (axis_t is not None), because the view is not ndarray but num.
         * Internally this operator slices the referenced array then flatten then actually
         * perform reduction (using reducer_t).
         * 
         * @tparam size_types 
         * @param indices 
         * @return constexpr auto 
         */
        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // The slice can be illustrated as follows:
            // assume array is (2,3,2) shape, and we are reducing on axis=1
            // hence the resulting shape should be (2,2)
            // at index (0,0), the slice should be (0,:,0)
            // the following axis logic is basically doing that.
            // TODO: consider to call eval on slices instead of putting all the code here

            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
            
            auto indices_ = pack_indices(indices...);

            // apply slice only works with fixed dim ndarray for now
            // TODO: support dynamic dim ndarray
            auto sliced = [&](){
                auto slices = detail::make_reduction_slices(indices_,array,axis,keepdims);
                // this slice operates directly with the underlying array
                // which may be pointer
                if constexpr (meta::is_pointer_v<array_type>) {
                    return apply_slice(*array,slices);
                } else {
                    return apply_slice(array, slices);
                }
            }();
            auto flattened = flatten(sliced);
            // TODO: instead of reduce using reducer_t, return reduce using None axis
            // doing so may simplify evaluation
            return [&](){
                if constexpr (is_none_v<initial_type>)
                    return reducer.template operator()<result_type>(flattened);
                else return reducer.template operator()<result_type>(flattened,initial);
            }();
        } // operator()

        // NOTE: the following is to allow reducing to numeric type
        static constexpr auto num_vtype = [](){
            using view_t = view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t >;
            if constexpr (meta::is_num_v<view_t>) {
                return meta::as_value_v<result_type>;
            } else {
                return meta::as_value_v<error::INVALID_NUM_REDUCE>;
            }
        }();
        using num_type = meta::type_t<decltype(num_vtype)>;

        constexpr operator num_type() const
        {
            if constexpr (meta::is_fail_v<num_type>) {
                return num_type{};
            } else {
                // reduce the whole array
                // must check if array is pointer or not since
                // flatten (and view in general) doesn't accept pointer
                auto flattened = [&](){
                    if constexpr (meta::is_pointer_v<array_type>) {
                        return flatten(*array);
                    } else {
                        return flatten(array);
                    }
                }();
                return [&](){
                    if constexpr (is_none_v<initial_type>)
                        return reducer.template operator()<result_type>(flattened);
                    else return reducer.template operator()<result_type>(flattened,initial);
                }();
            }
        } // operator result_type()
    }; // reduce_t

    /**
     * @brief Specialization of reduce_t for None axis.
     *
     * Following numpy, when axis is None, perform reduction on flattened array.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     */
    template <typename op_t, typename array_t, typename initial_t, typename keepdims_t>
    struct reduce_t<op_t,array_t,none_t,initial_t,keepdims_t>
    {
        using array_type    = resolve_array_type_t<array_t>;
        // use reference for now since raw array decays to pointer
        using axis_type     = none_t;
        using op_type       = op_t;
        using initial_type  = initial_t;
        using reducer_type  = reducer_t<op_t>;
        using element_type  = meta::get_element_type_t<array_t>;
        using keepdims_type = keepdims_t;

        using result_type = meta::type_t<detail::get_result_type<element_type,op_type>>;

        op_type       op;
        array_type    array;
        axis_type     axis;
        initial_type  initial;
        reducer_type  reducer;
        keepdims_type keepdims;

        constexpr reduce_t(op_type op, const array_t& array, axis_type axis, initial_type initial, keepdims_type keepdims)
            : op(op), array(initialize<array_type>(array)), axis(axis), initial(initial), reducer{op}, keepdims(keepdims) {}
        
        constexpr auto shape() const
        {
            // None axis with keepdims True:
            // just get the original shape and then fill with one
            [[maybe_unused]]
            auto f_shape = [&](){
                auto shape_ = detail::shape(array);
                using m_shape_t = decltype(shape_);
                if constexpr (meta::is_constant_index_array_v<m_shape_t>) {
                    // special case: shape is compile-time value,
                    // can't access and modify at runtime
                    constexpr auto N   = meta::len_v<m_shape_t>;
                    using val_t = meta::ct<1>;
                    constexpr auto val = val_t{};
                    auto res = meta::template_reduce<N-1>([&](auto init, auto /*index*/){
                        return detail::tuple_cat(init,meta::make_tuple_type_t<val_t>{val});
                    }, /*init=*/meta::make_tuple_type_t<val_t>{val});
                    return res;
                } else {
                    for (size_t i=0; i<len(shape_); i++)
                        at(shape_,i) = 1;
                    return shape_;
                }
            };
            if constexpr (meta::is_integral_constant_v<keepdims_t>) {
                if constexpr (static_cast<bool>(keepdims_t::value))
                    return f_shape();
                else return None;
            }
            else // if (is_none_v<keepdims_t>)
                return None;
        } // shape

        constexpr auto dim() const
        {
            if constexpr (meta::is_integral_constant_v<keepdims_t>) {
                if constexpr (!static_cast<bool>(keepdims_t::value))
                    return 0;
                else return detail::dim(array);
            }
            else return 0;
        } // dim

        constexpr operator result_type() const
        {
            // reduce the whole array
            // must check if array is pointer or not since
            // flatten (and view in general) doesn't accept pointer
            auto flattened = [&](){
                if constexpr (meta::is_pointer_v<array_type>) {
                    return flatten(*array);
                } else {
                    return flatten(array);
                }
            }();
            return [&](){
                if constexpr (is_none_v<initial_type>)
                    return reducer.template operator()<result_type>(flattened);
                else return reducer.template operator()<result_type>(flattened,initial);
            }(); 
        } // operator result_type()

        // TODO: remove
        template <typename...size_types>
        constexpr auto operator()(size_types.../*indices*/) const
        {
            // reduce the whole array
            auto flattened = [&](){
                if constexpr (meta::is_pointer_v<array_type>) {
                    return flatten(*array);
                } else {
                    return flatten(array);
                }
            }();
            return [&](){
                if constexpr (is_none_v<initial_type>)
                    return reducer.template operator()<result_type>(flattened);
                else return reducer.template operator()<result_type>(flattened,initial);
            }(); 
        } // operator()
    }; // reduce_t
} // namespace nmtools::view


namespace nmtools::meta
{
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct is_num< 
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t >
    >
    {
        static constexpr auto value = [](){
            // check if keepdims type makes this view reduced to num
            constexpr auto keepdims_ = [](){
                if constexpr (is_none_v<keepdims_t>) {
                    return is_none_v<axis_t>;
                } else if constexpr (is_integral_constant_v<keepdims_t>) {
                    return is_none_v<axis_t> && !static_cast<bool>(keepdims_t::value);
                } else /* constexpr (meta::is_boolean_v<axis_t>) */ {
                    // TODO: should not be encountered
                    // runtime boolean value should not be allowed
                    return false;
                }
            }();
            // check if axis makes it reduce to num
            constexpr auto value_ = [=](){
                // note that repeated/duplicate axis are NOT allowed for reduce ufunc,
                // and such condition is handled by runtime function,
                // here we assume such condition is already handled
                // (either by exception, maybe, or assert) by the corresponding function
                if constexpr (is_fixed_dim_ndarray_v<array_t> 
                    && (is_fixed_index_array_v<axis_t> || is_integral_v<axis_t>)
                    && is_integral_constant_v<keepdims_t>
                ) {
                    auto array_dim = fixed_dim_v<array_t>;
                    // dim to reduce, integer axis means reduce 1 dimension
                    auto axis_dim  = [](){
                        if constexpr (is_fixed_index_array_v<axis_t>) {
                            return len_v<axis_t>;
                        } else {
                            return 1ul;
                        }
                    }();
                    return (array_dim == axis_dim) && !keepdims_t::value;
                } else {
                    return keepdims_;
                }
            }();
            return (is_ndarray_v<array_t> && value_);
        }();
    };

    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct is_ndarray< 
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t >
    >
    {
        using view_t = view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t >;
        static constexpr auto value = is_ndarray_v<array_t> && !is_num_v<view_t>;
    };

    /**
     * @brief Compile-time shape inference for reduce ufuncs.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     */
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct fixed_ndarray_shape<
        view::reduce_t< op_t, array_t, axis_t, initial_t, keepdims_t >
    >
    {
        static inline constexpr auto value = [](){
            // the shape of the reduction can only be known at compile time
            // if axis and keepdims is integral constant
            if constexpr (
                    is_fixed_size_ndarray_v<array_t>
                && (is_integral_constant_v<axis_t> || is_none_v<axis_t>)
                && (is_integral_constant_v<keepdims_t> || is_none_v<keepdims_t>)
            ) {
                constexpr auto keepdims = [](){
                    if constexpr (is_integral_constant_v<keepdims_t>) {
                        return keepdims_t::value;
                     }else /* if constexpr (is_none_v) */ {
                        return false;
                     }
                }();
                if constexpr (!keepdims && is_none_v<axis_t>) {
                    // reduce on all axis and not keep dimensions,
                    // this is not considered as fixed shape ndarray, but should be num type instead
                    return detail::Fail;
                } else {
                    constexpr auto shape  = fixed_ndarray_shape_v<array_t>;
                    constexpr auto axes   = [&](){
                        if constexpr (is_none_v<axis_t>) {
                            // reduce on all axis and keepdims.
                            // use std array for now
                            constexpr auto dim = ::nmtools::len(shape);
                            using axis_type = meta::make_array_type_t<size_t,dim>;
                            auto axes = axis_type{};
                            for (size_t i=0; i<dim; i++)
                                at(axes,i) = i; // on all axis
                            return axes;
                        } else {
                            return axis_t::value;
                        }
                    }();
                    constexpr auto shape_ = index::remove_dims(shape, axes, keepdims);
                    constexpr auto dim_   = ::nmtools::len(shape_);
                    using result_t = meta::make_array_type_t<size_t,dim_>;
                    auto result = result_t{};
                    for (size_t i=0; i<dim_; i++)
                        at(result,i) = at(shape_,i);
                    return result;
                }
            } else {
                return detail::Fail;
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
    }; // fixed_ndarray_shape

    /**
     * @brief Infer the dimension of reduce ufunc view at compile time.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     */
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct fixed_dim< 
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t >
    >
    {
        using view_t = view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t >;
        static constexpr auto value = [](){
            if constexpr (is_num_v<view_t>) {
                // TODO: use specific errort type
                return detail::Fail;
            } else if constexpr (
                   is_fixed_dim_ndarray_v<array_t>
                && (is_integral_constant_v<keepdims_t> || is_none_v<keepdims_t>))
            {
                constexpr auto keepdims = [](){
                    if constexpr (is_none_v<keepdims_t>) {
                        return meta::false_type{};
                    } else {
                        return keepdims_t {};
                    }
                }();
                if constexpr (static_cast<bool>(keepdims)) {
                    return fixed_dim_v<array_t>;
                } else if constexpr (is_index_v<axis_t>) {
                    return fixed_dim_v<array_t> - 1;
                } else if constexpr (is_fixed_index_array_v<axis_t>) {
                    return fixed_dim_v<array_t> - fixed_index_array_size_v<axis_t>;
                } else {
                    return detail::Fail;
                }
            } else {
                return detail::Fail;
            }
        }();
        // TODO: consider to use fail type to indicate fail instead of void
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
        using type = value_type;
    }; // fixed_dim

    /**
     * @brief 
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     */
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct hybrid_ndarray_max_size<
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t >
    >
    {
        using view_t = view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t >;
        static inline constexpr auto value = [](){
            if constexpr (is_num_v<view_t>) {
                // TODO: use specific error type
                return detail::Fail;
            } else if constexpr (is_hybrid_ndarray_v<array_t>) {
                return hybrid_ndarray_max_size_v<array_t>;
            } else if constexpr (is_fixed_size_ndarray_v<array_t>) {
                constexpr auto shape = fixed_ndarray_shape_v<array_t>;
                return index::product(shape);
            } else {
                // TODO: use specific error type
                return detail::Fail;
            }
        }();
    };

    // provide specialization for reducer
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct get_element_type<
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t >
    >
    {
        using type = typename view::reduce_t<op_t, array_t, axis_t, initial_t, keepdims_t>::result_type;
    };

    /**
     * @brief Specialization of eval return type resolver for reduce ufunc.
     *
     * Need to specialize eval resolver because reducer may produce num, ndarray, or either.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     */
    // template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    // struct resolve_optype<
    //     void, array::eval_t, view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t>, none_t
    // >
    // {
    //     static constexpr auto vtype = [](){
    //         using view_t = view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t>;
    //         if constexpr (is_fixed_size_ndarray_v<view_t>) {
    //             // NOTE: resolve_unary_array_type defined in eval.hpp
    //             // only call on fixed_size_ndarray because axis_t may be runtime value otherwise
    //             return resolve_unary_array_type(as_value_v<array_t>, as_value_v<view_t>);
    //         } else if constexpr (is_num_v<view_t>) {
    //             using type = get_element_type_t<view_t>;
    //             return as_value_v<type>;
    //         } else /* if constexpr (is_ndarray_v<view_t>) */ {
    //             using element_t = get_element_type_t<view_t>;
    //             using type = make_dynamic_ndarray_t<element_t>;
    //             return as_value_v<type>;
    //         }
    //     }();
    //     using type = type_t<decltype(vtype)>;
    // }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_UFUNC_REDUCE_HPP