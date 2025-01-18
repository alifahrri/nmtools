#ifndef NMTOOLS_ARRAY_ARRAY_ONES_LIKE_HPP
#define NMTOOLS_ARRAY_ARRAY_ONES_LIKE_HPP

#include "nmtools/array/view/ones_like.hpp"
#include "nmtools/array/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename array_t, typename dtype_t=none_t>
    constexpr auto ones_like(const array_t& array, dtype_t dtype=dtype_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::ones_like(array,dtype);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // ones_like
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ONES_LIKE_HPP