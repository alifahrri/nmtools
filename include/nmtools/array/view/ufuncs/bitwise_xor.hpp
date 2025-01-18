#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_BITWISE_XOR_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_BITWISE_XOR_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct bitwise_xor
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t ^ u;
        } // operator()
    }; // bitwise_xor
}

namespace nmtools::view
{
    using bitwise_xor_t = fun::bitwise_xor;

    template <typename left_t, typename right_t>
    constexpr auto bitwise_xor(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(bitwise_xor_t{},a,b);
    } // bitwise_xor
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::bitwise_xor,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::bitwise_xor) const
        {
            auto str = nmtools_string();

            str += "bitwise_xor";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_BITWISE_XOR_HPP