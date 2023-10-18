#ifndef NMTOOLS_ARRAY_ARRAY_SOFTMIN_HPP
#define NMTOOLS_ARRAY_ARRAY_SOFTMIN_HPP

#include "nmtools/array/view/softmin.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly computes softmin function along an axis.
     * 
     * @tparam output_t 
     * @tparam context_t=none_t 
     * @tparam input_t 
     * @tparam dim_t 
     * @param input     input array
     * @param dim       compute axis
     * @param context 
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename input_t, typename dim_t>
    constexpr auto softmin(const input_t& input, dim_t dim,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto softmin_ = view::softmin(input,dim);
        return eval(softmin_
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // softmin
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SOFTMIN_HPP