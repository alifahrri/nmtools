#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_LOG_SIGMOID_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_LOG_SIGMOID_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for log sigmoid ufunc.
     * 
     */
    struct log_sigmoid
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            auto one = static_cast<T>(1);
            return math::log(one / (one + math::exp(-t)));
        } // operator()
    }; // log_sigmoid
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <>
    struct to_string_t<view::fun::log_sigmoid,none_t>
    {
        auto operator()(view::fun::log_sigmoid) const
        {
            nmtools_string str;

            str += "log_sigmoid";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using log_sigmoid_t = fun::log_sigmoid;

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