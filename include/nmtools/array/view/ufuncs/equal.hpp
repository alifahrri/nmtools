#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_EQUAL_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_EQUAL_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view::fun
{
    struct equal
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t == u;
        } // operator()
    }; // equal
}

namespace nmtools::view
{
    using equal_t = fun::equal;

    template <typename left_t, typename right_t>
    constexpr auto equal(const left_t& a, const right_t& b)
    {
        return ufunc(equal_t{},a,b);
    } // equal
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <>
    struct to_string_t<view::fun::equal,none_t>
    {
        auto operator()(view::fun::equal) const
        {
            auto str = nmtools_string();

            str += "equal";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_EQUAL_HPP