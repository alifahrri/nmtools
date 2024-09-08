#ifndef NMTOOLS_ARRAY_ARRAY_EXPAND_HPP
#define NMTOOLS_ARRAY_ARRAY_EXPAND_HPP

#include "nmtools/array/view/expand.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly expand the contents of an array.
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
        typename array_t, typename axis_t, typename spacing_t=nm_index_t, typename fill_value_t=nm_index_t>
    constexpr auto expand(const array_t& array, const axis_t& axis, const spacing_t& spacing=spacing_t{1}, fill_value_t fill_value=fill_value_t{0},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto expanded = view::expand(array,axis,spacing,fill_value);
        return eval(expanded
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // expand
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_EXPAND_HPP