#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ISINF_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ISINF_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct isinf
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::isinf(t);
        } // operator()
    }; // isinf
}

namespace nmtools::view
{
    using isinf_t = fun::isinf;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto isinf(const left_t& a)
    {
        return ufunc(isinf_t{},a);
    } // isinf
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <>
    struct to_string_t<view::fun::isinf,none_t>
    {
        auto operator()(view::fun::isinf) const
        {
            nmtools_string str;

            str += "isinf";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ISINF_HPP