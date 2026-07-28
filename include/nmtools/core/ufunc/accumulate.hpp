#ifndef NMTOOLS_ARRAY_VIEW_UFUNC_ACCUMULATE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNC_ACCUMULATE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/ref.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/core/decorator.hpp"
#include "nmtools/core/slice.hpp"
#include "nmtools/core/flatten.hpp"
#include "nmtools/index/outer.hpp"
#include "nmtools/index/remove_dims.hpp"
#include "nmtools/index/where.hpp"
#include "nmtools/index/sum.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/dtypes.hpp"
#include "nmtools/core/eval.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/utility/as_static.hpp"

#include "nmtools/core/ufunc/reduce.hpp"
#include "nmtools/core/ufunc/detail.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/utility/isequal.hpp"

namespace nmtools::args
{
    template <
        typename axis_t
        , typename dtype_t
        , typename op_t=none_t>
    struct accumulate
    {
        using op_type = op_t;
        using axis_type = axis_t;
        using dtype_type = dtype_t;

        axis_type axis   = {};
        dtype_type dtype = {};
        op_type op       = {};

        template <typename...args_t>
        constexpr auto operator==(const accumulate<args_t...>& other) const
        {
            using other_type = accumulate<args_t...>;
            return utils::isequal(axis,other.axis)
                && is_same_v<op_type,typename other_type::op_type>
                // TODO: check for dtype
            ;
        }
    };

    template <typename...args_t>
    accumulate(args_t...) -> accumulate<args_t...>;
} // namespace nmtools::args

namespace nmtools
{
    template <auto max_dim, typename...args_t>
    struct as_static_t<
        args::accumulate<args_t...>, max_dim
    >
    {
        using attribute_type = args::accumulate<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto axis = as_static<max_dim>(attribute.axis);
            return args::accumulate{axis,attribute.dtype,attribute.op};
        }
    };
} // nmtools

