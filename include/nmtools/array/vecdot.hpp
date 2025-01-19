#ifndef NMTOOLS_ARRAY_VIEW_VECDOT_HPP
#define NMTOOLS_ARRAY_VIEW_VECDOT_HPP

#include "nmtools/core/decorator.hpp"
#include "nmtools/core/alias.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/sum.hpp"

namespace nmtools::view
{
    template <typename lhs_t, typename rhs_t, typename dtype_t=none_t, typename keepdims_t=meta::false_type>
    constexpr auto vecdot(const lhs_t& lhs, const rhs_t& rhs, dtype_t dtype=dtype_t{}, keepdims_t keepdims=keepdims_t{})
    {
        auto aliased = view::aliased(lhs,rhs);

        auto a_lhs = nmtools::get<0>(aliased);
        auto a_rhs = nmtools::get<1>(aliased);

        auto axis = meta::ct_v<-1>;
        auto initial = None;

        return view::sum(
            view::multiply(a_lhs,a_rhs)
            , axis
            , dtype
            , initial
            , keepdims
        );
    } // vecdot
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_VECDOT_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_VECDOT_HPP
#define NMTOOLS_ARRAY_ARRAY_VECDOT_HPP

#include "nmtools/array/vecdot.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename lhs_t, typename rhs_t, typename dtype_t=none_t, typename keepdims_t=meta::false_type>
    constexpr auto vecdot(const lhs_t& lhs, const rhs_t& rhs, dtype_t dtype=dtype_t{}, keepdims_t keepdims=keepdims_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::vecdot(lhs,rhs,dtype,keepdims);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // vecdot
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_VECDOT_HPP