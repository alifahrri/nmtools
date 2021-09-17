#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SOFTPLUS_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SOFTPLUS_HPP

#include "nmtools/array/view/activations/softplus.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate element-wise softplus function
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam beta_t 
     * @tparam threshold_t 
     * @param array         input array
     * @param beta          the beta value of softplus formulation
     * @param threshold     values above this revert to linear function
     * @param context       evaluation context
     * @param output 
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename array_t, typename beta_t=float, typename threshold_t=float>
    NMTOOLS_UFUNC_CONSTEXPR
    auto softplus(const array_t& array, beta_t beta=beta_t{1}, threshold_t threshold=threshold_t{20},
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto a = view::softplus(array,beta,threshold);
        return eval(a,context,output);
    } // softplus
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SOFTPLUS_HPP