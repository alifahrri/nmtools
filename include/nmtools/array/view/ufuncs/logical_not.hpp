#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_NOT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_NOT_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools;:view::fun
{
    struct logical_not
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return !static_cast<bool>(t);
        } // operator()
    }; // logical_not
}

namespace nmtools::view
{
    using logical_not_t = fun::logical_not;

    template <typename left_t>
    constexpr auto logical_not(const left_t& a)
    {
        return ufunc(logical_not_t{},a);
    } // logical_not
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <>
    struct to_string_t<view::fun::logical_not,none_t>
    {
        auto operator()(view::fun::logical_not) const
        {
            auto str = nmtools_string();

            str += "logical_not";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING


#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_NOT_HPP