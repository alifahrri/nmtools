#ifndef NMTOOLS_ARRAY_ARRAY_VECDOT_HPP
#define NMTOOLS_ARRAY_ARRAY_VECDOT_HPP

#include "nmtools/array/view/vecdot.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename lhs_t, typename rhs_t, typename dtype_t=none_t, typename keepdims_t=meta::false_type>
    constexpr auto vecdot(const lhs_t& lhs, const rhs_t& rhs, dtype_t dtype=dtype_t{}, keepdims_t keepdims=keepdims_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::vecdot(lhs,rhs,dtype,keepdims);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // vecdot
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_VECDOT_HPP