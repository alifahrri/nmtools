#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_PRELU_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_PRELU_HPP

#include "nmtools/array/view/activations/prelu.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate element-wise prelu
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam alpha_t 
     * @param array     input array
     * @param alpha     negative slope of prelu
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t,
        typename array_t, typename alpha_t=float>
    constexpr auto prelu(const array_t& array, alpha_t alpha=alpha_t{0.25},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::prelu(array,alpha);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // prelu
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_PRELU_HPP