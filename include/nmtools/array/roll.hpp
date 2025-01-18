#ifndef NMTOOLS_ARRAY_ARRAY_ROLL_HPP
#define NMTOOLS_ARRAY_ARRAY_ROLL_HPP

#include "nmtools/array/view/roll.hpp"
#include "nmtools/array/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename array_t
        , typename shift_t
        , typename axis_t=none_t>
    constexpr auto roll(const array_t& array, const shift_t& shift, const axis_t& axis=axis_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto rolled = view::roll(array,shift,axis);
        return eval(
            rolled
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // roll
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ROLL_HPP