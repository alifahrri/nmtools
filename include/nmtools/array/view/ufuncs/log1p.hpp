#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOG1P_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOG1P_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct log1p
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::log1p(t);
        } // operator()
    }; // log1p
}

namespace nmtools::view
{
    using log1p_t = fun::log1p;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto log1p(const left_t& a)
    {
        return unary_ufunc(log1p_t{},a);
    } // log1p
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::log1p,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::log1p) const
        {
            nmtools_string str;

            str += "log1p";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOG1P_HPP