#ifndef NMTOOLS_ARRAY_VIEW_ZEROS_HPP
#define NMTOOLS_ARRAY_VIEW_ZEROS_HPP

#include "nmtools/array/view/full.hpp"

namespace nmtools::view
{
    /**
     * @brief Creates zeros view with given shape and dtype.
     *
     * All elements of this views has value of 0.
     * 
     * @tparam shape_t 
     * @tparam T 
     * @param shape 
     * @return constexpr auto 
     */
    template <typename shape_t, typename T>
    constexpr auto zeros(const shape_t& shape, dtype_t<T>)
    {
        return full(shape,static_cast<T>(0));
    } // zeros
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ZEROS_HPP