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
#include "nmtools/utility/fwd.hpp"

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
        template <typename result_t
            , typename array_t
            , typename initial_t=none_t
            , typename where_t=none_t>
        constexpr auto reduce(
            const array_t& array
            , [[maybe_unused]] initial_t initial=initial_t{}
            , [[maybe_unused]] const where_t& where=where_t{}
        ) const
        {
            using index_t = nm_size_t;
            auto i_id = 1;
            auto m_initial = [&](){
                if constexpr (
                    meta::has_identity_v<op_t>
                    && is_none_v<initial_t>
                ) {
                    i_id = 0;
                    return static_cast<result_t>(op.identity());
                } else if constexpr (
                    is_none_v<where_t>
                    && is_none_v<initial_t>
                ) {
                    return static_cast<result_t>(at(array,0));
                } else {
                    i_id = 0;
                    return static_cast<result_t>(initial);
                }
                // TODO: check for invalid case
                // if where is not none, must have identity
            }();
            auto size = len(array);
            for (index_t i=i_id; i<(index_t)size; i++) {
                if constexpr (is_none_v<where_t>) {
                    m_initial = op(m_initial,at(array,i));
                } else {
                    auto w_i = at(where,i);
                    if (w_i) {
                        m_initial = op(m_initial,at(array,i));
                    }
                }
            }
            return m_initial;
        } // reduce

        template <typename result_t
            , typename array_t
            , typename initial_t=none_t
            , typename where_t=none_t>
        constexpr auto operator()(
            const array_t& array
            , [[maybe_unused]] initial_t initial=initial_t{}
            , [[maybe_unused]] const where_t& where=where_t{}
        ) const
        {
            return reduce<result_t>(array,initial,where);
        }

        template <typename result_t
            , typename array_t
            , typename initial_t=none_t
            , typename where_t=none_t>
        constexpr auto operator()(
            meta::as_value<result_t>
            , const array_t& array
            , [[maybe_unused]] initial_t initial=initial_t{}
            , [[maybe_unused]] const where_t& where=where_t{}
        ) const
        {
            return reduce<result_t>(array,initial,where);
        }
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
        using operand_type  = meta::fwd_operand_t<array_t>;
        using array_type    = operand_type;
        using axis_type     = meta::fwd_attribute_t<axis_t>;
        using op_type       = op_t;
        using initial_type  = initial_t;
        using reducer_type  = reducer_t<op_t>;
        using keepdims_type = keepdims_t;
        using dtype_type    = dtype_t;

        using attributes_type = args::reduce<axis_type,dtype_type,initial_type,keepdims_type,op_type>;

        using left_array_type  = meta::conditional_t<meta::is_tuple_v<array_t>,meta::at_t<array_t,0>,array_t>;
        using src_element_type = meta::get_element_type_t<meta::remove_cvref_t<left_array_type>>;

        using src_shape_type = decltype(nmtools::shape<true>(meta::declval<left_array_type>()));
        using dst_shape_type = const meta::resolve_optype_t<index::remove_dims_t,src_shape_type,axis_t,keepdims_t>;

        using result_type  = meta::get_reducer_result_type_t<reducer_type,src_element_type,dtype_type,initial_type>;
        using element_type = result_type;

        op_type       op;
        array_type    array;
        axis_type     axis;
        initial_type  initial;
        reducer_type  reducer;
        keepdims_type keepdims;
        dtype_type    dtype;

        dst_shape_type shape_;

        constexpr reduce_t(op_type op, const array_t& array_, const axis_t& axis_, initial_type initial, keepdims_type keepdims_, dtype_type dtype=dtype_type{})
            : op(op)
            , array(fwd_operand(array_))
            , axis(fwd_attribute(axis_))
            , initial(initial)
            , reducer{op} // TODO: remove, recurse to scalar reduce ufunc instead of using reducer
            , keepdims(keepdims_)
            , dtype(dtype)
            , shape_(index::remove_dims([&](){
                if constexpr (meta::is_tuple_v<array_t>) {
                    return nmtools::shape<true>(nmtools::get<0>(array_));
                } else {
                    return nmtools::shape<true>(array_);
                }
            }(),axis_,keepdims_))
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
            if constexpr (meta::is_tuple_v<array_type>) {
                return array;
            } else {
                return nmtools_tuple<array_type>{array};
            }
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

        template <typename array_type, typename slices_t>
        static constexpr auto get_slice(const array_type& array, const slices_t& slices)
        {
            if constexpr (meta::is_pointer_v<array_type>) {
                return view::apply_slice(*array,slices);
            } else {
                return view::apply_slice(array, slices);
            }
        } // get_slice

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

            auto make_subarray = [](const auto& array, const auto& indices, const auto& axis, const auto keepdims){
                auto m_shape   = detail::shape<true>(array);
                auto slices    = index::reduction_slices(indices,unwrap(m_shape),axis,keepdims);
                auto sliced    = get_slice(array, slices);
                auto flattened = view::flatten(sliced);
                return flattened;
            };

            // apply slice only works with fixed dim ndarray for now
            // TODO: support dynamic dim ndarray
            const auto subarray = [&](){
                if constexpr (meta::is_tuple_v<array_type>) {
                    const auto m_array = nmtools::get<0>(array);
                    return make_subarray(m_array,indices_,axis,keepdims);
                } else {
                    return make_subarray(array,indices_,axis,keepdims);
                }
            }();
            const auto where = [&](){
                if constexpr (meta::is_tuple_v<array_type>) {
                    const auto m_array = nmtools::get<1>(array);
                    return make_subarray(m_array,indices_,axis,keepdims);
                } else {
                    return None;
                }
            }();
            auto result_vtype = meta::as_value_v<result_type>;
            return reducer(result_vtype,unwrap(subarray),initial,unwrap(where));
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

        // TODO: remove
        constexpr operator num_type() const
        {
            if constexpr (meta::is_fail_v<num_type>) {
                return num_type{};
            } else {
                // reduce the whole array
                // must check if array is pointer or not since
                // flatten (and view in general) doesn't accept pointer
                
                auto make_subarray = [](const auto& array){
                    using array_type = meta::remove_cvref_t<decltype(array)>;
                    if constexpr (meta::is_pointer_v<array_type>) {
                        auto flattened = view::flatten(*array);
                        return flattened;
                    } else {
                        auto flattened = view::flatten(array);
                        return flattened;
                    }
                };
    
                // TODO: support dynamic dim ndarray
                const auto subarray = [&](){
                    if constexpr (meta::is_tuple_v<array_type>) {
                        const auto m_array = nmtools::get<0>(array);
                        return make_subarray(m_array);
                    } else {
                        return make_subarray(array);
                    }
                }();
                const auto where = [&](){
                    if constexpr (meta::is_tuple_v<array_type>) {
                        const auto m_array = nmtools::get<1>(array);
                        return make_subarray(m_array);
                    } else {
                        return None;
                    }
                }();
                auto result_vtype = meta::as_value_v<result_type>;
                return reducer(result_vtype,unwrap(subarray),initial,unwrap(where));
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
        using operand_type  = meta::fwd_operand_t<array_t>;
        using array_type    = operand_type;
        using axis_type     = meta::fwd_attribute_t<none_t>;
        using op_type       = op_t;
        using initial_type  = initial_t;
        using reducer_type  = reducer_t<op_t>;
        using keepdims_type = keepdims_t;
        using dtype_type    = dtype_t;

        using attributes_type = args::reduce<axis_type,dtype_type,initial_type,keepdims_type,op_type>;

        using left_array_type  = meta::conditional_t<meta::is_tuple_v<array_t>,meta::at_t<array_t,0>,array_t>;
        using src_element_type = meta::get_element_type_t<meta::remove_cvref_t<left_array_type>>;

        using src_shape_type = decltype(nmtools::shape<true>(meta::declval<left_array_type>()));
        using dst_shape_type = const meta::resolve_optype_t<index::remove_dims_t,src_shape_type,axis_type,keepdims_t>;

        using result_type  = meta::get_reducer_result_type_t<reducer_type,src_element_type,dtype_type,initial_type>;
        using element_type = result_type;

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
            , array(fwd_operand(array_))
            , axis(fwd_attribute(axis_))
            , initial(initial)
            , reducer{op}
            , keepdims(keepdims_)
            , dtype(dtype)
            , shape_(index::remove_dims([&](){
                if constexpr (meta::is_tuple_v<array_t>) {
                    return nmtools::shape<true>(nmtools::get<0>(array_));
                } else {
                    return nmtools::shape<true>(array_);
                }
            }(),axis_,keepdims_))
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
            if constexpr (meta::is_tuple_v<array_type>) {
                return array;
            } else {
                return nmtools_tuple<array_type>{array};
            }
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

        constexpr auto reduce() const
        {
            auto make_subarray = [](const auto& array){
                using array_type = meta::remove_cvref_t<decltype(array)>;
                if constexpr (meta::is_pointer_v<array_type>) {
                    auto flattened = view::flatten(*array);
                    return flattened;
                } else {
                    auto flattened = view::flatten(array);
                    return flattened;
                }
            };
            // reduce the whole array
            const auto subarray = [&](){
                if constexpr (meta::is_tuple_v<array_type>) {
                    const auto m_array = nmtools::get<0>(array);
                    return make_subarray(m_array);
                } else {
                    return make_subarray(array);
                }
            }();
            const auto where = [&](){
                if constexpr (meta::is_tuple_v<array_type>) {
                    const auto m_array = nmtools::get<1>(array);
                    return make_subarray(m_array);
                } else {
                    return None;
                }
            }();
            auto result_vtype = meta::as_value_v<result_type>;
            return reducer(result_vtype,unwrap(subarray),initial,unwrap(where));
        }

        constexpr operator result_type() const
        {
            return reduce();
        } // operator result_type()

        // TODO: remove
        template <typename...size_types>
        constexpr auto operator()(size_types.../*indices*/) const
        {
            return reduce();
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
        // TODO: check if array_t is tuple of ndarray
        static constexpr auto value = (is_ndarray_v<array_t> || meta::is_tuple_v<array_t>) && !is_num_v<view_t>;
    };

    // provide specialization for reducer
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t, typename dtype_t>
    struct get_element_type<
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t, dtype_t >
    >
    {
        using type = typename view::reduce_t<op_t, array_t, axis_t, initial_t, keepdims_t, dtype_t>::result_type;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_UFUNC_REDUCE_HPP