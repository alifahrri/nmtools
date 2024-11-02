#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_BITWISE_OR_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_BITWISE_OR_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view::fun
{
    struct bitwise_or
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t | u;
        } // operator()
    }; // bitwise_or
}

namespace nmtools::view
{
    using bitwise_or_t = fun::bitwise_or;

    template <typename left_t, typename right_t>
    constexpr auto bitwise_or(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(bitwise_or_t{},a,b);
    } // bitwise_or
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::bitwise_or,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::bitwise_or) const
        {
            auto str = nmtools_string();

            str += "bitwise_or";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_BITWISE_OR_HPP