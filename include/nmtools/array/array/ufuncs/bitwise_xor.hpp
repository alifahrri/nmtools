#ifndef NMTOOLS_ARRAY_ARRAY_BITWISE_XOR_HPP
#define NMTOOLS_ARRAY_ARRAY_BITWISE_XOR_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/bitwise_xor.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct bitwise_xor
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t,
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
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_BITWISE_XOR_HPP