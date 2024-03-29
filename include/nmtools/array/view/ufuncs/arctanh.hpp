#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTANH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTANH_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct arctanh
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::atanh(t);
        } // operator()
    }; // arctanh
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using arctanh_t = fun::arctanh;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto arctanh(const left_t& a)
    {
        return ufunc(arctanh_t{},a);
    } // arctanh
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <>
    struct to_string_t<view::fun::arctanh,none_t>
    {
        auto operator()(view::fun::arctanh) const
        {
            nmtools_string str;

            str += "arctanh";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTANH_HPP