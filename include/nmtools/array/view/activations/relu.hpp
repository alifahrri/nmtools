#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_RELU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_RELU_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    /**
     * @brief Function object for ufunc relu view
     * 
     */
    struct relu_t
    {
        template <typename T>
        constexpr auto operator()(const T& x) const
        {
            return static_cast<T>(x > 0? x : 0);
        } // operator()
    }; // relu_t

    /**
     * @brief Creates element-wise ufunc relu view
     * 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto relu(const array_t& array)
    {
        return ufunc(relu_t{},array);
    } // relu
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_RELU_HPP