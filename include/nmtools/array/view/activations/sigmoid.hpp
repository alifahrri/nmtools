#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SIGMOID_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SIGMOID_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    /**
     * @brief Function object for sigmoid ufunc
     * 
     */
    struct sigmoid_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        static auto sigmoid(const T& t)
        {
            auto one = static_cast<T>(1);
            return one / (one + math::exp(-t));
        } // sigmoid

        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return sigmoid(t);
        } // operator()
    }; // sigmoid_t

    /**
     * @brief Create element-wise sigmoid ufunc view
     * 
     * @tparam array_t 
     * @param array     input array
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename array_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto sigmoid(const array_t& array)
    {
        return ufunc(sigmoid_t{},array);
    } // sigmoid
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SIGMOID_HPP