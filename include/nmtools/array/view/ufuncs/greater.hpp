#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_GREATER_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_GREATER_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view::fun
{
    struct greater_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t > u;
        } // operator()
    }; // greater_t
}

namespace nmtools::view
{
    using greater_t = fun::greater;

    template <typename left_t, typename right_t>
    constexpr auto greater(const left_t& a, const right_t& b)
    {
        return ufunc(greater_t{},a,b);
    } // greater
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <>
    struct to_string_t<view::fun::greater,none_t>
    {
        auto operator()(view::fun::greater) const
        {
            auto str = nmtools_string();

            str += "greater";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_GREATER_HPP