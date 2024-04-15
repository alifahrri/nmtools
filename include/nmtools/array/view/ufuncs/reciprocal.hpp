#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_RECIPROCAL_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_RECIPROCAL_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view::fun
{
    struct reciprocal
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return 1/t;
        } // operator()
    }; // reciprocal
}

namespace nmtools::view
{
    using reciprocal_t = fun::reciprocal;

    template <typename left_t>
    constexpr auto reciprocal(const left_t& a)
    {
        return ufunc(reciprocal_t{},a);
    } // reciprocal
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::reciprocal,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::reciprocal) const
        {
            nmtools_string str;

            str += "reciprocal";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_RECIPROCAL_HPP