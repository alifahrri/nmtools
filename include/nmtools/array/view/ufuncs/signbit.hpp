#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_SIGNBIT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_SIGNBIT_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct signbit
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::signbit(t);
        } // operator()
    }; // signbit
}

namespace nmtools::view
{
    using signbit_t = fun::signbit;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto signbit(const left_t& a)
    {
        return ufunc(signbit_t{},a);
    } // signbit
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::signbit,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::signbit) const
        {
            nmtools_string str;

            str += "signbit";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_SIGNBIT_HPP