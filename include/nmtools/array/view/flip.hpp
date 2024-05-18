#ifndef NMTOOLS_ARRAY_VIEW_FLIP_HPP
#define NMTOOLS_ARRAY_VIEW_FLIP_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/index/flip.hpp"
#include "nmtools/array/view/slice.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/apply_at.hpp"

namespace nmtools::view
{
    /**
     * @brief Reverse the order of elements of given array according to specified axis.
     *
     * Axis can be None, a single integer, or index_array.
     * For None axis, reverse all original axis.
     * 
     * @tparam array_t 
     * @tparam axis_t 
     * @param array array in which its elements are to be reversed
     * @param axis axis to operate
     * @return constexpr auto 
     */
    template <typename array_t, typename axis_t>
    constexpr inline auto flip(const array_t& array, const axis_t& axis)
    {
        auto a_dim  = dim<true>(array);
        auto slices = index::flip_slices(a_dim,axis);
        return apply_slice(array,slices);
    } // flip
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_FLIP_HPP