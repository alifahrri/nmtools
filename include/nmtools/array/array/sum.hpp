#ifndef NMTOOLS_ARRAY_ARRAY_SUM_HPP
#define NMTOOLS_ARRAY_ARRAY_SUM_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/sum.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate sum of array elements over a given axis.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam dtype_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @param a        input array.
     * @param axis     axis in which the sum is to be performed on.
     * @param dtype    desired data type.
     * @param initial  initial value.
     * @param keepdims if true, the reduced axes are kept in the resulting array.
     * @param context  evaluation context.
     * @param output   optional output.
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename dtype_t=none_t, typename initial_t=none_t,
        typename keepdims_t=std::false_type, typename array_t, typename axis_t>
    constexpr auto sum(const array_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
        initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{},
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto sum_ = view::sum(a,axis,dtype,initial,keepdims);
        return eval(sum_,context,output);
    } // sum
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SUM_HPP