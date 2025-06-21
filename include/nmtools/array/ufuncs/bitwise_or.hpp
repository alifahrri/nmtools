#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_BITWISE_OR_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_BITWISE_OR_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct bitwise_or
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t | u;
        } // operator()
    }; // bitwise_or
}

namespace nmtools::view
{
    using bitwise_or_t = fun::bitwise_or;

    template <typename left_t, typename right_t>
    constexpr auto bitwise_or(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(bitwise_or_t{},a,b);
    } // bitwise_or
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::bitwise_or,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::bitwise_or) const
        {
            auto str = nmtools_string();

            str += "bitwise_or";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_BITWISE_OR_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_BITWISE_OR_HPP
#define NMTOOLS_ARRAY_ARRAY_BITWISE_OR_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/bitwise_or.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct bitwise_or
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto bitwise_or = view::bitwise_or(a,b);
                return eval(bitwise_or
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // bitwise_or
    } // namespace fn

    constexpr inline auto bitwise_or = fn::bitwise_or{};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_BITWISE_OR_HPP