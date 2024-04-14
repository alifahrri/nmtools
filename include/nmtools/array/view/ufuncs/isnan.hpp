#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ISNAN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ISNAN_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct isnan
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::isnan(t);
        } // operator()
    }; // isnan
}

namespace nmtools::view
{
    using isnan_t = fun::isnan;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto isnan(const left_t& a)
    {
        return ufunc(isnan_t{},a);
    } // isnan
};

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::isnan,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::isnan) const
        {
            nmtools_string str;

            str += "isnan";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ISNAN_HPP