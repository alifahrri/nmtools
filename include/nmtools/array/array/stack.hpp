#ifndef NMTOOLS_ARRAY_ARRAY_STACK_HPP
#define NMTOOLS_ARRAY_ARRAY_STACK_HPP

#include "nmtools/array/view/stack.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename lhs_array_t, typename rhs_array_t, typename axis_t=meta::ct<0>>
    constexpr auto stack(const lhs_array_t& lhs, const rhs_array_t& rhs, axis_t axis=axis_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto result = view::stack(lhs,rhs,axis);
        return eval(result
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // stack
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_STACK_HPP