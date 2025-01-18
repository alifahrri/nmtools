#ifndef NMTOOLS_ARRAY_ARRAY_POSITIVE_HPP
#define NMTOOLS_ARRAY_ARRAY_POSITIVE_HPP

#include "nmtools/array/core/eval.hpp"
#include "nmtools/array/view/ufuncs/positive.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct positive
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto positive = view::positive(a);
                return eval(positive
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // positive
    } // namespace fn

    constexpr inline auto positive = fn::positive{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_POSITIVE_HPP