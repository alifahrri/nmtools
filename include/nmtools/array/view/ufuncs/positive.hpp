#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_POSITIVE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_POSITIVE_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct positive
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return +t;
        } // operator()
    }; // positive
}

namespace nmtools::view
{
    using positive_t = fun::positive;

    template <typename left_t>
    constexpr auto positive(const left_t& a)
    {
        return unary_ufunc(positive_t{},a);
    } // positive
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::positive,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::positive) const
        {
            nmtools_string str;

            str += "positive";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_POSITIVE_HPP