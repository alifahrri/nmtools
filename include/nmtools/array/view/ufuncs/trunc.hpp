#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_TRUNC_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_TRUNC_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct trunc
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::trunc(t);
        } // operator()
    }; // trunc
}

namespace nmtools::view
{
    using trunc_t = fun::trunc;

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto trunc(const left_t& a)
    {
        return unary_ufunc(trunc_t{},a);
    } // trunc
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::trunc,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::trunc) const
        {
            nmtools_string str;

            str += "trunc";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_TRUNC_HPP