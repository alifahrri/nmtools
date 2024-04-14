#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_SQRT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_SQRT_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct sqrt
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::sqrt(t);
        } // operator()
    }; // sqrt
}

namespace nmtools::view
{
    using sqrt_t = fun::sqrt;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto sqrt(const left_t& a)
    {
        return ufunc(sqrt_t{},a);
    } // sqrt
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::sqrt,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::sqrt) const
        {
            nmtools_string str;

            str += "sqrt";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_SQRT_HPP