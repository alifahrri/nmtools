#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_BITWISE_AND_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_BITWISE_AND_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view::fun
{
    struct bitwise_and
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t & u;
        } // operator()
    }; // bitwise_and
}

namespace nmtools::view
{
    using bitwise_and_t = fun::bitwise_and;

    template <typename left_t, typename right_t>
    constexpr auto bitwise_and(const left_t& a, const right_t& b)
    {
        return ufunc(bitwise_and_t{},a,b);
    } // bitwise_and
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::bitwise_and,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::bitwise_and) const
        {
            auto str = nmtools_string();

            str += "bitwise_and";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_BITWISE_AND_HPP