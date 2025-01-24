#ifndef NMTOOLS_ARRAY_VIEW_COSINE_SIMILARITY_HPP
#define NMTOOLS_ARRAY_VIEW_COSINE_SIMILARITY_HPP

#include "nmtools/array/broadcast_arrays.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/vector_norm.hpp"
#include "nmtools/array/sum.hpp"

namespace nmtools::view
{
    template <typename lhs_t, typename rhs_t, typename axis_t=meta::ct<1>, typename eps_t=float>
    constexpr auto cosine_similarity(const lhs_t& lhs, const rhs_t& rhs, axis_t axis=axis_t{}, eps_t eps=eps_t{1e-8})
    {
        // tuple<maybe<>,...> is not usable in constant expression :(
        // so broadcast arrays must return maybe<tuple<...>>
        auto broadcasted = view::broadcast_arrays(lhs,rhs);
        // TODO: support get to propagate maybe type
        auto a_lhs = nmtools::get<0>(unwrap(broadcasted));
        auto a_rhs = nmtools::get<1>(unwrap(broadcasted));

        auto keepdims = True;
        auto lhs_norm = view::maximum(
            view::vector_norm(a_lhs,axis,keepdims)
            , eps
        );
        auto rhs_norm = view::maximum(
            view::vector_norm(a_rhs,axis,keepdims)
            , eps
        );
        auto similarity = view::sum(view::divide(
            view::multiply(a_lhs,a_rhs)
            , view::multiply(lhs_norm,rhs_norm)
        ), axis);
        return similarity;
    }
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_COSINE_SIMILARITY_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_COSINE_SIMILARITY_HPP
#define NMTOOLS_ARRAY_ARRAY_COSINE_SIMILARITY_HPP

#include "nmtools/array/cosine_similarity.hpp"
#include "nmtools/core/eval.hpp"

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