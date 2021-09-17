#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_HARDSWISH_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_HARDSWISH_HPP

#include "nmtools/array/view/activations/hardswish.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute element-wise hardswish ufunc.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @param array     input array
     * @param context   evalutaion context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename array_t>
    constexpr auto hardswish(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto a = view::hardswish(array);
        return eval(a,context,output);
    } // hardswish
} // namespace nmtools::array


#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_HARDSWISH_HPP