#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATION_SOFTSIGN_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATION_SOFTSIGN_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for softsign ufunc
     * 
     */
    struct softsign
    {
        template <typename T>
        constexpr auto operator()(const T& x) const
        {
            auto abs_x = x > 0 ? x : -x;
            return x / (1 + abs_x);
        } // operator()
    }; // softsign
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <>
    struct to_string_t<view::fun::softsign,none_t>
    {
        auto operator()(view::fun::softsign) const
        {
            nmtools_string str;

            str += "softsign";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using softsign_t = fun::softsign;

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