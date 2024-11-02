#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_NEGATIVE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_NEGATIVE_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view::fun
{
    struct negative
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return -t;
        } // operator()
    }; // negative
}

namespace nmtools::view
{
    using negative_t = fun::negative;

    template <typename left_t>
    constexpr auto negative(const left_t& a)
    {
        return unary_ufunc(negative_t{},a);
    } // negative
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::negative,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::negative) const
        {
            nmtools_string str;

            str += "negative";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_NEGATIVE_HPP