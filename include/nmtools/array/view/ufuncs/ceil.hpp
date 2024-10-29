#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_CEIL_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_CEIL_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct ceil
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::ceil(t);
        } // operator()
    }; // ceil
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using ceil_t = fun::ceil;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto ceil(const left_t& a)
    {
        return unary_ufunc(ceil_t{},a);
    } // ceil
};

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::ceil,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::ceil) const
        {
            nmtools_string str;

            str += "ceil";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_CEIL_HPP