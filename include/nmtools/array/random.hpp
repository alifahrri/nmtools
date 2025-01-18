#ifndef NMTOOLS_ARRAY_ARRAY_RANDOM_HPP
#define NMTOOLS_ARRAY_ARRAY_RANDOM_HPP

#include "nmtools/array/view/random.hpp"
#include "nmtools/array/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename shape_t, typename T, typename generator_t>
    constexpr auto random(const shape_t& shape, dtype_t<T> dtype, generator_t& generator,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::random(shape, dtype, generator);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // random
}

#endif // NMTOOLS_ARRAY_ARRAY_RANDOM_HPP