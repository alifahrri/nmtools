#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_BITWISE_XOR_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_BITWISE_XOR_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct bitwise_xor
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t ^ u;
        } // operator()
    }; // bitwise_xor
}

namespace nmtools::view
{
    using bitwise_xor_t = fun::bitwise_xor;

    template <typename left_t, typename right_t>
    constexpr auto bitwise_xor(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(bitwise_xor_t{},a,b);
    } // bitwise_xor
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::bitwise_xor,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::bitwise_xor) const
        {
            auto str = nmtools_string();

            str += "bitwise_xor";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_BITWISE_XOR_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_BITWISE_XOR_HPP
#define NMTOOLS_ARRAY_ARRAY_BITWISE_XOR_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/bitwise_xor.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct bitwise_xor
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto bitwise_xor = view::bitwise_xor(a,b);
                return eval(bitwise_xor
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // bitwise_xor
    } // namespace fn

    constexpr inline auto bitwise_xor = fn::bitwise_xor{};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_BITWISE_XOR_HPP