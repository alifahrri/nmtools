#ifndef NMTOOLS_ARRAY_ARRAY_SINH_HPP
#define NMTOOLS_ARRAY_ARRAY_SINH_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/sinh.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct sinh
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto sinh = view::sinh(a);
                return eval(sinh
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // sinh
    } // namespace fn

    constexpr inline auto sinh = fn::sinh{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SINH_HPP