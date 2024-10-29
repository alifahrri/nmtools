#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCCOSH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCCOSH_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct arccosh
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::acosh(t);
        } // operator()
    }; // arccosh
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using arccosh_t = fun::arccosh;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto arccosh(const left_t& a)
    {
        return unary_ufunc(arccosh_t{},a);
    } // arccosh
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::arccosh,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::arccosh) const
        {
            nmtools_string str;

            str += "arccosh";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCCOSH_HPP