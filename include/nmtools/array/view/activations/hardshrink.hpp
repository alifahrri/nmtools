#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATION_HARDSHRINK_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATION_HARDSHRINK_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    /**
     * @brief Function object for hardshrink ufunc.
     * 
     * @tparam lambda_t 
     */
    template <typename lambda_t=float>
    struct hardshrink_t
    {
        const lambda_t lambda = 0.5;

        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            auto x = t;
            if ((x >= -lambda) && (x <= lambda)) {
                x = 0;
            }
            return x;
        } // operator()
    }; // hardshrink_t

    /**
     * @brief Creates element-wise hardshrink ufunc view.
     * 
     * @tparam array_t 
     * @tparam lambda_t 
     * @param array 
     * @param lambda 
     * @return constexpr auto 
     */
    template <typename array_t, typename lambda_t=float>
    constexpr auto hardshrink(const array_t& array, lambda_t lambda=lambda_t{0.5})
    {
        return ufunc(hardshrink_t{{lambda}},array);
    } // hardshrink
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATION_HARDSHRINK_HPP