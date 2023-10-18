#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SIGMOID_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SIGMOID_HPP

#include "nmtools/array/view/activations/sigmoid.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate element-wise sigmoid function.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @param array     input array
     * @param context   evaluation context
     * @param output 
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto sigmoid(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::sigmoid(array);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // sigmoid
} // namespace nmtools::array


#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SIGMOID_HPP