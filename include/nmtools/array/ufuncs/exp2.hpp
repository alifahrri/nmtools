#ifndef NMTOOLS_ARRAY_ARRAY_EXP2_HPP
#define NMTOOLS_ARRAY_ARRAY_EXP2_HPP

#include "nmtools/array/core/eval.hpp"
#include "nmtools/array/view/ufuncs/exp2.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct exp2
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto exp2 = view::exp2(a);
                return eval(exp2
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // exp2
    } // namespace fn

    constexpr inline auto exp2 = fn::exp2{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_EXP2_HPP