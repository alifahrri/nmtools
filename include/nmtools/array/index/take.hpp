#ifndef NMTOOLS_ARRAY_INDEX_TAKE_HPP
#define NMTOOLS_ARRAY_INDEX_TAKE_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/compute_indices.hpp"

namespace nmtools::index
{
    struct take_t {};
    struct shape_take_t {};

    template <typename shape_t, typename indices_t, typename axis_t>
    constexpr auto shape_take(const shape_t& shape, const indices_t& indices, axis_t axis)
    {
        using return_t = meta::resolve_optype_t<shape_take_t,shape_t,indices_t,axis_t>;

        auto res = return_t {};

        auto n = len(indices);
        // TODO: error when n > at(shape,axis)
        auto shape_take_impl = [&](auto i){
            at(res,i) = (i == axis) ? n : at(shape,i);
        };

        if constexpr (is_none_v<axis_t>)
            at(res,0) = n;
        else {
            auto dim = len(shape);
            if constexpr (meta::is_resizeable_v<return_t>)
                res.resize(dim);

            if constexpr (meta::has_tuple_size_v<shape_t>) {
                constexpr auto DIM = std::tuple_size_v<shape_t>;
                meta::template_for<DIM>(shape_take_impl);
            }
            else {
                for (size_t i=0; i<dim; i++)
                    shape_take_impl(i);
            }
        }

        return res;
    } // shape_take

    template <typename index_t, typename shape_t, typename indices_t, typename axis_t>
    constexpr auto take(const index_t& index, const shape_t& shape, const indices_t& indices, axis_t axis)
    {
        using return_t = meta::resolve_optype_t<take_t,index_t,shape_t,indices_t,axis_t>;

        auto res = return_t {};
        auto dim = len(shape);
        if constexpr (meta::is_resizeable_v<return_t>)
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
        
        auto take_impl = [&](auto i){
            auto dst_i = at(index,i);
            at(res, i) = (i == axis) ? at(indices,dst_i) : dst_i;
        };

        if constexpr (is_none_v<axis_t>) {
            // handle flat indices
            // TODO: provide overload that already compute strides
            auto strides = compute_strides(shape);
            auto dst_i   = at(index,0);
            auto offset  = at(indices,dst_i);
            impl::compute_indices(res, offset, shape, strides);
        }
        else {
            if constexpr (meta::has_tuple_size_v<index_t>) {
                constexpr auto DIM = std::tuple_size_v<index_t>;
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
    template <typename shape_t, typename indices_t>
    struct resolve_optype<
        void, index::shape_take_t, shape_t, indices_t, none_t
    >
    {
        // when slicing flattened array, the shape should be single element 1D array
        using type = std::array<size_t,1>;
    }; // shape_take_t

    template <typename shape_t, typename indices_t, typename axis_t>
    struct resolve_optype<
        void, index::shape_take_t, shape_t, indices_t, axis_t
    >
    {
        // when slicing at given axis, the resulting shape type follow original shape
        using type = tuple_to_array_t<transform_bounded_array_t<shape_t>>;
    }; // shape_take_t

    template <typename index_t, typename shape_t, typename indices_t, typename axis_t>
    struct resolve_optype<
        void, index::take_t, index_t, shape_t, indices_t, axis_t
    >
    {
        using type = tuple_to_array_t<transform_bounded_array_t<shape_t>>;
    }; // take_t
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_TAKE_HPP