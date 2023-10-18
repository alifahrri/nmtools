#ifndef NMTOOLS_ARRAY_ARRAY_SPLIT_HPP
#define NMTOOLS_ARRAY_ARRAY_SPLIT_HPP

#include "nmtools/array/view/split.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly split an array
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam index_t 
     * @tparam axis_t 
     * @param array 
     * @param indices_or_sections 
     * @param axis 
     * @param context 
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename index_t, typename axis_t>
    constexpr auto split(const array_t& array, const index_t& indices_or_sections, axis_t axis
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto split_ = view::split(array,indices_or_sections,axis);
        return apply_eval(split_
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    }
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SPLIT_HPP