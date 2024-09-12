#ifndef NMTOOLS_ARRAY_ARRAY_IDENTITY_HPP
#define NMTOOLS_ARRAY_ARRAY_IDENTITY_HPP

#include "nmtools/array/view/identity.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename n_t, typename T=float>
    constexpr auto identity(n_t n, dtype_t<T> dtype=dtype_t<T>{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::identity(n,dtype);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // identity
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_IDENTITY_HPP