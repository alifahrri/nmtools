#ifndef NMTOOLS_ARRAY_ARRAY_DIAGFLAT_HPP
#define NMTOOLS_ARRAY_ARRAY_DIAGFLAT_HPP

#include "nmtools/array/view/diagflat.hpp"
#include "nmtools/array/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename array_t, typename k_t=nm_index_t>
    constexpr auto diagflat(const array_t& array, k_t k=k_t{0}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::diagflat(array,k);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // diagflat
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_DIAGFLAT_HPP