#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_EXPM1_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_EXPM1_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct expm1
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::expm1(t);
        } // operator()
    }; // expm1
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using expm1_t = fun::expm1;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto expm1(const left_t& a)
    {
        return unary_ufunc(expm1_t{},a);
    } // expm1
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::expm1,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::expm1) const
        {
            nmtools_string str;

            str += "expm1";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_EXPM1_HPP