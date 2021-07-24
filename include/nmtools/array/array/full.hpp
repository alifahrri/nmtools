#ifndef NMTOOLS_ARRAY_ARRAY_FULL_HPP
#define NMTOOLS_ARRAY_ARRAY_FULL_HPP

#include "nmtools/array/view/full.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute full.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam shape_t 
     * @tparam fill_value_t 
     * @param shape      Desired shape
     * @param fill_value Fill value
     * @param context    Evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename shape_t, typename fill_value_t>
    constexpr auto full(const shape_t& shape, fill_value_t fill_value,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto a = view::full(shape,fill_value);
        return eval(a,context,output);
    } // full
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_FULL_HPP