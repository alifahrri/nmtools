#ifndef NMTOOLS_ARRAY_ARRAY_CUMSUM_HPP
#define NMTOOLS_ARRAY_ARRAY_CUMSUM_HPP

#include "nmtools/array/view/cumsum.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate the cumulative sum of elements along a given axis.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @param a     input array.
     * @param axis  axis in which the cumulative sum is to be operated on.
     * @param dtype desired data type
     * @param context evaluation context
     * @param output  optional output
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename array_t, typename axis_t, typename dtype_t=none_t>
    constexpr auto cumsum(const array_t& a, axis_t axis, dtype_t dtype=dtype_t{},
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto array = view::cumsum(a,axis,dtype);
        return eval(array,context,output);
    } // cumsum
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_CUMSUM_HPP