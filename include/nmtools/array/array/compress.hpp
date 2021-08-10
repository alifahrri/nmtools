#ifndef NMTOOLS_ARRAY_ARRAY_COMPRESS_HPP
#define NMTOOLS_ARRAY_ARRAY_COMPRESS_HPP

#include "nmtools/array/view/compress.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly select slices of an array along given axis.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam condition_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @param condition array that selects which entries to return. expected to have boolean element type
     * @param array     input array
     * @param axis      axis to take slices
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename condition_t, typename array_t, typename axis_t>
    constexpr auto compress(const condition_t& condition, const array_t& array, axis_t axis,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto compressed = view::compress(condition,array,axis);
        return eval(compressed,context,output);
    } // compress
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_COMPRESS_HPP