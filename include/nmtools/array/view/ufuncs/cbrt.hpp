#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_CBRT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_CBRT_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct cbrt
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::cbrt(t);
        } // operator()
    }; // cbrt
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using cbrt_t = fun::cbrt;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto cbrt(const left_t& a)
    {
        return unary_ufunc(cbrt_t{},a);
    } // cbrt
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::cbrt,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::cbrt) const
        {
            nmtools_string str;

            str += "cbrt";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_CBRT_HPP