#ifndef NMTOOLS_ARRAY_ARRAY_PAD_HPP
#define NMTOOLS_ARRAY_ARRAY_PAD_HPP

#include "nmtools/array/view/pad.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly pad an array
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam pad_width_t 
     * @tparam value_t 
     * @param array     input array
     * @param pad_width number of padding to be applied to each edge of the axes.
     * @param value     constant value
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename pad_width_t, typename value_t=float>
    constexpr auto pad(const array_t& array, const pad_width_t& pad_width, value_t value=static_cast<value_t>(0),
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto padded = view::pad(array,pad_width,value);
        return eval(padded
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // pad
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_PAD_HPP