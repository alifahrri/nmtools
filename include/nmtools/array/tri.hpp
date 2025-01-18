#ifndef NMTOOLS_ARRAY_ARRAY_TRI_HPP
#define NMTOOLS_ARRAY_ARRAY_TRI_HPP

#include "nmtools/array/view/tri.hpp"
#include "nmtools/array/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename n_t, typename m_t=none_t, typename k_t=nm_index_t, typename T=float>
    constexpr auto tri(n_t N, m_t M=m_t{}, k_t k=k_t{0}, dtype_t<T> dtype=dtype_t<T>{}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::tri(N,M,k,dtype);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // tri
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_TRI_HPP