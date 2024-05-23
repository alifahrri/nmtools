#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_SIN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_SIN_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct sin
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::sin(t);
        } // operator()
    }; // sin
}

namespace nmtools::view
{
    using sin_t = fun::sin;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto sin(const left_t& a)
    {
        return unary_ufunc(sin_t{},a);
    } // sin
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::sin,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::sin) const
        {
            nmtools_string str;

            str += "sin";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_SIN_HPP