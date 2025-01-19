#ifndef NMTOOLS_ARRAY_VIEW_CONV3D_HPP
#define NMTOOLS_ARRAY_VIEW_CONV3D_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/convnd.hpp"

namespace nmtools::view
{
    template <typename input_t, typename weight_t, typename bias_t=none_t
        , typename stride_t=none_t, typename padding_t=none_t, typename dilation_t=none_t, typename groups_t=meta::ct<1>>
    constexpr auto conv3d(const input_t& input, const weight_t& weight, const bias_t& bias=bias_t{}
        , const stride_t& stride=stride_t{}, const padding_t& padding=padding_t{}, const dilation_t& dilation=dilation_t{}, groups_t groups=groups_t{})
    {
        constexpr auto n_planes = meta::ct_v<3>;
        return view::convnd(n_planes,input,weight,bias,stride,padding,dilation,groups);
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_CONV3D_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_CONV3D_HPP
#define NMTOOLS_ARRAY_ARRAY_CONV3D_HPP

#include "nmtools/array/conv3d.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename input_t, typename weight_t, typename bias_t=none_t
        , typename stride_t=none_t, typename padding_t=none_t, typename dilation_t=none_t, typename groups_t=meta::ct<1>>
    constexpr auto conv3d(const input_t& input, const weight_t& weight, const bias_t& bias=bias_t{}
        , const stride_t& stride=stride_t{}, const padding_t& padding=padding_t{}, const dilation_t& dilation=dilation_t{}, groups_t groups=groups_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto result = view::conv3d(input,weight,bias,stride,padding,dilation,groups);
        return eval(result
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    }
}

#endif // NMTOOLS_ARRAY_ARRAY_CONV3D_HPP