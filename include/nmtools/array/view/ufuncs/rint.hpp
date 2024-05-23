#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_RINT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_RINT_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct rint
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::rint(t);
        } // operator()
    }; // rint
}

namespace nmtools::view
{
    using rint_t = fun::rint;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto rint(const left_t& a)
    {
        return unary_ufunc(rint_t{},a);
    } // rint
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::rint,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::rint) const
        {
            nmtools_string str;

            str += "rint";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_RINT_HPP