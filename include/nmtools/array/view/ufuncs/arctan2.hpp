#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTAN2_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTAN2_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct arctan2
    {
        template <typename T, typename U>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return math::atan2(t,u);
        } // operator()
    }; // arctan2
}

namespace nmtools::view
{
    using arctan2_t = fun::arctan2;

    template <typename left_t, typename right_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto arctan2(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(arctan2_t{},a,b);
    } // arctan2
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::arctan2,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::arctan2) const
        {
            auto str = nmtools_string();

            str += "arctan2";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTAN2_HPP