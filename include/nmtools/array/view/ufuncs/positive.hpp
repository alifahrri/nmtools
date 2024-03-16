#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_POSITIVE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_POSITIVE_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view::fun
{
    struct positive
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return +t;
        } // operator()
    }; // positive
}

namespace nmtools::view
{
    using positive_t = fun::positive;

    template <typename left_t>
    constexpr auto positive(const left_t& a)
    {
        return ufunc(positive_t{},a);
    } // positive
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <>
    struct to_string_t<view::fun::positive,none_t>
    {
        auto operator()(view::fun::positive) const
        {
            nmtools_string str;

            str += "positive";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_POSITIVE_HPP