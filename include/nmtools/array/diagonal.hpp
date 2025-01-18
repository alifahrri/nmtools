#ifndef NMTOOLS_ARRAY_ARRAY_DIAGONAL_HPP
#define NMTOOLS_ARRAY_ARRAY_DIAGONAL_HPP

#include "nmtools/array/view/diagonal.hpp"
#include "nmtools/array/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename array_t, typename offset_t=meta::ct<0>, typename axis1_t=meta::ct<0>, typename axis2_t=meta::ct<1>>
    constexpr auto diagonal(const array_t& array, offset_t offset=offset_t{}, axis1_t axis1=axis1_t{}, axis2_t axis2=axis2_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::diagonal(array,offset,axis1,axis2);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // diagonal
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_DIAGONAL_HPP