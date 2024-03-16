#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSINH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSINH_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct arcsinh
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::asinh(t);
        } // operator()
    }; // arcsinh
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using arcsinh_t = fun::arcsinh;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto arcsinh(const left_t& a)
    {
        return ufunc(arcsinh_t{},a);
    } // arcsinh
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <>
    struct to_string_t<view::fun::arcsinh,none_t>
    {
        auto operator()(view::fun::arcsinh) const
        {
            nmtools_string str;

            str += "arcsinh";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING


#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSINH_HPP