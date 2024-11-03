#ifndef NMTOOLS_ARRAY_VIEW_COSINE_SIMILARITY_HPP
#define NMTOOLS_ARRAY_VIEW_COSINE_SIMILARITY_HPP

#include "nmtools/array/view/broadcast_arrays.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"
#include "nmtools/array/view/ufuncs/maximum.hpp"
#include "nmtools/array/view/ufuncs/divide.hpp"
#include "nmtools/array/view/vector_norm.hpp"
#include "nmtools/array/view/sum.hpp"

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