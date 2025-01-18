#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_TAN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_TAN_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct tan
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::tan(t);
        } // operator()
    }; // tan
}

namespace nmtools::view
{
    using tan_t = fun::tan;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto tan(const left_t& a)
    {
        return unary_ufunc(tan_t{},a);
    } // tan
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::tan,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::tan) const
        {
            nmtools_string str;

            str += "tan";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_TAN_HPP