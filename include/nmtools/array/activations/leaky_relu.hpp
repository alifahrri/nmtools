#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATION_LEAKY_RELU_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATION_LEAKY_RELU_HPP

#include "nmtools/array/view/activations/leaky_relu.hpp"
#include "nmtools/array/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute element-wise leaky relu
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam negative_slope_t 
     * @param array             input array
     * @param negative_slope    controls the angle of the negative slope
     * @param context           evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename negative_slope_t=float>
    constexpr auto leaky_relu(const array_t& array, negative_slope_t negative_slope=negative_slope_t{0.01},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::leaky_relu(array,negative_slope);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // leaky_relu
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATION_LEAKY_RELU_HPP