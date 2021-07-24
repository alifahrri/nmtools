#ifndef NMTOOLS_ARRAY_VIEW_UFUNC_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNC_HPP

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
#include "nmtools/array/shape.hpp"
#include "nmtools/array/dtypes.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/eval.hpp"
#include "nmtools/constants.hpp"

#include <tuple>
#include <variant>

// clang doesn't support constexpr math while gcc does
#if defined(__GNUC__) && !defined(__clang__) && !defined(NMTOOLS_UFUNC_CONSTEXPR)
#define NMTOOLS_UFUNC_CONSTEXPR constexpr
#else
#define NMTOOLS_UFUNC_CONSTEXPR
#endif

namespace nmtools::view
{
    namespace detail
    {
        /**
         * @brief helper metafunction to deduce the operand types for ufunc,
         * dont take reference for 'view' objects/
         * 
         * @tparam always_void 
         * @tparam arrays_t 
         */
        template <typename always_void,typename...arrays_t>
        struct get_operands_type
        {
            using type = std::tuple<const arrays_t&...>;
        }; // get_operands_type

        template <typename...arrays_t>
        struct get_operands_type<
            std::enable_if_t<(meta::is_view_v<arrays_t> || ...)>
            , arrays_t...
        >
        {
            // TODO: note that array may be mixed with view and non-view,
            // only copy those view while keep reference for non-view arrays
            using type = std::tuple<arrays_t...>;
        }; // get_operands_type

        template <typename...arrays_t>
        using get_operands_type_t = meta::type_t<get_operands_type<void,arrays_t...>>;

        /**
         * @brief Helper trait to check if type T has member type `result_type`
         * 
         * @tparam T type to check
         * @tparam typename 
         */
        template <typename T, typename=void>
        struct has_result_type : std::false_type {};

        template <typename T>
        struct has_result_type<T,std::void_t<typename T::result_type>> : std::true_type {};

        template <typename T>
        constexpr inline auto has_result_type_v = has_result_type<T>::value;

        /**
         * @brief Helper metafunction to deduce the return type from op an args for ufuncs.
         * 
         * @tparam always_void 
         * @tparam op_t 
         * @tparam args_t 
         */
        template <typename always_void, typename op_t, typename...args_t>
        struct get_ufunc_result_type
        {
            using type = decltype(std::declval<op_t>()(std::declval<args_t>()...));
        }; // get_ufunc_result_type

        template <typename op_t, typename...args_t>
        struct get_ufunc_result_type<
            std::void_t<typename op_t::result_type>,
            op_t, args_t...
        >
        {
            using type = typename op_t::result_type;
        }; // get_ufunc_result_type

        template <typename op_t, typename...args_t>
        using get_ufunc_result_type_t = typename get_ufunc_result_type<void,op_t,args_t...>::type;

        /**
         * @brief Helper metafunction to deduce the type of reduce operations.
         * 
         * @tparam reducer_t 
         * @tparam element_t 
         * @tparam typename 
         */
        template <typename reducer_t, typename element_t, typename=void>
        struct get_reducer_result_type
        {
            using type = element_t;
        }; // get_reducer_result_type

        template <typename reducer_t, typename element_t>
        struct get_reducer_result_type< reducer_t, element_t,
            std::void_t<typename reducer_t::result_type>
        >
        {
            using type = typename reducer_t::result_type;
        }; // get_reducer_result_type

        template <typename reducer_t, typename element_t>
        using get_reducer_result_type_t = typename get_reducer_result_type<reducer_t,element_t>::type;

        /**
         * @brief helper type that wrapps type `T`, avoid constructing the actual type.
         * 
         * @tparam T 
         */
        template <typename T>
        struct type_wrapper
        {
            using type = T;
        }; // type_wrapper
        
        /**
         * @brief Get the result type of given op_type
         *
         * Prefer op_type::result_type when available, use element_t otherwise.
         * 
         * @tparam element_t 
         * @tparam op_type 
         */
        template <typename element_t, typename op_type>
        struct get_result_type
        {
            // for op type with explicit result_type member type, prefer that type
            // other wise use referenced array's element type
            static constexpr auto vtype = [](){
                if constexpr (detail::has_result_type_v<op_type>) {
                    using result_t = typename op_type::result_type;
                    return meta::as_value<result_t>{};
                }
                else return meta::as_value<element_t>{};
            }();
            using type = meta::type_t<meta::remove_cvref_t<decltype(vtype)>>;
        };
    } // namespace detail

