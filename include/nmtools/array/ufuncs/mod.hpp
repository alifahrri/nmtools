#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_MOD_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_MOD_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

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

#ifndef NMTOOLS_ARRAY_ARRAY_MOD_HPP
#define NMTOOLS_ARRAY_ARRAY_MOD_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/mod.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct mod
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto mod = view::mod(a,b);
                return eval(mod
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // mod
    } // namespace fn

    constexpr inline auto mod = fn::mod{};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_MOD_HPP