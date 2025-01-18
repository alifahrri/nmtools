#ifndef NMTOOLS_ARRAY_ARRAY_WHERE_HPP
#define NMTOOLS_ARRAY_ARRAY_WHERE_HPP

#include "nmtools/array/view/where.hpp"
#include "nmtools/array/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate where view.
     *
     * The elements for the resulting array are chosen from x or y depending on condition array.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam condition_t 
     * @tparam x_t 
     * @tparam y_t 
     * @param condition condition array
     * @param x         choice array if true
     * @param y         choice array if false
     * @param context   execution context
     * @param output    optional output
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename condition_t, typename x_t, typename y_t>
    constexpr auto where(const condition_t& condition, const x_t& x, const y_t& y,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto array = view::where(condition, x, y);
        return eval(array
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // where
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_WHERE_HPP