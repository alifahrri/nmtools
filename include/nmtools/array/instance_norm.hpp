#ifndef NMTOOLS_ARRAY_ARRAY_INSTANCE_NORM_HPP
#define NMTOOLS_ARRAY_ARRAY_INSTANCE_NORM_HPP

#include "nmtools/array/view/instance_norm.hpp"
#include "nmtools/array/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename input_t, typename weight_t, typename bias_t, typename nd_t, typename epsilon_t=float>
    constexpr auto instance_norm(const input_t& input, const weight_t& weight, const bias_t& bias, nd_t nd, epsilon_t epsilon=epsilon_t{1e-5}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto instance_norm = view::instance_norm(input,weight,bias,nd,epsilon);
        return eval(instance_norm
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // instance_norm

    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename input_t, typename weight_t, typename bias_t, typename epsilon_t=float>
    constexpr auto instance_norm_1d(const input_t& input, const weight_t& weight, const bias_t& bias, epsilon_t epsilon=epsilon_t{1e-5}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto instance_norm = view::instance_norm_1d(input,weight,bias,epsilon);
        return eval(instance_norm
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // instance_norm_1d

    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename input_t, typename weight_t, typename bias_t, typename epsilon_t=float>
    constexpr auto instance_norm_2d(const input_t& input, const weight_t& weight, const bias_t& bias, epsilon_t epsilon=epsilon_t{1e-5}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto instance_norm = view::instance_norm_2d(input,weight,bias,epsilon);
        return eval(instance_norm
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // instance_norm_2d

    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename input_t, typename weight_t, typename bias_t, typename epsilon_t=float>
    constexpr auto instance_norm_3d(const input_t& input, const weight_t& weight, const bias_t& bias, epsilon_t epsilon=epsilon_t{1e-5}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto instance_norm = view::instance_norm_3d(input,weight,bias,epsilon);
        return eval(instance_norm
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // instance_norm_3d
}

#endif // NMTOOLS_ARRAY_ARRAY_INSTANCE_NORM_HPP