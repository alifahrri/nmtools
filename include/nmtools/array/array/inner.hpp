#ifndef NMTOOLS_ARRAY_ARRAY_INNER_HPP
#define NMTOOLS_ARRAY_ARRAY_INNER_HPP

#include "nmtools/array/view/inner.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename lhs_t, typename rhs_t>
    constexpr auto inner(const lhs_t& lhs, const rhs_t& rhs
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::inner(lhs,rhs);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // inner
}

#endif // NMTOOLS_ARRAY_ARRAY_INNER_HPP