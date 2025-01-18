#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_FLOOR_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_FLOOR_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct floor
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::floor(t);
        } // operator()
    }; // floor
}

namespace nmtools::view
{
    using floor_t = fun::floor;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto floor(const left_t& a)
    {
        return unary_ufunc(floor_t{},a);
    } // floor
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::floor,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::floor) const
        {
            nmtools_string str;

            str += "floor";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_FLOOR_HPP