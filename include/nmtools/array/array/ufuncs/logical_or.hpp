#ifndef NMTOOLS_ARRAY_ARRAY_LOGICAL_OR_HPP
#define NMTOOLS_ARRAY_ARRAY_LOGICAL_OR_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/logical_or.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct logical_or
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto logical_or = view::logical_or(a,b);
                return eval(logical_or
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // logical_or
    } // namespace fn

    constexpr inline auto logical_or = fn::logical_or{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_LOGICAL_OR_HPP