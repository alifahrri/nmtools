#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_NEGATIVE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_NEGATIVE_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view::fun
{
    struct negative
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return -t;
        } // operator()
    }; // negative
}

namespace nmtools::view
{
    using negative_t = fun::negative;

    template <typename left_t>
    constexpr auto negative(const left_t& a)
    {
        return ufunc(negative_t{},a);
    } // negative
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <>
    struct to_string_t<view::fun::negative,none_t>
    {
        auto operator()(view::fun::negative) const
        {
            nmtools_string str;

            str += "negative";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_NEGATIVE_HPP