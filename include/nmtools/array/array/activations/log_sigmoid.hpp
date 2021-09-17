#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_LOG_SIGMOID_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_LOG_SIGMOID_HPP

#include "nmtools/array/view/activations/log_sigmoid.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute element-wise log sigmoid
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @param array     input array
     * @param context   evalutation context
     * @param output 
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename array_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto log_sigmoid(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto a = view::log_sigmoid(array);
        return eval(a,context,output);
    } // log_sigmoid
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_LOG_SIGMOID_HPP