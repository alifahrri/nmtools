#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SOFTSHRINK_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SOFTSHRINK_HPP

#include "nmtools/array/view/activations/softshrink.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate element-wise sfortshrink function
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam lambda_t 
     * @param array     input array
     * @param lambda    lambda value of softshrink formulation
     * @param context 
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t,
        typename array_t, typename lambda_t=float>
    constexpr auto softshrink(const array_t& array, lambda_t lambda=lambda_t{0.5},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::softshrink(array,lambda);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // softshrink
} // namespace nmtools::array


#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SOFTSHRINK_HPP