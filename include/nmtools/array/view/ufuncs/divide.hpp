#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_DIVIDE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_DIVIDE_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view::fun
{
    struct divide
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t / u;
        } // operator()
    }; // divide
}

namespace nmtools::view
{
    using divide_t = fun::divide;

    template <typename left_t, typename right_t>
    constexpr auto divide(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(divide_t{},a,b);
    } // divide
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::divide,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::divide) const
        {
            auto str = nmtools_string();

            str += "divide";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_DIVIDE_HPP