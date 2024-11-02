#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_COS_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_COS_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct cos
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::cos(t);
        } // operator()
    }; // cos
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using cos_t = fun::cos;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto cos(const left_t& a)
    {
        return unary_ufunc(cos_t{},a);
    } // cos
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::cos,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::cos) const
        {
            nmtools_string str;

            str += "cos";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_COS_HPP