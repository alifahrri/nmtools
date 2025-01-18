#ifndef NMTOOLS_ARRAY_ARRAY_RESIZE_HPP
#define NMTOOLS_ARRAY_ARRAY_RESIZE_HPP

#include "nmtools/array/view/resize.hpp"
#include "nmtools/array/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename dst_shape_t>
    constexpr auto resize(const array_t& array, const dst_shape_t& dst_shape,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto resized = view::resize(array,dst_shape);
        return eval(resized
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // resize
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_RESIZE_HPP