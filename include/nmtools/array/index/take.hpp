#ifndef NMTOOLS_ARRAY_INDEX_TAKE_HPP
#define NMTOOLS_ARRAY_INDEX_TAKE_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/ndarray/hybrid.hpp"

namespace nmtools::index
{
    struct take_t {};
    struct shape_take_t {};

    template <typename shape_t, typename indices_t, typename axis_t>
    constexpr auto shape_take(const shape_t& shape, const indices_t& indices, [[maybe_unused]] axis_t axis)
    {
        using return_t = meta::resolve_optype_t<shape_take_t,shape_t,indices_t,axis_t>;

        auto res = return_t {};

        if constexpr (!meta::is_constant_index_array_v<return_t>) {
            auto n = len(indices);
            // TODO: error when n > at(shape,axis)

            using namespace literals;

            if constexpr (is_none_v<axis_t>)
                at(res,0_ct) = n;
            else {
                using element_t = meta::get_index_element_type_t<return_t>;
                auto shape_take_impl = [&](auto i){
                    using common_t = meta::promote_index_t<axis_t,decltype(i)>;
                    at(res,i) = ((common_t)i == (common_t)axis) ? (element_t)n : (element_t)at(shape,i);
                };
                [[maybe_unused]] auto dim = len(shape);
                if constexpr (meta::is_resizable_v<return_t>)
                    res.resize(dim);

                if constexpr (meta::is_fixed_index_array_v<shape_t>) {
                    constexpr auto DIM = meta::len_v<shape_t>;
                    meta::template_for<DIM>(shape_take_impl);
                }
                else {
                    for (size_t i=0; i<dim; i++)
                        shape_take_impl(i);
                }
            }
        }

        return res;
    } // shape_take

    template <typename index_t, typename shape_t, typename indices_t, typename axis_t>
    constexpr auto take(const index_t& index, const shape_t& shape, const indices_t& indices, [[maybe_unused]] axis_t axis)
    {
        using return_t = meta::resolve_optype_t<take_t,index_t,shape_t,indices_t,axis_t>;

        auto res = return_t {};
        [[maybe_unused]] auto dim = len(shape);
        if constexpr (meta::is_resizable_v<return_t>)
            res.resize(dim);

        // map dst index to src index (original array) at given axis
        // for example
        // ```
        // shape = [6]
        // indices = [0,1,4]
        // axis = 0
        // index = [2]
        // ```
        // let n be the number of dim,
        // the dst_i is index at i
        // the src_i should be the value of indices at dst_i

        if constexpr (is_none_v<axis_t>) {
            // handle flat indices
            // TODO: provide overload that already compute strides
            auto strides = compute_strides(shape);
            auto dst_i   = at(index,0);
            auto offset  = at(indices,dst_i);
            impl::compute_indices(res, offset, shape, strides);
        }
        else {
            auto take_impl = [&](auto i){
                auto dst_i = at(index,i);
                using common_t = meta::promote_index_t<axis_t,decltype(i)>;
                at(res, i) = ((common_t)i == (common_t)axis) ? at(indices,dst_i) : dst_i;
            };
            if constexpr (meta::is_fixed_index_array_v<index_t>) {
                constexpr auto DIM = meta::len_v<index_t>;
                meta::template_for<DIM>(take_impl);
            }
            else {
                for (size_t i=0; i<dim; i++)
                    take_impl(i);
            }
        }

        return res;
    } // take
} // namespace nmtools::index

namespace nmtools::meta
{
    // TODO: compute at compile-time whenever possible
    template <typename shape_t, typename indices_t>
    struct resolve_optype<
        void, index::shape_take_t, shape_t, indices_t, none_t
    >
    {
        // when slicing flattened array, the shape should be single element 1D array
        using type = nmtools_array<size_t,1>;
    }; // shape_take_t

    namespace error
    {
        template <typename...>
        struct SHAPE_TAKE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename shape_t, typename indices_t, typename axis_t>
    struct resolve_optype<
        void, index::shape_take_t, shape_t, indices_t, axis_t
    >
    {
        static constexpr auto vtype = [](){
            // indices may not be index array
            using index_t = get_element_or_common_type_t<indices_t>;
            [[maybe_unused]] constexpr auto index_array_or_index_ndarray = (is_ndarray_v<indices_t> && is_index_v<index_t>) || is_index_array_v<indices_t>;
            if constexpr (
                (is_constant_index_array_v<shape_t> || is_clipped_index_array_v<shape_t>)
                && is_constant_index_array_v<indices_t>
                && (is_none_v<axis_t> || is_constant_index_v<axis_t>)
            ) {
                constexpr auto shape = to_value_v<shape_t>;
                constexpr auto axis  = to_value_v<axis_t>;
                constexpr auto indices = to_value_v<indices_t>;
                constexpr auto result  = index::shape_take(shape, indices, axis);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_type = type_t<decltype(init)>;
                    constexpr auto I = at(result,index);
                    if constexpr (is_constant_index_array_v<shape_t>) {
                        using type = append_type_t<init_type,ct<I>>;
                        return as_value_v<type>;
                    } else {
                        using type = append_type_t<init_type,clipped_size_t<I>>;
                        return as_value_v<type>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_index_array_v<shape_t> && index_array_or_index_ndarray && is_none_v<axis_t>) {
                return as_value_v<none_t>;
            } else if constexpr (
                is_index_array_v<shape_t>
                && index_array_or_index_ndarray
                && is_index_v<axis_t>
            ) {
                if constexpr (is_bounded_array_v<shape_t> || is_constant_index_array_v<shape_t>) {
                    constexpr auto N = len_v<shape_t>;
                    using type = nmtools_array<index_t,N>;
                    return as_value_v<type>;
                } else {
                    // when slicing at given axis, the resulting shape type follow original shape
                    return as_value_v<shape_t>;
                }
            } else {
                using type = error::SHAPE_TAKE_UNSUPPORTED<shape_t,indices_t,axis_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // shape_take_t

    template <typename dst_indices_t, typename shape_t, typename indices_t, typename axis_t>
    struct resolve_optype<
        void, index::take_t, dst_indices_t, shape_t, indices_t, axis_t
    >
    {
        static constexpr auto vtype = [](){
            constexpr auto DIM = len_v<shape_t>;
            constexpr auto b_dim = bounded_size_v<shape_t>;
            using index_t = get_index_element_type_t<shape_t>;
            if constexpr (DIM > 0) {
                using type = nmtools_array<index_t,DIM>;
                return as_value_v<type>;
            } else if constexpr (!is_fail_v<decltype(b_dim)>) {
                using type = array::static_vector<index_t,b_dim>;
                return as_value_v<type>;
            } else {
                // TODO: small buffer optimization
                using type = nmtools_list<index_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // take_t
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_TAKE_HPP