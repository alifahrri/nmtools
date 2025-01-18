#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_COSH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_COSH_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct cosh
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::cosh(t);
        } // operator()
    }; // cosh
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using cosh_t = fun::cosh;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto cosh(const left_t& a)
    {
        return unary_ufunc(cosh_t{},a);
    } // cosh
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::cosh,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::cosh) const
        {
            nmtools_string str;

            str += "cosh";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_COSH_HPP