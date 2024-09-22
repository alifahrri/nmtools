#ifndef NMTOOLS_ARRAY_ARRAY_SWAPAXES_HPP
#define NMTOOLS_ARRAY_ARRAY_SWAPAXES_HPP

#include "nmtools/array/view/swapaxes.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename array_t, typename axis1_t, typename axis2_t>
    constexpr auto swapaxes(const array_t& array, axis1_t axis1, axis2_t axis2
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::swapaxes(array,axis1,axis2);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    }
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SWAPAXES_HPP