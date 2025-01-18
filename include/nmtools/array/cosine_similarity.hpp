#ifndef NMTOOLS_ARRAY_ARRAY_COSINE_SIMILARITY_HPP
#define NMTOOLS_ARRAY_ARRAY_COSINE_SIMILARITY_HPP

#include "nmtools/array/view/cosine_similarity.hpp"
#include "nmtools/array/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename lhs_t, typename rhs_t, typename axis_t=meta::ct<1>, typename eps_t=float>
    constexpr auto cosine_similarity(const lhs_t& lhs, const rhs_t& rhs, axis_t axis=axis_t{}, eps_t eps=eps_t{1e-8}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::cosine_similarity(lhs,rhs,axis,eps);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // cosine_similarity
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_COSINE_SIMILARITY_HPP