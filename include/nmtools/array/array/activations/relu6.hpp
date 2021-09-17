#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_RELU6_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_RELU6_HPP

#include "nmtools/array/view/activations/relu6.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute element-wise relu6.
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
    constexpr auto relu6(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto a = view::relu6(array);
        return eval(a,context,output);
    } // relu6
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_RELU6_HPP