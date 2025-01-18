#ifndef NMTOOLS_ARRAY_ARRAY_EXPAND_DIMS_HPP
#define NMTOOLS_ARRAY_ARRAY_EXPAND_DIMS_HPP

#include "nmtools/array/view/expand_dims.hpp"
#include "nmtools/array/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly expand the shape of an array.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @param array     input array
     * @param axis      position in the expanded axes where the new axis (or axes) is placed.
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename axis_t>
    constexpr auto expand_dims(const array_t& array, axis_t axis,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto expanded = view::expand_dims(array,axis);
        return eval(expanded
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // expand_dims
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_EXPAND_DIMS_HPP