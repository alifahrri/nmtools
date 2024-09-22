#ifndef NMTOOLS_ARRAY_ARRAY_VECTOR_NORM_HPP
#define NMTOOLS_ARRAY_ARRAY_VECTOR_NORM_HPP

#include "nmtools/array/view/vector_norm.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename array_t, typename axis_t=none_t, typename keepdims_t=meta::false_type, typename ord_t=nm_index_t>
    constexpr auto vector_norm(const array_t& array, const axis_t& axis=axis_t{}, keepdims_t keepdims=keepdims_t{}, ord_t ord=ord_t{2}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::vector_norm(array,axis,keepdims,ord);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // vector_norm
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_VECTOR_NORM_HPP