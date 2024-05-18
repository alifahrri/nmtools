#ifndef NMTOOLS_ARRAY_VIEW_ONES_HPP
#define NMTOOLS_ARRAY_VIEW_ONES_HPP

#include "nmtools/array/view/full.hpp"

namespace nmtools::view
{
    /**
     * @brief Creates a ones view with given shape and dtype.
     * 
     * All elements in the view has value of 1.
     * 
     * @tparam shape_t 
     * @tparam T 
     * @param shape desired shape
     * @return constexpr auto 
     */
    template <typename shape_t, typename T>
    constexpr auto ones(const shape_t& shape, dtype_t<T>)
    {
        return full(shape,static_cast<T>(1));
    } // ones
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ONES_HPP