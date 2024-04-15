#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_EXP_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_EXP_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct exp
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::exp(t);
        } // operator()
    }; // exp
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using exp_t = fun::exp;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto exp(const left_t& a)
    {
        return ufunc(exp_t{},a);
    } // exp
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::exp,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::exp) const
        {
            nmtools_string str;

            str += "exp";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_EXP_HPP