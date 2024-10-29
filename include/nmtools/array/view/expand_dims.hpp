#ifndef NMTOOLS_ARRAY_VIEW_EXPAND_DIMS_HPP
#define NMTOOLS_ARRAY_VIEW_EXPAND_DIMS_HPP

#include "nmtools/array/index/expand_dims.hpp"
#include "nmtools/array/view/reshape.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::view
{
    /**
     * @brief expand the shape of an array
     * 
     * @tparam array_t array_like
     * @tparam axis_t integer or array of integer
     * @param array input array
     * @param axis Position in the expanded axes where the new axis (or axes) is placed.
     * @return constexpr auto expand_dims view
     */
    template <typename array_t, typename axis_t>
    constexpr auto expand_dims(const array_t& array, const axis_t& axis)
    {
        auto src_shape = shape<true>(array);
        auto dst_shape = index::shape_expand_dims(src_shape,axis);
        return view::reshape(array,dst_shape);
    } // expand_dims

} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_EXPAND_DIMS_HPP