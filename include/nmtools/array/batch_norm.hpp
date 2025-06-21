#ifndef NMTOOLS_ARRAY_VIEW_BATCH_NORM_HPP
#define NMTOOLS_ARRAY_VIEW_BATCH_NORM_HPP

#include "nmtools/array/atleast_nd.hpp"
#include "nmtools/array/moveaxis.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufuncs/sqrt.hpp"

#include "nmtools/meta.hpp"

namespace nmtools::view
{
    /**
     * @brief create a view that applies Batch Normalization for each channel across a batch of data.
     * 
     * @tparam input_t 
     * @tparam mean_t 
     * @tparam var_t 
     * @tparam weight_t 
     * @tparam bias_t 
     * @tparam epsilon_t 
     * @param input     input array with shape (N,C,H,W)
     * @param mean      (estimated) mean array with shape (C)
     * @param var       (estimated) var array with shape (C)
     * @param weight    a.k.a. scale with shape (C)
     * @param bias      bias with shape (C)
     * @param eps       epsilon value to use to avoid division by zero.
     * @return constexpr auto 
     */
    template <typename input_t, typename mean_t, typename var_t, typename weight_t, typename bias_t, typename epsilon_t=float>
    constexpr auto batch_norm(const input_t& input, const mean_t& mean, const var_t& var, const weight_t& weight, const bias_t& bias, epsilon_t eps=epsilon_t{1e-5})
    {
        // assume only 2D for now
        // TODO: support 1D & 3D
        // assume NCHW or CHW
        // TODO: support NHWC

        auto src_axis = meta::ct_v<-1>;
        auto dst_axis = meta::ct_v<-3>;

        auto aliased  = view::aliased(input,mean,var,weight,bias,eps);
        // TODO: propagate error handling, aliased may return maybe<tuple<...>> if any of its input is maybe
        auto a_input  = nmtools::get<0>(unwrap(aliased));
        auto a_mean   = nmtools::get<1>(unwrap(aliased));
        auto a_var    = nmtools::get<2>(unwrap(aliased));
        auto a_weight = nmtools::get<3>(unwrap(aliased));
        auto a_bias   = nmtools::get<4>(unwrap(aliased));
        auto a_eps    = nmtools::get<5>(unwrap(aliased));

        auto weight_ = view::moveaxis(view::atleast_nd(a_weight,meta::ct_v<3>),src_axis,dst_axis);
        auto bias_   = view::moveaxis(view::atleast_nd(a_bias,meta::ct_v<3>),src_axis,dst_axis);
        auto mean_   = view::moveaxis(view::atleast_nd(a_mean,meta::ct_v<3>),src_axis,dst_axis);
        auto var_    = view::moveaxis(view::atleast_nd(a_var,meta::ct_v<3>),src_axis,dst_axis);
        auto stddev_ = view::sqrt(view::add(var_,a_eps));

        auto subtracted = view::subtract(a_input,mean_);
        auto divided    = view::divide(subtracted,stddev_);
        auto multiplied = view::multiply(divided,weight_);
        return view::add(multiplied,bias_);
    } // batch_norm
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_BATCH_NORM_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_BATCH_NORM_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_BATCH_NORM_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/moveaxis.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufuncs/sqrt.hpp"
#include "nmtools/array/batch_norm.hpp"

namespace nmtools::functional
{
    constexpr inline auto batch_norm_fun = [](const auto&...args){
        return view::batch_norm(args...);
    };

    constexpr inline auto batch_norm = functor_t{quinary_fmap_t<decltype(batch_norm_fun)>{{batch_norm_fun}}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_BATCH_NORM_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_BATCH_NORM_HPP
#define NMTOOLS_ARRAY_ARRAY_BATCH_NORM_HPP

#include "nmtools/array/batch_norm.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly compute batch_norm.
     * 
     * @tparam output_t 
     * @tparam context_t=none_t 
     * @tparam input_t 
     * @tparam mean_t 
     * @tparam var_t 
     * @tparam weight_t 
     * @tparam bias_t 
     * @tparam epsilon_t 
     * @param input     input array with shape (N,C,H,W)
     * @param mean      (estimated) mean array with shape (C)
     * @param var       (estimated) var array with shape (C)
     * @param weight    a.k.a. scale with shape (C)
     * @param bias      bias with shape (C)
     * @param eps       epsilon value to use to avoid division by zero.
     * @param context 
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename input_t, typename mean_t, typename var_t, typename weight_t, typename bias_t, typename epsilon_t=float>
    constexpr auto batch_norm(const input_t& input, const mean_t& mean, const var_t& var, const weight_t& weight, const bias_t& bias, epsilon_t eps=epsilon_t{1e-5}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto batch_norm_ = view::batch_norm(input,mean,var,weight,bias,eps);
        return eval(batch_norm_
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // batch_norm
} // namespace nmtools


#endif // NMTOOLS_ARRAY_ARRAY_BATCH_NORM_HPP