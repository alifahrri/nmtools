#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATION_SOFTSIGN_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATION_SOFTSIGN_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    /**
     * @brief Function object for softsign ufunc
     * 
     */
    struct softsign_t
    {
        template <typename T>
        constexpr auto operator()(const T& x) const
        {
            auto abs_x = x > 0 ? x : -x;
            return x / (1 + abs_x);
        } // operator()
    }; // softsign_t

    /**
     * @brief Create element-wise softsign ufunc view
     * 
     * @tparam array_t 
     * @param array     input array
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto softsign(const array_t& array)
    {
        return ufunc(softsign_t{}, array);
    } // softsign
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATION_SOFTSIGN_HPP