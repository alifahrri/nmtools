#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_RELU_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_RELU_HPP

#include "nmtools/array/view/activations/relu.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute element-wise relu.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @param array     input array
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename array_t>
    constexpr auto relu(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto a = view::relu(array);
        return eval(a,context,output);
    } // relu
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_RELU_HPP