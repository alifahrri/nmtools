#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_TANHSHRINK_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_TANHSHRINK_HPP

#include "nmtools/array/view/activations/tanhshrink.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate element-wise tanhshrink function
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
    auto tanhshrink(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::tanhshrink(array);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // tanhshrink
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_TANHSHRINK_HPP