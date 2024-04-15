#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_SINH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_SINH_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct sinh
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::sinh(t);
        } // operator()
    }; // sinh
}

namespace nmtools::view
{
    using sinh_t = fun::sinh;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto sinh(const left_t& a)
    {
        return ufunc(sinh_t{},a);
    } // sinh
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::sinh,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::sinh) const
        {
            nmtools_string str;

            str += "sinh";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_SINH_HPP