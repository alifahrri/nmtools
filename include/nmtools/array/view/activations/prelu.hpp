#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_PRELU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_PRELU_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    /**
     * @brief Function object for prelu ufunc
     * 
     * @tparam alpha_t 
     */
    template <typename alpha_t=float>
    struct prelu_t
    {
        const alpha_t alpha = 0.25;

        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            if (t >= 0) {
                return t;
            } else {
                return alpha * t;
            }
        } // operator()
    }; // prelu_t

    /**
     * @brief Create element-wise prelu ufunc view
     * 
     * @tparam array_t 
     * @tparam alpha_t 
     * @param array     input array
     * @param alpha 
     * @return constexpr auto 
     */
    template <typename array_t, typename alpha_t=float>
    constexpr auto prelu(const array_t& array, alpha_t alpha=alpha_t{0.25})
    {
        return ufunc(prelu_t{{alpha}},array);
    } // prelu
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_PRELU_HPP