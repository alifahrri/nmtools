#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SOFTSHRINK_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SOFTSHRINK_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    /**
     * @brief Function object for softshrink ufunc
     * 
     * @tparam lambda_t 
     */
    template <typename lambda_t=float>
    struct softshrink_t
    {
        const lambda_t lambda = 0.5;

        template <typename T>
        constexpr auto operator()(const T& x) const
        {
            if (x > lambda) {
                return x - lambda;
            } else if (x < -lambda) {
                return x + lambda;
            } else {
                return static_cast<T>(0);
            }
        } // operator()
    }; // softshrink_t

    /**
     * @brief Create element-wise softshrink ufunc view.
     * 
     * @tparam array_t 
     * @tparam lambda_t 
     * @param array     input array
     * @param lambda    lambda value of softshrink formulation
     * @return constexpr auto 
     */
    template <typename array_t, typename lambda_t=float>
    constexpr auto softshrink(const array_t& array, lambda_t lambda=lambda_t{0.5})
    {
        return ufunc(softshrink_t{{lambda}},array);
    } // softshrink
    
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SOFTSHRINK_HPP