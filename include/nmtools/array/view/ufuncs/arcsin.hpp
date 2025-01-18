#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSIN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSIN_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct arcsin
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::asin(t);
        } // operator()
    }; // arcsin
} // nmtools::view::fun

namespace nmtools::view
{
    using arcsin_t = fun::arcsin;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto arcsin(const left_t& a)
    {
        return unary_ufunc(arcsin_t{},a);
    } // arcsin
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::arcsin,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::arcsin) const
        {
            nmtools_string str;

            str += "arcsin";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSIN_HPP