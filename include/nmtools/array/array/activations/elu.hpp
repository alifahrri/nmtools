#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_ELU_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_ELU_HPP

#include "nmtools/array/view/activations/elu.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute element-wise elu function.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam alpha_t 
     * @param array     input array
     * @param alpha     the alpha value in elu formulation
     * @param context   evaluation context
     * @param output 
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t,
        typename array_t, typename alpha_t=float>
    NMTOOLS_UFUNC_CONSTEXPR
    auto elu(const array_t& array, alpha_t alpha=alpha_t{1.0},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::elu(array,alpha);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // elu
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_ELU_HPP