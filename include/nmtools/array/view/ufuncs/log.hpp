#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOG_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOG_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct log
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::log(t);
        } // operator()
    }; // log
}

namespace nmtools::view
{
    using log_t = fun::log;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto log(const left_t& a)
    {
        return unary_ufunc(log_t{},a);
    } // log
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::log,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::log) const
        {
            nmtools_string str;

            str += "log";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOG_HPP