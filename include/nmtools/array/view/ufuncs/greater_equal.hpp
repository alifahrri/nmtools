#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_GREATER_EQUAL_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_GREATER_EQUAL_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view::fun
{
    struct greater_equal
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t >= u;
        } // operator()
    }; // greater_equal
}

namespace nmtools::view
{
    using greater_equal_t = fun::greater_equal;

    template <typename left_t, typename right_t>
    constexpr auto greater_equal(const left_t& a, const right_t& b)
    {
        return ufunc(greater_equal_t{},a,b);
    } // greater_equal
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <>
    struct to_string_t<view::fun::greater_equal,none_t>
    {
        auto operator()(view::fun::greater_equal) const
        {
            auto str = nmtools_string();

            str += "greater_equal";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_GREATER_EQUAL_HPP