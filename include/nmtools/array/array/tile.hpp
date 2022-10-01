#ifndef NMTOOLS_ARRAY_ARRAY_TILE_HPP
#define NMTOOLS_ARRAY_ARRAY_TILE_HPP

#include "nmtools/array/view/tile.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate tile op.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam reps_t 
     * @param array     input array
     * @param reps      number of repetitions
     * @param context   evaluation context
     * @param output    optional output
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t,
        typename array_t, typename reps_t>
    constexpr auto tile(const array_t& array, const reps_t& reps,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto tiled = view::tile(array,reps);
        return eval(tiled
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // tile
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_TILE_HPP