#ifndef NMTOOLS_ARRAY_VIEW_OUTER_HPP
#define NMTOOLS_ARRAY_VIEW_OUTER_HPP

#include "nmtools/core/alias.hpp"
#include "nmtools/array/flatten.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"

namespace nmtools::view
{
    template <typename lhs_t, typename rhs_t>
    constexpr auto outer(const lhs_t& lhs, const rhs_t& rhs)
    {
        auto aliased = view::aliased(lhs,rhs);
        auto flat_lhs = view::flatten(nmtools::get<0>(aliased));
        auto flat_rhs = view::flatten(nmtools::get<1>(aliased));

        return view::multiply(
            view::reshape(flat_lhs,nmtools_tuple{meta::ct_v<-1>,meta::ct_v<1>})
            , flat_rhs
        );
    }
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_OUTER_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_OUTER_HPP
#define NMTOOLS_ARRAY_ARRAY_OUTER_HPP

#include "nmtools/array/outer.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename lhs_t, typename rhs_t>
    constexpr auto outer(const lhs_t& lhs, const rhs_t& rhs
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::outer(lhs,rhs);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // outer
}

#endif // NMTOOLS_ARRAY_ARRAY_OUTER_HPP