#ifndef NMTOOLS_ARRAY_ARRAY_DSTACK_HPP
#define NMTOOLS_ARRAY_ARRAY_DSTACK_HPP

#include "nmtools/array/view/dstack.hpp"
#include "nmtools/array/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename a_t, typename b_t>
    constexpr auto dstack(const a_t& a, const b_t& b
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto array = view::dstack(a,b);
        return eval(
            array
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    }
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_DSTACK_HPP