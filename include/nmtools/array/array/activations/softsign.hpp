#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SOFTSIGN_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SOFTSIGN_HPP

#include "nmtools/array/view/activations/softsign.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate element-wise softsign function
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @param array     input array
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t>
    constexpr auto softsign(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::softsign(array);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // softsign
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SOFTSIGN_HPP