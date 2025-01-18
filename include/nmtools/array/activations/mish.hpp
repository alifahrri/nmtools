#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_MISH_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_MISH_HPP

#include "nmtools/array/view/activations/mish.hpp"
#include "nmtools/array/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto mish(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::mish(array);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // mish
} // namespace nmtools::array


#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_MISH_HPP