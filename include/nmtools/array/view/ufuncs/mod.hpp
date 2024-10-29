#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_MOD_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_MOD_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view::fun
{
    struct mod
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t % u;
        } // operator()
    }; // mod
}

namespace nmtools::view
{
    using mod_t = fun::mod;

    template <typename left_t, typename right_t>
    constexpr auto mod(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(mod_t{},a,b);
    } // mod
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::mod,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::mod) const
        {
            auto str = nmtools_string();

            str += "mod";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_MOD_HPP