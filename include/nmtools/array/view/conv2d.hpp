#ifndef NMTOOLS_ARRAY_VIEW_CONV2D_HPP
#define NMTOOLS_ARRAY_VIEW_CONV2D_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/convnd.hpp"

namespace nmtools::view
{
    template <typename input_t, typename weight_t, typename bias_t=none_t
        , typename stride_t=none_t, typename padding_t=none_t, typename dilation_t=none_t, typename groups_t=meta::ct<1>>
    constexpr auto conv2d(const input_t& input, const weight_t& weight, const bias_t& bias=bias_t{}
        , const stride_t& stride=stride_t{}, const padding_t& padding=padding_t{}, const dilation_t& dilation=dilation_t{}, groups_t groups=groups_t{})
    {
        constexpr auto n_planes = meta::ct_v<2>;
        return view::convnd(n_planes,input,weight,bias,stride,padding,dilation,groups);
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_CONV2D_HPP