#ifndef NMTOOLS_ARRAY_ARRAY_LAYER_NORM_HPP
#define NMTOOLS_ARRAY_ARRAY_LAYER_NORM_HPP

#include "nmtools/array/view/layer_norm.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename input_t, typename weight_t, typename bias_t, typename epsilon_t=float>
    constexpr auto layer_norm(const input_t& input, const weight_t& weight, const bias_t& bias, epsilon_t epsilon=epsilon_t{1e-5}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto layer_norm = view::layer_norm(input,weight,bias,epsilon);
        return eval(layer_norm
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // layer_norm
}

#endif // NMTOOLS_ARRAY_ARRAY_LAYER_NORM_HPP