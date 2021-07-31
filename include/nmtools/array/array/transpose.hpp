#ifndef NMTOOLS_ARRAY_ARRAY_TRANSPOSE_HPP
#define NMTOOLS_ARRAY_ARRAY_TRANSPOSE_HPP

#include "nmtools/array/view/transpose.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate transpose op
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam axes_t 
     * @param array     input array
     * @param axes      transpose axes
     * @param context   evaluation context
     * @param output    optional output
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename array_t, typename axes_t=none_t>
    constexpr auto transpose(const array_t& array, axes_t axes=axes_t{},
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto transposed = view::transpose(array,axes);
        return eval(transposed,context,output);
    } // transpose
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_TRANSPOSE_HPP