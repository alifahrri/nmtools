#ifndef NMTOOLS_ARRAY_ARRAY_SOFTMAX_HPP
#define NMTOOLS_ARRAY_ARRAY_SOFTMAX_HPP

#include "nmtools/array/view/softmax.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly computes softmax function along an axis.
     * 
     * @tparam output_t 
     * @tparam context_t=none_t 
     * @tparam input_t 
     * @tparam dim_t 
     * @param input     input array
     * @param dim       axis to operate softmax
     * @param context 
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename input_t, typename dim_t>
    constexpr auto softmax(const input_t& input, dim_t dim,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto softmax_ = view::softmax(input,dim);
        return eval(softmax_
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // softmax
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SOFTMAX_HPP