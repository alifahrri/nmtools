#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ISFINITE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ISFINITE_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct isfinite
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::isfinite(t);
        } // operator()
    }; // isfinite
}

namespace nmtools::view
{
    using isfinite_t = fun::isfinite;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto isfinite(const left_t& a)
    {
        return ufunc(isfinite_t{},a);
    } // isfinite
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <>
    struct to_string_t<view::fun::isfinite,none_t>
    {
        auto operator()(view::fun::isfinite) const
        {
            nmtools_string str;

            str += "isfinite";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ISFINITE_HPP