namespace nmtools::meta
{
    template <
          typename axis_t
        , typename dtype_t
        , typename op_t>
    struct is_attribute<args::accumulate<axis_t,dtype_t,op_t>> : true_type {};
} // namespace nmtools::meta

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename op_t
        , typename axis_t
        , typename dtype_t
        , typename formatter_t
    >
    struct to_string_t<
        args::accumulate<op_t,axis_t,dtype_t>
        , formatter_t
    > {
        using attribute_type = args::accumulate<op_t,axis_t,dtype_t>;
        using formatter_type = formatter_t;

        auto operator()(const attribute_type& attribute) const noexcept
        {
            nmtools_string str;

            auto op_str = to_string(attribute.op);
            if (op_str.empty()) {
                op_str = NMTOOLS_TYPENAME_TO_STRING(op_t);
            }

            str += "{";

            str += ".op=";
            str += op_str;
            str += ",.axis=";
            str += to_string(attribute.axis,formatter_type{});
            str += ",.dtype=";
            str += to_string(attribute.dtype,formatter_type{});

            str += "}";
            
            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

/*************************************************************************** */
namespace nmtools::index
{
    struct accumulate_slices_t {};

    template <typename shape_t, typename indices_t, typename axis_t>
    constexpr auto accumulate_slices([[maybe_unused]] const shape_t& shape
        , [[maybe_unused]] const indices_t& indices
        , [[maybe_unused]] const axis_t axis)
    {
        using result_t = resolve_optype_t<accumulate_slices_t,shape_t,indices_t,axis_t>;
        
        auto result = result_t {};

        // assume if tuple then constant slice index array
        // TODO: add constant slice index array trait concept
        if constexpr (!is_fail_v<result_t>
            && !is_tuple_v<result_t>
        ) {
            [[maybe_unused]] auto dim = len(shape);
            if constexpr (is_resizable_v<result_t>) {
                result.resize(dim);
            }
            for (nm_size_t i=0; i<dim; i++) {
                // index at axis i
                auto s = at(indices,i);
                auto start = (i==(nm_size_t)axis ? 0 : s);
                auto stop  = s + 1;
                at(result,i) = {(nm_size_t)start,(nm_size_t)stop};
            }
        }

        return result;
    } // accumulate_slices
}

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct ACCUMULATE_SLICES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename shape_t, typename indices_t, typename axis_t>
    struct resolve_optype<
        void, index::accumulate_slices_t, shape_t, indices_t, axis_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<shape_t>
                || !is_index_array_v<indices_t>
                || !is_index_v<axis_t>
            ) {
                using type = error::ACCUMULATE_SLICES_UNSUPPORTED<shape_t,indices_t,axis_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<shape_t>
                && is_constant_index_array_v<indices_t>
                && is_constant_index_v<axis_t>
            ) {
                constexpr auto shape   = to_value_v<shape_t>;
                constexpr auto indices = to_value_v<indices_t>;
                constexpr auto result  = index::accumulate_slices(shape,indices,axis_t{});
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    using start_t = ct<(nm_size_t)at(at(result,I),0)>;
                    using stop_t  = ct<(nm_size_t)at(at(result,I),1)>;
                    using slice_t = nmtools_tuple<start_t,stop_t>;
                    using type = append_type_t<init_t,slice_t>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto DIM = len_v<shape_t>;
                constexpr auto MAX_DIM = max_len_v<indices_t>;
                using inner_t = nmtools_array<nm_size_t,2>;
                if constexpr (DIM > 0) {
                    using outer_t = nmtools_array<inner_t,DIM>;
                    return as_value_v<outer_t>;
                } else if constexpr (MAX_DIM > 0) {
                    using outer_t = nmtools_static_vector<inner_t,MAX_DIM>;
                    return as_value_v<outer_t>;
                } else {
                    // TODO: use small vector
                    using outer_t = nmtools_list<inner_t>;
                    return as_value_v<outer_t>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

/*************************************************************************** */

namespace nmtools::view
{
    /**
     * @brief Type constructor for accumulate ufuncs.
     *
     * Accumulate the result on given axis.
     * 
     * @tparam op_t operator type
     * @tparam array_t array type
     * @tparam axis_t axis type
     */
    template <typename op_t, typename array_t, typename axis_t, typename dtype_t=none_t>
    struct accumulate_t
    {
        using array_type    = resolve_array_type_t<array_t>;
        using axis_type     = resolve_attribute_type_t<axis_t>;
        using op_type       = op_t;
        using reducer_type  = reducer_t<op_t>;
        using element_type  = get_element_type_t<array_t>;
        using dtype_type    = dtype_t;

        using result_type = type_t<detail::get_result_type<element_type,op_type>>;

        using attributes_type = args::accumulate<axis_type,dtype_type,op_type>;

        using shape_type = decltype(nmtools::shape<true>(declval<array_t>()));
        using size_type  = decltype(nmtools::size<true>(declval<array_t>()));

        op_type      op;
        array_type   array;
        axis_type    axis;
        reducer_type reducer;
        shape_type   shape_;
        size_type    size_;
        dtype_type   dtype;

        constexpr accumulate_t(op_t op, const array_t& array_, const axis_t& axis, dtype_t dtype={})
            : op(op)
            , array(initialize<array_type>(array_))
            , axis(init_attribute<axis_type>(axis))
            , reducer{op}
            , shape_(nmtools::shape<true>(array_))
            , size_(nmtools::size<true>(array_))
            , dtype(dtype)
        {}

        constexpr accumulate_t(const array_t& array_, const args::accumulate<axis_t,dtype_t,op_t>& attributes)
            : accumulate_t(
                attributes.op
                , array_
                , attributes.axis
                , attributes.dtype
            )
        {}

        constexpr auto operands() const noexcept
        {
            return nmtools_tuple<array_type>{array};
        }

        constexpr auto attributes() const noexcept
        {
            return attributes_type{axis,dtype,op};
        }

        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        constexpr auto size() const
        {
            return size_;
        } // size

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
            auto indices_ = pack_indices(indices...);
            auto slices = index::accumulate_slices(shape_,indices_,axis);
            auto sliced = [&](){
                if constexpr (is_pointer_v<array_type>) {
                    return apply_slice(*array, slices);
                } else {
                    return apply_slice(array, slices);
                }
            }();
            auto flattened = unwrap(view::flatten(sliced));
            return reducer.template operator()<result_type>(flattened);
        } // operator()
    }; // accumulate_t
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename op_t, typename array_t, typename axis_t, typename dtype_t>
    struct is_ndarray< 
        view::decorator_t< view::accumulate_t, op_t, array_t, axis_t, dtype_t >
    >
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };

    // provide specialization for reducer
    template <typename op_t, typename array_t, typename axis_t, typename dtype_t>
    struct get_element_type<
        view::decorator_t< view::accumulate_t, op_t, array_t, axis_t, dtype_t >
    >
    {
        using type = typename view::accumulate_t<op_t, array_t, axis_t, dtype_t>::result_type;
    };
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_VIEW_UFUNC_ACCUMULATE_HPP