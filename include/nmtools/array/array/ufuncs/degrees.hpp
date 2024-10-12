#ifndef NMTOOLS_ARRAY_ARRAY_UFUNCS_DEGREES_HPP
#define NMTOOLS_ARRAY_ARRAY_UFUNCS_DEGREES_HPP

#include "nmtools/array/view/ufuncs/degrees.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename array_t>
    constexpr auto degrees(const array_t& array
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::degrees(array);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    }
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_UFUNCS_DEGREES_HPP