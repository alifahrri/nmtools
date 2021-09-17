#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_HARDSWISH_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_HARDSWISH_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    /**
     * @brief Function object for hardswish ufunc.
     * 
     */
    struct hardswish_t
    {
        template <typename T>
        constexpr auto operator()(const T& x) const
        {
            if (x < -3) {
                return static_cast<T>(0);
            } else if (x >= 3) {
                return x;
            } else {
                return x * (x + 3) / 6;
            }
        } // operator()
    }; // hardswish_t

    /**
     * @brief Create element-wise hardswish ufunc view.
     * 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto hardswish(const array_t& array)
    {
        return ufunc(hardswish_t{},array);
    } // hardswish
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_HARDSWISH_HPP