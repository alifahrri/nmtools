#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_OR_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_OR_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct logical_or
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return static_cast<bool>(t) || static_cast<bool>(u);
        } // operator()
    }; // logical_or
}

namespace nmtools::view
{
    using logical_or_t = fun::logical_or;

    template <typename left_t, typename right_t>
    constexpr auto logical_or(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(logical_or_t{},a,b);
    } // logical_or

    template <typename left_t, typename axis_t>
    constexpr auto reduce_logical_or(const left_t& a, const axis_t& axis)
    {
        auto init = false;
        return reduce(logical_or_t{},a,axis,init);
    } // reduce_logical_or
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::logical_or,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::logical_or) const
        {
            auto str = nmtools_string();

            str += "logical_or";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_OR_HPP