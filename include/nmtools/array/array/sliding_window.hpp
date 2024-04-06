#ifndef NMTOOLS_ARRAY_ARRAY_RESIZE_HPP
#define NMTOOLS_ARRAY_ARRAY_RESIZE_HPP

#include "nmtools/array/view/sliding_window.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename array_t, typename window_shape_t, typename axis_t=none_t>
    constexpr auto sliding_window(const array_t& array, const window_shape_t& window_shape, const axis_t& axis=axis_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto sliding_window = view::sliding_window(array,window_shape,axis);
        return eval(
            sliding_window
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // sliding_window
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_RESIZE_HPP