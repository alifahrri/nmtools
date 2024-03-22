#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_TANH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_TANH_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct tanh
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::tanh(t);
        } // operator()
    }; // tanh
}

namespace nmtools::view
{
    using tanh_t = fun::tanh;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto tanh(const left_t& a)
    {
        return ufunc(tanh_t{},a);
    } // tanh
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <>
    struct to_string_t<view::fun::tanh,none_t>
    {
        auto operator()(view::fun::tanh) const
        {
            nmtools_string str;

            str += "tanh";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_TANH_HPP