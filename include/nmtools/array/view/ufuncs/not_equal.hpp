#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_NOT_EQUAL_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_NOT_EQUAL_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view::fun
{
    struct not_equal
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t != u;
        } // operator()
    }; // not_equal
}

namespace nmtools::view
{
    using not_equal_t = fun::not_equal;

    template <typename left_t, typename right_t>
    constexpr auto not_equal(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(not_equal_t{},a,b);
    } // not_equal
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::not_equal,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::not_equal) const
        {
            auto str = nmtools_string();

            str += "not_equal";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_NOT_EQUAL_HPP