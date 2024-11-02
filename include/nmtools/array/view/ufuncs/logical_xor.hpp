#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_XOR_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_XOR_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view::fun
{
    struct logical_xor
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return static_cast<bool>(t) ^ static_cast<bool>(u);
        } // operator()
    }; // logical_xor
}

namespace nmtools::view
{
    using logical_xor_t = fun::logical_xor;

    template <typename left_t, typename right_t>
    constexpr auto logical_xor(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(logical_xor_t{},a,b);
    } // logical_xor

    template <typename left_t, typename axis_t>
    constexpr auto reduce_logical_xor(const left_t& a, const axis_t& axis)
    {
        auto init = false;
        return reduce(logical_xor_t{},a,axis,init);
    } // reduce_logical_xor
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::logical_xor,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::logical_xor) const
        {
            auto str = nmtools_string();

            str += "logical_xor";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_XOR_HPP