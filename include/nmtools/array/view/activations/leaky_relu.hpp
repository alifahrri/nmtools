#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_LEAKY_RELU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_LEAKY_RELU_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    /**
     * @brief Function object for leaky relu ufunc
     * 
     * @tparam negative_slope_t 
     */
    template <typename negative_slope_t=float>
    struct leaky_relu_t
    {
        const negative_slope_t negative_slope = 0.01;

        template <typename T>
        constexpr auto operator()(const T& t) const -> T
        {
            return (t >= 0? t : negative_slope * t);
        } // operator()
    }; // leaky_relu_t

    /**
     * @brief Create element-wise leaky relu ufunc view.
     * 
     * @tparam array_t 
     * @tparam negative_slope_t 
     * @param array             input array
     * @param negative_slope    controls the angle of the negative slope
     * @return constexpr auto 
     */
    template <typename array_t, typename negative_slope_t=float>
    constexpr auto leaky_relu(const array_t& array, negative_slope_t negative_slope=negative_slope_t{0.01})
    {
        return ufunc(leaky_relu_t<negative_slope_t>{{negative_slope}},array);
    } // leaky_relu
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_LEAKY_RELU_HPP