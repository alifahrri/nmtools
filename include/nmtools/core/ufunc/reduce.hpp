#ifndef NMTOOLS_ARRAY_VIEW_UFUNC_REDUCE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNC_REDUCE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/ref.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/core/decorator.hpp"
#include "nmtools/core/flatten.hpp"
#include "nmtools/core/slice.hpp"
#include "nmtools/index/outer.hpp"
#include "nmtools/index/remove_dims.hpp"
#include "nmtools/index/where.hpp"
#include "nmtools/index/sum.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/dtypes.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/core/eval.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/utility/as_static.hpp"

#include "nmtools/core/ufunc/detail.hpp"
#include "nmtools/utility/isequal.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/index/reduce.hpp"

namespace nmtools::args
{
    template <
        typename axis_t
        , typename dtype_t
        , typename initial_t
        , typename keepdims_t
        , typename op_t=none_t>
    struct reduce
    {
        using op_type       = op_t;
        using axis_type     = axis_t;
        using dtype_type    = dtype_t;
        using initial_type  = initial_t;
        using keepdims_type = keepdims_t;

        axis_type     axis  = {};
        dtype_type    dtype = {};
        initial_type  initial   = {};
        keepdims_type keepdims  = {};
        op_type       op        = {};

        template <typename...args_t>
        constexpr auto operator==(const reduce<args_t...>& other) const
        {
            using other_type = reduce<args_t...>;
            return utils::isequal(axis,other.axis)
                && utils::isequal(initial,other.initial)
                && utils::isequal(keepdims,other.keepdims)
                && meta::is_same_v<op_t,typename other_type::op_type>
                // TODO: check for dtype
            ;
        }
    };

    template <typename...args_t>
    reduce(args_t...) -> reduce<args_t...>;
} // namespace nmtools::args

namespace nmtools::array
{
    template <auto max_dim, typename...args_t>
    struct as_static_t<
        args::reduce<args_t...>, max_dim
    >
    {
        using attribute_type = args::reduce<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto axis = as_static<max_dim>(attribute.axis);
            return args::reduce{axis
                , attribute.dtype
                , attribute.initial
                , attribute.keepdims
                , attribute.op
            };
        }
    };
} // nmtools::array

