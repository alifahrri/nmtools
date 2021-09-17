#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SOFTPLUS_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SOFTPLUS_HPP

#include "nmtools/array/view/ufunc.hpp"
#include <cmath>

namespace nmtools::view
{
    /**
     * @brief Function object for softplus ufunc
     * 
     * @tparam beta_t 
     * @tparam threshold_t 
     */
    template <typename beta_t=float, typename threshold_t=float>
    struct softplus_t
    {
        const beta_t beta = 1;
        const threshold_t threshold = 20;

        template <typename beta_type=float, typename threshold_type=float, typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        static auto softplus(const T& x, beta_type beta=beta_type{1}, threshold_type threshold=threshold_type{20})
        {
            auto t_times_beta = x * beta;
            if (t_times_beta > threshold) {
                return x;
            } else {
                return std::log(1 + std::exp(t_times_beta)) / beta;
            }
        } // softplus

        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& x) const
        {
            return softplus(x,beta,threshold);
        } // operator()
    }; // softplus_t

    template <typename beta_t, typename threshold_t>
    softplus_t(beta_t,threshold_t) -> softplus_t<beta_t,threshold_t>;

    /**
     * @brief Create element-wise softplus ufunc view.
     * 
     * @tparam array_t 
     * @tparam beta_t 
     * @tparam threshold_t 
     * @param array     input array
     * @param beta      the beta value of softplus formulation
     * @param threshold values above this revert to linear function
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename array_t, typename beta_t=float, typename threshold_t=float>
    NMTOOLS_UFUNC_CONSTEXPR
    auto softplus(const array_t& array, beta_t beta=beta_t{1}, threshold_t threshold=threshold_t{20})
    {
        return ufunc(softplus_t{beta,threshold},array);
    } // softplus

} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SOFTPLUS_HPP