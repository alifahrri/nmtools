#ifndef NMTOOLS_ARRAY_ARRAY_TRIL_HPP
#define NMTOOLS_ARRAY_ARRAY_TRIL_HPP

#include "nmtools/array/view/tril.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename k_t=nm_size_t>
    constexpr auto tril(const array_t& array, k_t k=k_t{0}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>
    ) {
        auto a = view::tril(array,k);
        return eval(a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // tril
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_TRIL_HPP