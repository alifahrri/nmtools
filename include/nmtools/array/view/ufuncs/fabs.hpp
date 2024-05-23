#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_FABS_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_FABS_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct fabs
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::fabs(t);
        } // operator()
    }; // fabs
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using fabs_t = fun::fabs;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto fabs(const left_t& a)
    {
        return unary_ufunc(fabs_t{},a);
    } // fabs
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::fabs,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::fabs) const
        {
            nmtools_string str;

            str += "fabs";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_FABS_HPP