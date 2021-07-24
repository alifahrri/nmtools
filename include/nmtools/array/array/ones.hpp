#ifndef NMTOOLS_ARRAY_ARRAY_ONES_HPP
#define NMTOOLS_ARRAY_ARRAY_ONES_HPP

#include "nmtools/array/view/ones.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute ones.
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
    constexpr auto ones(const shape_t& shape, dtype_t<T> dtype,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto a = view::ones(shape,dtype);
        return eval(a,context,output);
    } // ones
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ONES_HPP