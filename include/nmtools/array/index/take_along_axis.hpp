#ifndef NMTOOLS_ARRAY_INDEX_TAKE_ALONG_AXIS_HPP
#define NMTOOLS_ARRAY_INDEX_TAKE_ALONG_AXIS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/index/normalize_axis.hpp"
#include "nmtools/array/index/broadcast_shape.hpp"

namespace nmtools::index
{
    struct shape_take_along_axis_t {};

    struct take_along_axis_t {};

    /**
     * @brief Compute the resulting shape of take_along_axis op.
     * 
     * @tparam shape_t 
     * @tparam shape_indices_t 
     * @tparam axis_t 
     * @param shape     the shape of src array
     * @param indices   the shape of indices args
     * @param axis      axis in which the op to be operates on
     * @return constexpr auto 
     */
    template <typename shape_t, typename shape_indices_t, typename axis_t>
    constexpr auto shape_take_along_axis(const shape_t& shape, const shape_indices_t& indices, axis_t axis)
    {
        // TODO: take actual indices instead of the shape of indices, to allow bound check
        using result_t = meta::resolve_optype_t<shape_take_along_axis_t,shape_t,shape_indices_t,axis_t>;

        if constexpr (!meta::is_fail_v<result_t>) {
            // TODO: make maybe type at resolve_optype
            using return_t = nmtools_maybe<result_t>;

            auto shape_dim   = (size_t)len(shape);
            auto indices_dim = (size_t)len(indices);
            auto maybe_axis  = normalize_axis(axis, shape_dim);

            const auto [broadcast_s, b_shape] = broadcast_shape(shape,indices);

            if (!static_cast<bool>(maybe_axis) || !((size_t)shape_dim == (size_t)indices_dim) || !static_cast<bool>(broadcast_s)) {
                return return_t {}; // Nothing
            }

            auto result = result_t {};
            auto axis_  = *maybe_axis;
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(shape_dim);
            }

            for (size_t i=0; i<(size_t)shape_dim; i++) {
                if (i==axis_) {
                    at(result,i) = at(indices,i);
                } else {
                    at(result,i) = at(b_shape,i);
                }
            }

            return return_t{result};
        } else {
            // let the caller decide what to do
            return result_t {};
        }
    } // shape_take_along_axis

} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        // we do not know the type
        template <typename...>
        struct SHAPE_TAKE_ALONG_AXIS_UNSUPPORTED : detail::fail_t {};

        // shape and indices for take_along_axis must have the same number of dims
        template <typename...>
        struct SHAPE_TAKE_ALONG_AXIS_INVALID_DIM : detail::fail_t {};

        template <typename...>
        struct TAKE_ALONG_AXIS_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    template <typename shape_t, typename indices_shape_t, typename axis_t>
    struct resolve_optype<
        void, index::shape_take_along_axis_t, shape_t, indices_shape_t, axis_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_constant_index_array_v<shape_t>) {
                using type = resolve_optype_t<index::shape_take_along_axis_t, decltype(to_value_v<shape_t>), indices_shape_t, axis_t>;
                return as_value_v<type>;
            } else if constexpr (is_fixed_index_array_v<shape_t> && is_fixed_index_array_v<indices_shape_t> && is_index_v<axis_t>) {
                constexpr auto shape_dim   = len_v<shape_t>;
                constexpr auto indices_dim = len_v<indices_shape_t>;
                if constexpr (shape_dim == indices_dim) {
                    using type = transform_bounded_array_t<shape_t>;
                    return as_value_v<type>;
                } else {
                    using type = error::SHAPE_TAKE_ALONG_AXIS_INVALID_DIM<shape_t,indices_shape_t,axis_t>;
                    return as_value_v<type>;
                }
            } else if constexpr (is_index_array_v<shape_t> && is_index_array_v<indices_shape_t> && is_index_v<axis_t>) {
                // TODO: consider to return maybe type here
                // take_along_axis doesn't change dimension
                using type = transform_bounded_array_t<shape_t>;
                return as_value_v<type>;
            } else {
                using type = error::SHAPE_TAKE_ALONG_AXIS_UNSUPPORTED<shape_t,indices_shape_t,axis_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // shape_take_along_axis_t

    template <typename dst_indices_t, typename shape_t, typename indices_t, typename axis_t>
    struct resolve_optype<
        void, index::take_along_axis_t, dst_indices_t, shape_t, indices_t, axis_t
    >
    {
        static constexpr auto vtype = [](){
            using element_t = get_element_type_t<indices_t>;
            // simply follow shape_t
            if constexpr (
                   is_index_array_v<dst_indices_t>
                && is_index_array_v<shape_t>
                && is_ndarray_v<indices_t>
                && is_index_v<element_t>
                && is_index_v<axis_t>
            ) {
                using type = transform_bounded_array_t<shape_t>;
                return as_value_v<type>;
            } else {
                using type = error::TAKE_ALONG_AXIS_UNSUPPORTED<dst_indices_t, shape_t, indices_t, axis_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
    
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_TAKE_ALONG_AXIS_HPP