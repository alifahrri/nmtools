#ifndef NMTOOLS_ARRAY_ARRAY_TENSORDOT_HPP
#define NMTOOLS_ARRAY_ARRAY_TENSORDOT_HPP

#include "nmtools/array/view/tensordot.hpp"
#include "nmtools/array/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename lhs_t, typename rhs_t, typename axes_t=meta::ct<2>>
    constexpr auto tensordot(const lhs_t& lhs, const rhs_t& rhs, axes_t axes=axes_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::tensordot(lhs,rhs,axes);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // tensordot
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_TENSORDOT_HPP