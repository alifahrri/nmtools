#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SILU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SILU_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/array/view/activations/sigmoid.hpp"

namespace nmtools::view
{
    /**
     * @brief Function object for silu ufunc
     * 
     */
    struct silu_t : sigmoid_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return t * sigmoid(t);
        } // operator()
    }; // silu_t

    /**
     * @brief Create element-wise Sigmoid Linear Unit (SiLU) ufunc view.
     * 
     * @tparam array_t 
     * @param array     input array
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename array_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto silu(const array_t& array)
    {
        return ufunc(silu_t{},array);
    } // silu
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SILU_HPP