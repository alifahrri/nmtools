#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCCOS_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCCOS_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct arccos
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::acos(t);
        } // operator()
    }; // arccos
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using arccos_t = fun::arccos;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto arccos(const left_t& a)
    {
        return unary_ufunc(arccos_t{},a);
    } // arccos
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::arccos,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::arccos) const
        {
            nmtools_string str;

            str += "arccos";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCCOS_HPP