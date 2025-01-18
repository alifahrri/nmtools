#ifndef NMTOOLS_ARRAY_ARRAY_FLIP_HPP
#define NMTOOLS_ARRAY_ARRAY_FLIP_HPP

#include "nmtools/array/core/eval.hpp"
#include "nmtools/array/view/flip.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate flip
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @param array array to be flipped
     * @param axis axis to operate on
     * @param context exectution context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename axis_t>
    constexpr auto flip(const array_t& array, const axis_t& axis,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto flipped = view::flip(array,axis);
        return eval(flipped
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // flip

    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t>
    constexpr auto fliplr(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto flipped = view::fliplr(array);
        return eval(flipped
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // fliplr

    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t>
    constexpr auto flipud(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto flipped = view::flipud(array);
        return eval(flipped
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // flipud
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_FLIP_HPP