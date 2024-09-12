#ifndef NMTOOLS_ARRAY_ARRAY_FULL_LIKE_HPP
#define NMTOOLS_ARRAY_ARRAY_FULL_LIKE_HPP

#include "nmtools/array/view/full_like.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename array_t, typename fill_value_t, typename dtype_t=none_t>
    constexpr auto full_like(const array_t& array, fill_value_t fill_value, dtype_t dtype=dtype_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::full_like(array,fill_value,dtype);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // full_like
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_FULL_LIKE_HPP