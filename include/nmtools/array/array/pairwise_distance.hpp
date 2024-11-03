#ifndef NMTOOLS_ARRAY_ARRAY_PAIRWISE_DISTANCE_HPP
#define NMTOOLS_ARRAY_ARRAY_PAIRWISE_DISTANCE_HPP

#include "nmtools/array/view/pairwise_distance.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename lhs_t, typename rhs_t, typename ord_t=meta::ct<2>, typename eps_t=float, typename keepdims_t=meta::false_type>
    constexpr auto pairwise_distance(const lhs_t& lhs, const rhs_t& rhs, ord_t ord=ord_t{}, eps_t eps=eps_t{1e-6}, keepdims_t keepdims=keepdims_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::pairwise_distance(lhs,rhs,ord,eps,keepdims);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    }
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_PAIRWISE_DISTANCE_HPP