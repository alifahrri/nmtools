#ifndef NMTOOLS_ARRAY_ARRAY_SQUEEZE_HPP
#define NMTOOLS_ARRAY_ARRAY_SQUEEZE_HPP

#include "nmtools/array/view/squeeze.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly squeeze an arrray. Removes single dimensions from the array.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @param array     input array
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t,
        typename array_t>
    constexpr auto squeeze(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto squeezed = view::squeeze(array);
        return eval(squeezed
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // reshape
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SQUEEZE_HPP