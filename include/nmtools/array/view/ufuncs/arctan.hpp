#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTAN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTAN_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct arctan
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::atan(t);
        } // operator()
    }; // arctan
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using arctan_t = fun::arctan;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto arctan(const left_t& a)
    {
        return unary_ufunc(arctan_t{},a);
    } // arctan
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::arctan,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::arctan) const
        {
            nmtools_string str;

            str += "arctan";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTAN_HPP