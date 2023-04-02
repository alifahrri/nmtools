#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_ELU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_ELU_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    /**
     * @brief Function object for ELU ufunc.
     * 
     * @tparam alpha_t 
     */
    template <typename alpha_t=float>
    struct elu_t
    {
        const alpha_t alpha = 1.0;

        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return (t > 0? t : alpha * (math::exp(t)-1));
        } // operator()
    }; // elu_t

    /**
     * @brief Create element-wise ELU ufunc view.
     * 
     * @tparam array_t 
     * @tparam alpha_t 
     * @param array     input array
     * @param alpha     the alpha value of ELU formulation.
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename array_t, typename alpha_t=float>
    NMTOOLS_UFUNC_CONSTEXPR
    auto elu(const array_t& array, alpha_t alpha=alpha_t{1})
    {
        return ufunc(elu_t<alpha_t>{{alpha}}, array);
    } // elu
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_ELU_HPP