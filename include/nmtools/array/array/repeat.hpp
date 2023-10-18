#ifndef NMTOOLS_ARRAY_ARRAY_REPEAT_HPP
#define NMTOOLS_ARRAY_ARRAY_REPEAT_HPP

#include "nmtools/array/view/repeat.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate repeat op. Repeats elements of an array.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam repeats_t 
     * @tparam axis_t 
     * @param array     input array
     * @param repeats   the number of repetititons for each element
     * @param axis      the axis aloong which repeat values.
     * @param context   evaluation context.
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename repeats_t, typename axis_t>
    constexpr auto repeat(const array_t& array, repeats_t repeats, axis_t axis,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto repeated = view::repeat(array,repeats,axis);
        return eval(repeated
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // repeat
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_REPEAT_HPP