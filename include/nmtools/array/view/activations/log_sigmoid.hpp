#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_LOG_SIGMOID_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_LOG_SIGMOID_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    /**
     * @brief Function object for log sigmoid ufunc.
     * 
     */
    struct log_sigmoid_t
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            auto one = static_cast<T>(1);
            return math::log(one / (one + math::exp(-t)));
        } // operator()
    }; // log_sigmoid_t

    /**
     * @brief Create element-wise log sigmoid ufunc view.
     * 
     * @tparam array_t 
     * @param array     input array
     * @return  
     */
    template <typename array_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto log_sigmoid(const array_t& array)
    {
        return ufunc(log_sigmoid_t{}, array);
    } // log_sigmoid
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_LOG_SIGMOID_HPP