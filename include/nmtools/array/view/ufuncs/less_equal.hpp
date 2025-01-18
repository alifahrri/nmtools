#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LESS_EQUAL_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LESS_EQUAL_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct less_equal
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t <= u;
        } // operator()
    }; // less_equal
}

namespace nmtools::view
{
    using less_equal_t = fun::less_equal;

    template <typename left_t, typename right_t>
    constexpr auto less_equal(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(less_equal_t{},a,b);
    } // less_equal
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::less_equal,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::less_equal) const
        {
            auto str = nmtools_string();

            str += "less_equal";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LESS_EQUAL_HPP