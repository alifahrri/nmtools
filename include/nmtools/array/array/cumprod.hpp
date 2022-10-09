#ifndef NMTOOLS_ARRAY_ARRAY_CUMPROD_HPP
#define NMTOOLS_ARRAY_ARRAY_CUMPROD_HPP

#include "nmtools/array/view/cumprod.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate the cumulative product of elements along a given axis.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @param a     input array.
     * @param axis  axis in which the cumulative product is to be operated on.
     * @param dtype desired data type
     * @param context evaluation context
     * @param output  optional output
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t,
        typename array_t, typename axis_t, typename dtype_t=none_t>
    constexpr auto cumprod(const array_t& a, axis_t axis, dtype_t dtype=dtype_t{},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto array = view::cumprod(a,axis,dtype);
        return eval(array
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // cumprod
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_CUMPROD_HPP