namespace nmtools::meta
{
    template <
        typename axis_t
        , typename dtype_t
        , typename initial_t
        , typename keepdims_t
        , typename op_t>
    struct is_attribute<
        args::reduce<axis_t,dtype_t,initial_t,keepdims_t,op_t>
    > : true_type {};
} // namespace nmtools::meta

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename op_t
        , typename axis_t
        , typename dtype_t
        , typename initial_t
        , typename keepdims_t
        , typename formatter_t
    >
    struct to_string_t<
        args::reduce<op_t,axis_t,dtype_t,initial_t,keepdims_t>
        , formatter_t
    >
    {
        using attribute_type = args::reduce<op_t,axis_t,dtype_t,initial_t,keepdims_t>;
        using formatter_type = formatter_t;

        auto operator()(const attribute_type& attribute) const noexcept
        {
            nmtools_string str;

            auto op_str = nmtools_string("");
            op_str = NMTOOLS_TYPENAME_TO_STRING(op_t);

            using mapper_type = to_string_t<decltype(attribute.op),formatter_type>;
            if constexpr (meta::has_result_type_v<mapper_type>) {
                if constexpr (!meta::is_fail_v<typename mapper_type::result_type>) {
                    op_str = to_string(attribute.op,formatter_type{});
                }
            }

            str += "{";

            str += ".op=";
            str += op_str; 
            str += ",.axis=";
            str += to_string(attribute.axis,formatter_type{}); 
            str += ",.dtype=";
            str += to_string(attribute.dtype,formatter_type{}); 
            str += ",.initial=";
            str += to_string(attribute.initial,formatter_type{});
            str += ",.keepdims=";
            str += to_string(attribute.keepdims,formatter_type{});

            str += "}";
            
            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    namespace error
    {
        struct INVALID_NUM_REDUCE : meta::detail::fail_t {};
    } // namespace error

    // TODO: remove, use scalar reduce instead
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
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t, typename dtype_t=none_t>
    struct reduce_t
    {
        // if given array is a view, just use value instead of reference
        using operands_type = resolve_array_type_t<array_t>;
        using array_type    = operands_type;
        using axis_type     = resolve_attribute_type_t<axis_t>;
        using op_type       = op_t;
        using initial_type  = initial_t;
        using reducer_type  = reducer_t<op_t>;
        using element_type  = meta::get_element_type_t<array_t>;
        using keepdims_type = keepdims_t;
        using dtype_type    = dtype_t;

        using attributes_type = args::reduce<axis_type,dtype_type,initial_type,keepdims_type,op_type>;

        using src_shape_type = decltype(nmtools::shape<true>(meta::declval<array_t>()));
        using dst_shape_type = const meta::resolve_optype_t<index::remove_dims_t,src_shape_type,axis_t,keepdims_t>;

        using result_type = meta::type_t<detail::get_result_type<element_type,op_type>>;

        op_type       op;
        array_type    array;
        axis_type     axis;
        initial_type  initial;
        reducer_type  reducer;
        keepdims_type keepdims;
        dtype_type    dtype;

        dst_shape_type shape_;

        constexpr reduce_t(op_type op, const array_t& array_, const axis_t& axis_, initial_type initial, keepdims_type keepdims_, dtype_type dtype=dtype_type{})
            : op(op), array(initialize<array_type>(array_))
            , axis(init_attribute<axis_type>(axis_))
            , initial(initial)
            , reducer{op} // TODO: remove, recurse to scalar reduce ufunc instead of using reducer
            , keepdims(keepdims_)
            , dtype(dtype)
            , shape_(index::remove_dims(nmtools::shape<true>(array_),axis_,keepdims_))
        {}

        constexpr reduce_t(const array_t& array_, const args::reduce<axis_t,dtype_t,initial_t,keepdims_t,op_t>& attributes)
            : reduce_t(
                  attributes.op
                , array_
                , attributes.axis
                , attributes.initial
                , attributes.keepdims
                , attributes.dtype
            )
        {}

        constexpr auto operands() const noexcept
        {
            return nmtools_tuple<array_type>{array};
        }

        constexpr auto attributes() const noexcept
        {
            return attributes_type{axis, dtype, initial, keepdims, op};
        }

        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            // assume arrays is already broadcasted together
            return len(shape());
        } // dim

        constexpr auto size() const
        {
            return index::product(shape());
        }

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
                auto slices = index::reduction_slices(indices_,unwrap(detail::shape<true>(array)),axis,keepdims);
                // this slice operates directly with the underlying array
                // which may be pointer
                if constexpr (meta::is_pointer_v<array_type>) {
                    return apply_slice(*array,slices);
                } else {
                    return apply_slice(array, slices);
                }
            }();
            // NOTE: use view::flatten to avoid ambiguous call because of ADL
            auto flattened = unwrap(view::flatten(sliced));
            // TODO: instead of reduce using reducer_t, return reduce using None axis
            // doing so may simplify evaluation
            return [&](){
                if constexpr (is_none_v<initial_type>)
                    return reducer.template operator()<result_type>(flattened);
                else return reducer.template operator()<result_type>(flattened,initial);
            }();
        } // operator()

        // NOTE: the following is to allow reducing to numeric type
        // maybe encountered when reducing scalar type.
        // following numpy, reducing scalar is allowed.
        static constexpr auto num_vtype = [](){
            using view_t = view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t, dtype_t >;
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
                        return unwrap(view::flatten(*array));
                    } else {
                        return unwrap(view::flatten(array));
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
    template <typename op_t, typename array_t, typename initial_t, typename keepdims_t, typename dtype_t>
    struct reduce_t<op_t,array_t,none_t,initial_t,keepdims_t,dtype_t>
    {
        using array_type    = resolve_array_type_t<array_t>;
        // use reference for now since raw array decays to pointer
        using axis_type     = none_t;
        using op_type       = op_t;
        using initial_type  = initial_t;
        using reducer_type  = reducer_t<op_t>;
        using element_type  = meta::get_element_type_t<array_t>;
        using keepdims_type = keepdims_t;
        using dtype_type    = dtype_t;

        using attributes_type = args::reduce<axis_type,dtype_type,initial_type,keepdims_type,op_type>;

        using src_shape_type = decltype(nmtools::shape<true>(meta::declval<array_t>()));
        using dst_shape_type = const meta::resolve_optype_t<index::remove_dims_t,src_shape_type,axis_type,keepdims_t>;

        using result_type = meta::type_t<detail::get_result_type<element_type,op_type>>;

        op_type       op;
        array_type    array;
        axis_type     axis;
        initial_type  initial;
        reducer_type  reducer;
        keepdims_type keepdims;
        dtype_type    dtype;

        dst_shape_type shape_;

        constexpr reduce_t(op_type op, const array_t& array_, axis_type axis_, initial_type initial, keepdims_type keepdims_, dtype_type dtype=dtype_type{})
            : op(op)
            , array(initialize<array_type>(array_))
            , axis(axis_)
            , initial(initial)
            , reducer{op}
            , keepdims(keepdims_)
            , dtype(dtype)
            , shape_(index::remove_dims(nmtools::shape<true>(array_),axis_,keepdims_))
        {}

        constexpr reduce_t(const array_t& array_, const args::reduce<none_t,dtype_t,initial_t,keepdims_t,op_t>& attributes)
            : reduce_t(
                  attributes.op
                , array_
                , attributes.axis
                , attributes.initial
                , attributes.keepdims
                , attributes.dtype
            )
        {}

        constexpr auto operands() const noexcept
        {
            return nmtools_tuple<array_type>{array};
        }

        constexpr auto attributes() const noexcept
        {
            return attributes_type{axis, dtype, initial, keepdims, op};
        }
        
        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape_);
        } // dim

        constexpr auto size() const noexcept
        {
            // reducing with None axis strictly return 1 element
            return meta::ct_v<1ul>;
        }

        constexpr operator result_type() const
        {
            // reduce the whole array
            // must check if array is pointer or not since
            // flatten (and view in general) doesn't accept pointer
            auto flattened = [&](){
                if constexpr (meta::is_pointer_v<array_type>) {
                    return unwrap(view::flatten(*array));
                } else {
                    return unwrap(view::flatten(array));
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
                    return unwrap(view::flatten(*array));
                } else {
                    return unwrap(view::flatten(array));
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
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t, typename dtype_t>
    struct is_reduction< 
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t, dtype_t >
    > : true_type {};

    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t, typename dtype_t>
    struct is_num< 
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t, dtype_t >
    >
    {
        static constexpr auto value = [](){
            using view_type = view::reduce_t< op_t, array_t, axis_t, initial_t, keepdims_t, dtype_t >;
            using dst_shape_type = typename view_type::dst_shape_type;
            return is_none_v<dst_shape_type>;
        }();
    };

    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t, typename dtype_t>
    struct fixed_size< 
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t, dtype_t >
        // , enable_if_t<!is_none_v<axis_t>>
    >
    {
        static constexpr auto value = [](){
            using decorator_type = view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t, dtype_t >;
            using view_type = view::reduce_t< op_t, array_t, axis_t, initial_t, keepdims_t, dtype_t >;
            if constexpr (has_dst_size_type_v<view_type>) {
                using dst_size_type = typename view_type::dst_size_type;
                if constexpr (is_constant_index_v<dst_size_type>) {
                    return dst_size_type::value;
                } else {
                    return error::FIXED_SIZE_UNSUPPORTED<decorator_type>{};
                }
            } else if constexpr (has_dst_shape_type_v<view_type>) {
                using dst_shape_type = typename view_type::dst_shape_type;
                if constexpr (is_constant_index_array_v<dst_shape_type>) {
                    return index::product(dst_shape_type{});
                } else {
                    return error::FIXED_SIZE_UNSUPPORTED<decorator_type>{};
                }
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<decorator_type>{};
            }
        }();
    }; // fixed_size

    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t, typename dtype_t>
    struct is_ndarray< 
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t, dtype_t >
    >
    {
        using view_t = view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t, dtype_t >;
        static constexpr auto value = is_ndarray_v<array_t> && !is_num_v<view_t>;
    };

    // provide specialization for reducer
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t, typename dtype_t>
    struct get_element_type<
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t, dtype_t >
    >
    {
        using type = typename view::reduce_t<op_t, array_t, axis_t, initial_t, keepdims_t>::result_type;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_UFUNC_REDUCE_HPP