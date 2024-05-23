#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOG10_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOG10_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct log10
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::log10(t);
        } // operator()
    }; // log10
}

namespace nmtools::view
{
    using log10_t = fun::log10;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto log10(const left_t& a)
    {
        return unary_ufunc(log10_t{},a);
    } // log10
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::log10,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::log10) const
        {
            nmtools_string str;

            str += "log10";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOG10_HPP