#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOG2_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOG2_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct log2
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::log2(t);
        } // operator()
    }; // log2
}

namespace nmtools::view
{
    using log2_t = fun::log2;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto log2(const left_t& a)
    {
        return unary_ufunc(log2_t{},a);
    } // log2
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::log2,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::log2) const
        {
            nmtools_string str;

            str += "log2";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOG2_HPP