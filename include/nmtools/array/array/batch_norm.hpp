#ifndef NMTOOLS_ARRAY_ARRAY_BATCH_NORM_HPP
#define NMTOOLS_ARRAY_ARRAY_BATCH_NORM_HPP

#include "nmtools/array/view/batch_norm.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
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
    template <typename output_t=none_t, typename context_t=none_t
        , typename input_t, typename mean_t, typename var_t, typename weight_t, typename bias_t, typename epsilon_t=float>
    constexpr auto batch_norm(const input_t& input, const mean_t& mean, const var_t& var, const weight_t& weight, const bias_t& bias, epsilon_t eps=epsilon_t{1e-5}
        , context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto batch_norm_ = view::batch_norm(input,mean,var,weight,bias,eps);
        return eval(batch_norm_,nmtools::forward<context_t>(context),nmtools::forward<output_t>(output));
    } // batch_norm
} // namespace nmtools::array


#endif // NMTOOLS_ARRAY_ARRAY_BATCH_NORM_HPP