#ifndef NMTOOLS_ARRAY_ARRAY_CONV1D_HPP
#define NMTOOLS_ARRAY_ARRAY_CONV1D_HPP

#include "nmtools/array/view/conv1d.hpp"
#include "nmtools/array/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename input_t, typename weight_t, typename bias_t=none_t
        , typename stride_t=none_t, typename padding_t=none_t, typename dilation_t=none_t, typename groups_t=meta::ct<1>>
    constexpr auto conv1d(const input_t& input, const weight_t& weight, const bias_t& bias=bias_t{}
        , const stride_t& stride=stride_t{}, const padding_t& padding=padding_t{}, const dilation_t& dilation=dilation_t{}, groups_t groups=groups_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto result = view::conv1d(input,weight,bias,stride,padding,dilation,groups);
        return eval(result
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    }
}

#endif // NMTOOLS_ARRAY_ARRAY_CONV1D_HPP