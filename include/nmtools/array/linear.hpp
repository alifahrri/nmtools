#ifndef NMTOOLS_ARRAY_VIEW_LINEAR_HPP
#define NMTOOLS_ARRAY_VIEW_LINEAR_HPP

#include "nmtools/core/alias.hpp"
#include "nmtools/array/tensordot.hpp"
#include "nmtools/array/ufuncs/add.hpp"

namespace nmtools::view
{
    template <typename input_t, typename weight_t, typename bias_t=none_t>
    constexpr auto linear(const input_t& input, const weight_t& weight, const bias_t& bias=bias_t{})
    {
        auto axes = nmtools_tuple{
            nmtools_tuple{meta::ct_v<-1>}
            , nmtools_tuple{meta::ct_v<-1>}
        };
        if constexpr (is_none_v<bias_t>) {
            return view::tensordot(input,weight,axes);
        } else {
            auto aliased  = view::aliased(input,weight,bias);
            auto a_input  = nmtools::get<0>(aliased);
            auto a_weight = nmtools::get<1>(aliased);
            auto a_bias   = nmtools::get<2>(aliased);
            return view::add(view::tensordot(a_input,a_weight,axes), a_bias);
        }
    } // linear
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_LINEAR_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_LINEAR_HPP
#define NMTOOLS_ARRAY_ARRAY_LINEAR_HPP

#include "nmtools/array/linear.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename input_t, typename weight_t, typename bias_t=none_t>
    constexpr auto linear(const input_t& input, const weight_t& weight, const bias_t& bias=bias_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::linear(input,weight,bias);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // linear
} // nmtools

#endif // NMTOOLS_ARRAY_ARRAY_LINEAR_HPP