    /**
     * @brief A type constructor for actual ufuncs.
     *
     * The number of arrays passed must be matched with op's arity.
     * 
     * @tparam op_t 
     * @tparam arrays_t 
     */
    template <typename op_t, typename...arrays_t>
    struct ufunc_t
    {
        using operands_type = detail::get_operands_type_t<arrays_t...>;
        using array_type = operands_type;
        using op_type = op_t;
        using result_type = detail::get_ufunc_result_type_t<op_t,meta::get_element_type_t<arrays_t>...>;

        op_type op;
        operands_type operands;

        constexpr ufunc_t(op_type op, operands_type operands)
            : op(op), operands(operands) {}
        
        constexpr auto shape() const
        {
            // assume arrays is already broadcasted together
            return ::nmtools::shape(std::get<0>(operands));
        } // shape

        constexpr auto dim() const
        {
            // assume arrays is already broadcasted together
            return ::nmtools::dim(std::get<0>(operands));
        } // dim

        template <typename indices_t, size_t...Is>
        static constexpr auto apply_at(op_type op, const operands_type& operands, const indices_t& indices, std::index_sequence<Is...>)
        {
            using ::nmtools::apply_at;
            return op(apply_at(std::get<Is>(operands),indices)...);
        } // apply_at

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
            using ::nmtools::detail::make_array;
            using common_t = std::common_type_t<size_types...>;
            auto indices_ = [&](){
                // handle non-packed indices
                if constexpr (std::is_integral_v<common_t>)
                    return make_array<std::array>(indices...);
                // handle packed indices, number of indices must be 1
                else {
                    static_assert (sizeof...(indices)==1
                        , "unsupported index for broadcast_to view"
                    );
                    return std::get<0>(std::tuple{indices...});
                }
            }();
            constexpr auto N = sizeof...(arrays_t);
            return apply_at(op, operands, indices_, std::make_index_sequence<N>{});
        } // operator()
    }; // ufunc_t

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
            auto initial = static_cast<result_t>(at(array,0));
            auto size = len(array);
            for (size_t i=1; i<size; i++)
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
        using operands_type = std::conditional_t<is_view_v<array_t>,array_t,const array_t&>;
        using array_type    = operands_type;
        // use reference for now since raw array decays to pointer
        using axis_type     = const axis_t&;
        using op_type       = op_t;
        using initial_type  = initial_t;
        using reducer_type  = reducer_t<op_t>;
        using element_type  = meta::get_element_type_t<array_t>;
        using keepdims_type = keepdims_t;

        using result_type = meta::type_t<detail::get_result_type<element_type,op_type>>;

        array_type array;
        axis_type axis;
        op_type op;
        initial_type initial;
        reducer_type reducer;
        keepdims_type keepdims;

        constexpr reduce_t(op_type op, array_type array, axis_type axis, initial_type initial, keepdims_type keepdims)
            : op(op), array(array), axis(axis), initial(initial), reducer{op}, keepdims(keepdims) {}
        
        constexpr auto shape() const
        {
            return index::remove_dims(::nmtools::shape(array), axis, keepdims);
        } // shape

        constexpr auto dim() const
        {
            // assume arrays is already broadcasted together
            return len(shape());
        } // dim

        /**
         * @brief compute element at given indices, effectively perform reduction.
         * 
         * Computing such element only available if not reducing the whole array
         * (axis_t is not None).
         * 
         * @tparam size_types 
         * @param indices 
         * @return constexpr auto 
         */
        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
            using ::nmtools::detail::make_array;
            using common_t = std::common_type_t<size_types...>;
            auto indices_ = [&](){
                // handle non-packed indices
                if constexpr (std::is_integral_v<common_t>)
                    return make_array<std::array>(indices...);
                // handle packed indices, number of indices must be 1
                else {
                    static_assert (sizeof...(indices)==1
                        , "unsupported index for broadcast_to view"
                    );
                    return std::get<0>(std::tuple{indices...});
                }
            }();
            // for now, assume axis is int and array is fixed_dim
            constexpr auto DIM = meta::fixed_dim_v<array_t>;
            // type for slicing is DIMx2 where 2 represent start and stop
            using slices_type = std::array<std::array<size_t,2>,DIM>;
            auto slices = slices_type {};
            auto shape_ = ::nmtools::shape(array);
            // indices and the referenced array may have different dim,
            // this variable track index for indices_
            auto ii = size_t{0};
            // helper lambda to check if axis i is in the specified axis for reduction
            auto in_axis = [&](auto i){
                if constexpr (std::is_integral_v<axis_t>)
                    return i==axis;
                else {
                    auto f_predicate = [i](auto axis){
                        return i==axis;
                    };
                    auto found = index::where(f_predicate, axis);
                    return static_cast<bool>(len(found));
                }
            };
            // here, len(slices) already matched the dimension of source array
            for (size_t i=0; i<len(slices); i++) {
                // take all elements at given axis
                if (in_axis(i)) {
                    at(slices,i) = {0,at(shape_,i)};
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
            // apply slice only works with fixed dim ndarray for now
            // TODO: support dynamic dim ndarray
            auto sliced = apply_slice(array, slices);
            auto flattened = flatten(sliced);
            return [&](){
                if constexpr (is_none_v<initial_type>)
                    return reducer.template operator()<result_type>(flattened);
                else return reducer.template operator()<result_type>(flattened,initial);
            }();
        } // operator()
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
        // if given array is a view, just use value instead of reference
        using operands_type = std::conditional_t<is_view_v<array_t>,array_t,const array_t&>;
        using array_type    = operands_type;
        // use reference for now since raw array decays to pointer
        using axis_type     = const none_t&;
        using op_type       = op_t;
        using initial_type  = initial_t;
        using reducer_type  = reducer_t<op_t>;
        using element_type  = meta::get_element_type_t<array_t>;
        using keepdims_type = keepdims_t;

        using result_type = meta::type_t<detail::get_result_type<element_type,op_type>>;

        array_type array;
        axis_type axis;
        op_type op;
        initial_type initial;
        reducer_type reducer;
        keepdims_type keepdims;

        constexpr reduce_t(op_type op, array_type array, axis_type axis, initial_type initial, keepdims_type keepdims)
            : op(op), array(array), axis(axis), initial(initial), reducer{op}, keepdims(keepdims) {}
        
        constexpr auto shape() const
        {
            // just get the original shape and then fill with one
            auto f_shape = [&](){
                auto shape_ = nmtools::shape(array);
                for (size_t i=0; i<len(shape_); i++)
                    at(shape_,i) = 1;
                return shape_;
            };
            if constexpr (meta::is_integral_constant_v<keepdims_t>) {
                if constexpr (static_cast<bool>(keepdims_t::value))
                    return f_shape();
                else return None;
            }
            // use variant since it can be none or the shape
            // else if constexpr (meta::is_boolean_v<keepdims_t>) {
            //     using shape_t  = decltype(nmtools::shape(array));
            //     // use none_t as first alternative, since it is must be defautl construtctibel
            //     using return_t = std::variant<none_t,shape_t>;
            //     return (keepdims ? return_t{f_shape()} : return_t{None});
            // }
            else // if (is_none_v<keepdims_t>)
                return None;
        } // shape

        constexpr auto dim() const
        {
            if constexpr (meta::is_integral_constant_v<keepdims_t>) {
                if constexpr (!static_cast<bool>(keepdims_t::value))
                    return 0;
                else return nmtools::dim(array);
            }
            else return 0;
        } // dim

        operator result_type() const
        {
            // reduce the whole array
            auto flattened = flatten(array);
            return [&](){
                if constexpr (is_none_v<initial_type>)
                    return reducer.template operator()<result_type>(flattened);
                else return reducer.template operator()<result_type>(flattened,initial);
            }(); 
        } // operator result_type()

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // reduce the whole array
            auto flattened = flatten(array);
            return [&](){
                if constexpr (is_none_v<initial_type>)
                    return reducer.template operator()<result_type>(flattened);
                else return reducer.template operator()<result_type>(flattened,initial);
            }(); 
        } // operator()
    }; // reduce_t

    /**
     * @brief Type constructor for accumulate ufuncs.
     *
     * Accumulate the result on given axis.
     * 
     * @tparam op_t operator type
     * @tparam array_t array type
     * @tparam axis_t axis type
     */
    template <typename op_t, typename array_t, typename axis_t>
    struct accumulate_t
    {
        // if given array is a view, just use value instead of reference
        using operands_type = std::conditional_t<is_view_v<array_t>,array_t,const array_t&>;
        using array_type    = operands_type;
        using axis_type     = axis_t;
        using op_type       = op_t;
        using reducer_type  = reducer_t<op_t>;
        using element_type  = meta::get_element_type_t<array_t>;

        using result_type = meta::type_t<detail::get_result_type<element_type,op_type>>;

        array_type array;
        axis_type axis;
        op_type op;
        reducer_type reducer;

        constexpr accumulate_t(op_type op, array_type array, axis_type axis)
            : op(op), array(array), axis(axis), reducer{op} {}

        constexpr auto shape() const
        {
            return ::nmtools::shape(array);
        } // shape

        constexpr auto dim() const
        {
            return ::nmtools::dim(array);
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
            using ::nmtools::detail::make_array;
            using common_t = std::common_type_t<size_types...>;
            auto indices_ = [&](){
                // handle non-packed indices
                if constexpr (std::is_integral_v<common_t>)
                    return make_array<std::array>(indices...);
                // handle packed indices, number of indices must be 1
                else {
                    static_assert (sizeof...(indices)==1
                        , "unsupported index for broadcast_to view"
                    );
                    return std::get<0>(std::tuple{indices...});
                }
            }();
            // for now, assume axis is int and array is fixed_dim
            constexpr auto DIM = meta::fixed_dim_v<array_t>;
            // type for slicing is DIMx2 where 2 represent start and stop
            using slices_type = std::array<std::array<size_t,2>,DIM>;
            auto slices = slices_type {};
            // here, len(slices) already matched the dimension of source array
            auto dim = len(slices);
            for (size_t i=0; i<dim; i++) {
                // index at axis i
                auto s = at(indices_,i);
                auto start = i==axis ? 0 : s;
                auto stop  = s + 1;
                at(slices,i) = {start,stop};
            }
            // apply slice only works with fixed dim ndarray for now
            // TODO: support dynamic dim ndarray
            auto sliced = apply_slice(array, slices);
            auto flattened = flatten(sliced);
            return reducer.template operator()<result_type>(flattened);
        } // operator()
    }; // accumulate_t

    /**
     * @brief Type constructor for outer ufuncs.
     * 
     * Apply op to pairs of element of lhs and rhs.
     *
     * @tparam op_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename op_t, typename lhs_t, typename rhs_t>
    struct outer_t
    {
        using operands_type = detail::get_operands_type_t<lhs_t,rhs_t>;
        using array_type = operands_type;
        using op_type = op_t;
        using lhs_element_type = meta::get_element_type_t<lhs_t>;
        using rhs_element_type = meta::get_element_type_t<rhs_t>;
        using result_type = detail::get_ufunc_result_type_t<op_t,lhs_element_type,rhs_element_type>;

        op_type op;
        operands_type operands;

        constexpr outer_t(op_type op, operands_type operands)
            : op(op), operands(operands) {}
        
        constexpr auto shape() const
        {
            auto ashape = ::nmtools::shape(std::get<0>(operands));
            auto bshape = ::nmtools::shape(std::get<1>(operands));
            return index::shape_outer(ashape,bshape);
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
            using ::nmtools::detail::make_array;
            using common_t = std::common_type_t<size_types...>;
            auto indices_ = [&](){
                // handle non-packed indices
                if constexpr (std::is_integral_v<common_t>)
                    return make_array<std::array>(indices...);
                // handle packed indices, number of indices must be 1
                else {
                    static_assert (sizeof...(indices)==1
                        , "unsupported index for broadcast_to view"
                    );
                    return std::get<0>(std::tuple{indices...});
                }
            }();
            const auto& a = std::get<0>(operands);
            const auto& b = std::get<1>(operands);
            auto ashape = ::nmtools::shape(a);
            auto bshape = ::nmtools::shape(b);
            auto [aidx, bidx] = index::outer(indices_,ashape,bshape);
            return op(apply_at(a,aidx),apply_at(b,bidx));
        } // operator()
    }; // outer_t

    // provide user defined CTAD with tuple of arrays as args
    template <typename op_t, typename...arrays_t>
    ufunc_t(op_t, std::tuple<arrays_t...>) -> ufunc_t<op_t,arrays_t...>;

    template <typename op_t, typename...arrays_t>
    constexpr auto _ufunc(ufunc_t<op_t,arrays_t...> func)
    {
        // help deduction
        return decorator_t<ufunc_t,op_t,arrays_t...>{func};
    }; // _ufunc

    /**
     * @brief Creates unfunc_t object, given op and arrays.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam arrays_t 
     * @param op 
     * @param array 
     * @param arrays 
     * @return constexpr auto 
     */
    template <typename op_t, typename array_t, typename...arrays_t>
    constexpr auto ufunc(op_t op, const array_t& array, const arrays_t&...arrays)
    {
        // enable broadcasting if operands >= 2
        if constexpr (sizeof...(arrays) > 0) {
            auto b_arrays = broadcast_arrays(array, arrays...);
            auto func = ufunc_t{op, b_arrays};
            // NOTE: deduction failed
            // return decorator_t{func};
            return _ufunc(func);
        }
        // single argument ufunc, skip broadcasting
        else {
            using view_t = decorator_t<ufunc_t,op_t,array_t>;
            return view_t{{op,{array}}};
        }
    } // ufunc

    /**
     * @brief Create reduce_t object given op, array, axis and initial value.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam initial_t 
     * @param op operation to perform, must be binary op
     * @param array array in which reduction to be performed
     * @param axis axis to reduce
     * @param initial inital value, can be None
     * @param keepdims keep reduced axes in the result as dimensions with size one.
     * @return constexpr auto 
     */
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t=std::false_type>
    constexpr auto reduce(op_t op, const array_t& array, const axis_t& axis, initial_t initial, keepdims_t keepdims=keepdims_t{})
    {
        // note: axis as reference to prevent array decays

        // when axis is None, reduce can return scalar or ndarray depends on keepdims type
        // use variant to tell that the return value may be scalar or ndarray,
        // depending on the value of keepdims at runtime
        if constexpr (is_none_v<axis_t> && meta::is_boolean_v<keepdims_t>) {
            using scalar_t = decorator_t<reduce_t,op_t,array_t,axis_t,initial_t,std::false_type>;
            using ndarray_t = decorator_t<reduce_t,op_t,array_t,axis_t,initial_t,std::true_type>;
            // TODO: make default either type configurable
            using either_t = std::variant<scalar_t,ndarray_t>;
            return (keepdims ?
                    either_t{ndarray_t{{op,array,axis,initial,True}}}
                : either_t{scalar_t{{op,array,axis,initial,False}}});
        }
        // otherwise simply use as it is
        else {
            using view_t = decorator_t<reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t>;
            return view_t{{op,array,axis,initial,keepdims}};
        }
    } // reduce

    /**
     * @brief Create accumulate_t object given op, array and axis.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @param op 
     * @param array 
     * @param axis 
     * @return constexpr auto 
     */
    template <typename op_t, typename array_t, typename axis_t>
    constexpr auto accumulate(op_t op, const array_t& array, axis_t axis)
    {
        // note: axis as reference to prevent array decays
        using view_t = decorator_t<accumulate_t,op_t,array_t,axis_t>;
        return view_t{{op,array,axis}};
    } // accumulate

    /**
     * @brief Create outer_t object given op, lhs array and rhs array.
     * 
     * @tparam op_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     * @param op operation to perform for each pair of lhs and rhs
     * @param lhs lhs array
     * @param rhs rhs array
     * @return constexpr auto 
     */
    template <typename op_t, typename lhs_t, typename rhs_t>
    constexpr auto outer(op_t op, const lhs_t& lhs, const rhs_t& rhs)
    {
        using view_t = decorator_t<outer_t,op_t,lhs_t,rhs_t>;
        return view_t{{op,{lhs,rhs}}};
    }
} // namespace nmtools::view

