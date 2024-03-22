#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LESS_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LESS_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view::fun
{
    struct less
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t < u;
        } // operator()
    }; // less
}

namespace nmtools::view
{
    using less_t = fun::less;

    template <typename left_t, typename right_t>
    constexpr auto less(const left_t& a, const right_t& b)
    {
        return ufunc(less_t{},a,b);
    } // less
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <>
    struct to_string_t<view::fun::less,none_t>
    {
        auto operator()(view::fun::less) const
        {
            auto str = nmtools_string();

            str += "less";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LESS_HPP