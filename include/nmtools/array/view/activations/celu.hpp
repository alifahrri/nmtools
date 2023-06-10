#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_CELU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_CELU_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    /**
     * @brief Function object for ufunc celu view.
     * 
     * @tparam alpha_t 
     */
    template <typename alpha_t=float>
    struct celu_t
    {
        const alpha_t alpha = 1.0;

        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            constexpr auto zero = static_cast<T>(0);
            return math::max(zero,t) + math::min(zero,alpha*(math::exp(t / alpha)-1));
        } // operator()
    }; // celu_t

    /**
     * @brief Create element-wise celu ufunc view.
     * 
     * @tparam array_t 
     * @tparam alpha_t 
     * @param array     input array
     * @param alpha     the alpha value in the celu formulation.
     * @return 
     */
    template <typename array_t, typename alpha_t=float>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto celu(const array_t& array, alpha_t alpha=alpha_t{1.0})
    {
        return ufunc(celu_t<alpha_t>{{alpha}},array);
    } // celu
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_CELU_HPP