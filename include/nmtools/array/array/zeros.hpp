#ifndef NMTOOLS_ARRAY_ARRAY_ZEROS_HPP
#define NMTOOLS_ARRAY_ARRAY_ZEROS_HPP

#include "nmtools/array/view/zeros.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate zeros.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam shape_t 
     * @tparam T 
     * @param shape   Desired shape
     * @param dtype   Desired data type
     * @param context Evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename shape_t, typename T>
    constexpr auto zeros(const shape_t& shape, dtype_t<T> dtype,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto a = view::zeros(shape,dtype);
        return eval(a,context,output);
    } // zeros
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ZEROS_HPP