#ifndef NMTOOLS_ARRAY_ARRAY_CONV_HPP
#define NMTOOLS_ARRAY_ARRAY_CONV_HPP

#include "nmtools/array/view/conv.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly applies 2D convolution over an input image composed of several input channels.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam input_t 
     * @tparam weight_t 
     * @tparam bias_t 
     * @tparam stride_t 
     * @tparam padding_t 
     * @tparam dilation_t 
     * @param input     input array with format NCHW or CHW
     * @param weight    filters of shape with format (OutC,C,k_h,k_w)
     * @param bias      optional bias, can be either index array or num
     * @param stride    optional stride, can be either index array or num
     * @param padding   optional padding, can be either index array or num
     * @param dilation  
     * @param context 
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename input_t, typename weight_t, typename bias_t=none_t, typename stride_t=none_t, typename padding_t=none_t, typename dilation_t=none_t>
    constexpr auto conv2d(const input_t& input, const weight_t& weight, const bias_t& bias=bias_t{}, const stride_t& stride=stride_t{}
        , [[maybe_unused]] const padding_t& padding=padding_t{}, const dilation_t& dilation=dilation_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto conv2d_ = view::conv2d(input,weight,bias,stride,padding,dilation);
        return eval(conv2d_
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // conv2d
} // namespace nmtools::array


#endif // NMTOOLS_ARRAY_ARRAY_CONV_HPP