namespace nmtools::meta
{
    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename op_t, typename...arrays_t>
    struct fixed_matrix_size< view::ufunc_t<op_t,arrays_t...> >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename op_t, typename...arrays_t>
    struct fixed_vector_size< view::ufunc_t<op_t,arrays_t...> >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    /**
     * @brief Specialization of hybrid_ndarray_max_size for ufunc view.
     *
     * Note that when this meta fn returns not Fail results,
     * is_hybrid_ndarray concept should be true.
     * 
     * @tparam op_t 
     * @tparam arrays_t 
     */
    template <typename op_t, typename...arrays_t>
    struct hybrid_ndarray_max_size< view::decorator_t<view::ufunc_t, op_t,arrays_t...> >
    {
        static inline constexpr auto value = [](){
            if constexpr ((is_hybrid_ndarray_v<arrays_t> && ...)) {
                using types = std::tuple<arrays_t...>;
                return template_reduce<sizeof...(arrays_t)>([](auto init, auto index){
                    constexpr auto i = decltype(index)::value;
                    using type = at_t<types,i>;
                    constexpr auto s = hybrid_ndarray_max_size_v<type>;
                    return (init > s ? init : s);
                }, 0ul);
            } else {
                return detail::Fail;
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
        using type = value_type;
    }; // hybrid_ndarray_max_size

    template <typename op_t, typename...arrays_t>
    struct fixed_dim< view::decorator_t<view::ufunc_t, op_t,arrays_t...> >
    {
        static inline constexpr auto value = [](){
            if constexpr ((is_fixed_dim_ndarray_v<arrays_t> && ...)) {
                using types = std::tuple<arrays_t...>;
                auto ref_dim  = fixed_dim_v<at_t<types,0>>;
                if constexpr (static_cast<bool>((fixed_dim_v<arrays_t> == ...)))
                    return ref_dim;
                else return detail::Fail;
            } else {
                return detail::Fail;
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
        using type = value_type;
    }; // fixed_dim

    /**
     * @brief Specialization of fixed_ndarray_shape for ufunc view
     * 
     * @tparam op_t 
     * @tparam arrays_t 
     */
    template <typename op_t, typename...arrays_t>
    struct fixed_ndarray_shape< view::ufunc_t<op_t,arrays_t...> >
    {
        static inline constexpr auto value = [](){
            using array_types = type_list<arrays_t...>;
            // check if all arrays is fixed shape
            // NOTE: somehow if constexpr with fold expression doesnt work, use template_for instead
            constexpr auto all_fixed_shape = [](){
                auto all_fixed = true;
                template_for<sizeof...(arrays_t)>([&all_fixed](auto index){
                    constexpr auto I = decltype(index)::value;
                    using type = type_list_at_t<I,array_types>;
                    all_fixed = all_fixed && is_fixed_size_ndarray_v<type>;
                });
                return all_fixed;
            }();
            // if all array is fixed shape, check if all array has same shape
            if constexpr (all_fixed_shape) {
                // assume at least 1 array is provided
                using array0_t = type_list_at_t<0,array_types>;
                constexpr auto shape0 = fixed_ndarray_shape_v<array0_t>;
                // actual checking
                constexpr auto shame_shape = [=](){
                    auto same = true;
                    template_for<sizeof...(arrays_t)>([&same,&shape0](auto index){
                        constexpr auto I = decltype(index)::value;
                        using type = type_list_at_t<I,array_types>;
                        static_assert( !std::is_void_v<type>
                            , "internal error: fixed_ndarray_shape< view::ufunc_t<op_t,arrays_t...> >"
                        );
                        static_assert( is_fixed_size_ndarray_v<type>
                            , "internal error: fixed_ndarray_shape< view::ufunc_t<op_t,arrays_t...> >"
                        );
                        same = same && utils::isequal(fixed_ndarray_shape_v<type>,shape0);
                    });
                    return same;
                }();
                // if all arrays have the same shape, return the shape
                // otherwise return fail
                if constexpr (shame_shape)
                    return shape0;
                else return detail::Fail;
            }
            // otherwise return fail
            else return detail::Fail;
        }();
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename op_t, typename...arrays_t>
    struct is_ndarray< view::decorator_t< view::ufunc_t, op_t, arrays_t... >>
    {
        static constexpr auto value = (is_ndarray_v<arrays_t> && ...);
    };

    template <typename op_t, typename...arrays_t>
    struct get_element_type<
        view::decorator_t< view::ufunc_t, op_t, arrays_t... >
    >
    {
        using type = typename view::ufunc_t<op_t, arrays_t...>::result_type;
    };

    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct fixed_matrix_size<
        view::reduce_t< op_t, array_t, axis_t, initial_t, keepdims_t >
    >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct fixed_vector_size<
        view::reduce_t< op_t, array_t, axis_t, initial_t, keepdims_t >
    >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
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
                && is_integral_constant_v<axis_t>
                && (is_integral_constant_v<keepdims_t> || is_none_v<keepdims_t>)
            ) {
                constexpr auto shape = fixed_ndarray_shape_v<array_t>;
                constexpr auto axis  = axis_t::value;
                constexpr auto keepdims = [](){
                    if constexpr (is_integral_constant_v<keepdims_t>)
                        return keepdims_t::value;
                    else /* if constexpr (is_none_v) */ return false;
                }();
                return index::remove_dims(shape, axis, keepdims);
            } else {
                return detail::Fail;
            }
        }();
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct is_ndarray< 
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t >
    >
    {
        static constexpr auto value_ = [](){
            if constexpr (is_none_v<axis_t> && is_none_v<keepdims_t>)
                return false;
            else if constexpr (is_none_v<axis_t> && is_integral_constant_v<keepdims_t>)
                return static_cast<bool>(keepdims_t::value);
            else return true;
        }();
        static constexpr auto value = is_ndarray_v<array_t> && value_;
    };

    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct is_num< 
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t >
    >
    {
        static constexpr auto value_ = [](){
            if constexpr (is_none_v<keepdims_t>)
                return true;
            else if constexpr (is_integral_constant_v<keepdims_t>)
                return !static_cast<bool>(keepdims_t::value);
            else return false;
        }();
        static constexpr auto value = is_ndarray_v<array_t> && is_none_v<axis_t> && value_;
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
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct resolve_optype<
        void, array::eval_t, view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t>, none_t
    >
    {
        static constexpr auto vtype = [](){
            using view_t = view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t>;
            if constexpr (is_fixed_size_ndarray_v<view_t>) {
                // NOTE: resolve_unary_array_type defined in eval.hpp
                // only call on fixed_size_ndarray because axis_t may be runtime value otherwise
                return resolve_unary_array_type(as_value_v<array_t>, as_value_v<view_t>);
            } else if constexpr (is_num_v<view_t>) {
                using type = get_element_type_t<view_t>;
                return as_value_v<type>;
            } else /* if constexpr (is_ndarray_v<view_t>) */ {
                using element_t = get_element_type_t<view_t>;
                using type = make_dynamic_ndarray_t<element_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype

    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename op_t, typename array_t, typename axis_t>
    struct fixed_matrix_size<
        view::accumulate_t< op_t, array_t, axis_t >
    >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename op_t, typename array_t, typename axis_t>
    struct fixed_vector_size<
        view::accumulate_t< op_t, array_t, axis_t >
    >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    template <typename op_t, typename array_t, typename axis_t>
    struct fixed_ndarray_shape<
        view::accumulate_t< op_t, array_t, axis_t >
    >
    {
        // accumulate ufunc doesnt change the shape
        static inline constexpr auto value = fixed_ndarray_shape_v<array_t>;
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename op_t, typename array_t, typename axis_t>
    struct is_ndarray< 
        view::decorator_t< view::accumulate_t, op_t, array_t, axis_t >
    >
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };

    // provide specialization for reducer
    template <typename op_t, typename array_t, typename axis_t>
    struct get_element_type<
        view::decorator_t< view::accumulate_t, op_t, array_t, axis_t >
    >
    {
        using type = typename view::accumulate_t<op_t, array_t, axis_t>::result_type;
    };

    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename op_t, typename lhs_t, typename rhs_t>
    struct fixed_matrix_size<
        view::outer_t< op_t, lhs_t, rhs_t >
    >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename op_t, typename lhs_t, typename rhs_t>
    struct fixed_vector_size<
        view::outer_t< op_t, lhs_t, rhs_t >
    >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    template <typename op_t, typename lhs_t, typename rhs_t>
    struct fixed_ndarray_shape<
        view::outer_t< op_t, lhs_t, rhs_t >
    >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_fixed_size_ndarray_v<lhs_t> && is_fixed_size_ndarray_v<rhs_t>) {
                constexpr auto lhs_shape = fixed_ndarray_shape_v<lhs_t>;
                constexpr auto rhs_shape = fixed_ndarray_shape_v<rhs_t>;
                return index::shape_outer(lhs_shape,rhs_shape);
            } else {
                return detail::fail_t{};
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
    }; // fixed_ndarray_shape

    /**
     * @brief Infer the fixed dim for outer view.
     *
     * Return Fail when dimension of the view is not known at compile-time.
     * 
     * @tparam op_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename op_t, typename lhs_t, typename rhs_t>
    struct fixed_dim<
        view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t >
    >
    {
        static constexpr auto value = [](){
            using view_t = view::outer_t< op_t, lhs_t, rhs_t >;
            if constexpr (
                   is_fixed_dim_ndarray_v<lhs_t>
                && is_fixed_dim_ndarray_v<rhs_t>
            ) {
                return fixed_dim_v<lhs_t> + fixed_dim_v<rhs_t>;
            } else {
                return detail::Fail;
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
        using type = value_type;
    };

    /**
     * @brief Infer maximum size (of hybrid ndarray) for outer view.
     * 
     * Return Fail when the view is not hybrid ndarray.
     * 
     * @tparam op_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename op_t, typename lhs_t, typename rhs_t>
    struct hybrid_ndarray_max_size<
        view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t >
    >
    {
        static constexpr auto value = [](){
            if constexpr (
                   is_hybrid_ndarray_v<lhs_t>
                && is_hybrid_ndarray_v<rhs_t>
            ) {
                return hybrid_ndarray_max_size_v<lhs_t> * hybrid_ndarray_max_size_v<rhs_t>;
            } else if constexpr (
                   is_fixed_size_ndarray_v<lhs_t>
                && is_hybrid_ndarray_v<rhs_t>
            ) {
                constexpr auto shape = fixed_ndarray_shape_v<lhs_t>;
                constexpr auto lhs = index::sum(shape);
                constexpr auto rhs = hybrid_ndarray_max_size_v<rhs_t>;
                return lhs * rhs;
            }  else if constexpr (
                   is_hybrid_ndarray_v<lhs_t>
                && is_fixed_size_ndarray_v<rhs_t>
            ) {
                constexpr auto lhs = hybrid_ndarray_max_size_v<lhs_t>;
                constexpr auto shape = fixed_ndarray_shape_v<rhs_t>;
                constexpr auto rhs = index::sum(shape);
                return lhs * rhs;
            } else {
                return detail::Fail;
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
        using type = value_type;
    };

    template <typename op_t, typename lhs_t, typename rhs_t>
    struct is_ndarray< 
        view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t >
    >
    {
        static constexpr auto value = is_ndarray_v<lhs_t> && is_ndarray_v<rhs_t>;
    };

    // provide specialization for reducer
    template <typename op_t, typename lhs_t, typename rhs_t>
    struct get_element_type<
        view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t >
    >
    {
        using type = typename view::outer_t<op_t, lhs_t, rhs_t>::result_type;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_UFUNC_HPP
