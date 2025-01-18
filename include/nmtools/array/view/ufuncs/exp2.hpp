#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_EXP2_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_EXP2_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct exp2
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::exp2(t);
        } // operator()
    }; // exp2
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using exp2_t = fun::exp2;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto exp2(const left_t& a)
    {
        return unary_ufunc(exp2_t{},a);
    } // exp2
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::exp2,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::exp2) const
        {
            nmtools_string str;

            str += "exp2";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_EXP2_HPP