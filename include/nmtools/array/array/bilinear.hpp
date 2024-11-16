#ifndef NMTOOLS_ARRAY_ARRAY_BILINEAR_HPP
#define NMTOOLS_ARRAY_ARRAY_BILINEAR_HPP

#include "nmtools/array/view/bilinear.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename lhs_t, typename rhs_t, typename weight_t, typename bias_t=none_t>
    constexpr auto bilinear(const lhs_t& lhs, const rhs_t& rhs, const weight_t& weight, const bias_t& bias=bias_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::bilinear(lhs,rhs,weight,bias);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // bilinear
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_BILINEAR_HPP