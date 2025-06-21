#ifndef NMTOOLS_ARRAY_VIEW_CONV2D_HPP
#define NMTOOLS_ARRAY_VIEW_CONV2D_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/convnd.hpp"

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

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_CONV2D_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_CONV2D_HPP

#include "nmtools/array/sliding_window.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/expand.hpp"
#include "nmtools/array/pad.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/array/conv2d.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct conv2d_bias
        {
            template <typename array_t, typename weight_t, typename bias_t, typename...args_t>
            constexpr auto operator()(const array_t& array, const weight_t& weight, const bias_t& bias, const args_t&...args) const
            {
                return view::conv2d(array,weight,bias,args...);
            }
        };

        struct conv2d
        {
            template <typename array_t, typename weight_t, typename...args_t>
            constexpr auto operator()(const array_t& array, const weight_t& weight, const args_t&...args) const
            {
                return view::conv2d(array,weight,None,args...);
            }
        };
    } // namespace fun

    constexpr inline auto conv2d = functor_t{binary_fmap_t<fun::conv2d>{}};

    constexpr inline auto conv2d_bias = functor_t{ternary_fmap_t<fun::conv2d_bias>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_CONV2D_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_CONV2D_HPP
#define NMTOOLS_ARRAY_ARRAY_CONV2D_HPP

#include "nmtools/array/conv2d.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename input_t, typename weight_t, typename bias_t=none_t
        , typename stride_t=none_t, typename padding_t=none_t, typename dilation_t=none_t, typename groups_t=meta::ct<1>>
    constexpr auto conv2d(const input_t& input, const weight_t& weight, const bias_t& bias=bias_t{}
        , const stride_t& stride=stride_t{}, const padding_t& padding=padding_t{}, const dilation_t& dilation=dilation_t{}, groups_t groups=groups_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto result = view::conv2d(input,weight,bias,stride,padding,dilation,groups);
        return eval(result
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    }
}

#endif // NMTOOLS_ARRAY_ARRAY_CONV2D_HPP