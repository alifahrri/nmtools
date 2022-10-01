#ifndef NMTOOLS_ARRAY_ARRAY_TAKE_HPP
#define NMTOOLS_ARRAY_ARRAY_TAKE_HPP

#include "nmtools/array/view/take.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate take op.
     * 
     * Take elements from an array along an axis.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam indices_t 
     * @tparam axis_t 
     * @param array     input array
     * @param indices   the indices of elements to be extracted
     * @param axis      which axis to take element
     * @param context   evaluation context
     * @param output    optional outptu
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t,
        typename array_t, typename indices_t, typename axis_t>
    constexpr auto take(const array_t& array, const indices_t& indices, axis_t axis,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto array_ = view::take(array,indices,axis);
        return eval(array_
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // take
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_TAKE_HPP