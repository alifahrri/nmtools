#ifndef NMTOOLS_ARRAY_VIEW_CUMPROD_HPP
#define NMTOOLS_ARRAY_VIEW_CUMPROD_HPP

#include "nmtools/array/view/ufuncs/multiply.hpp"

namespace nmtools::view
{
    /**
     * @brief Create a view that represents the cumulative product of elements along a given axis.
     *
     * This view is equivalent to view::accumulate_multiply.
     * 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @param a     input array.
     * @param axis  axis in which the cumulative product is to be operated on.
     * @param dtype desired data type
     * @return constexpr auto 
     */
    template <typename array_t, typename axis_t, typename dtype_t>
    constexpr auto cumprod(const array_t& a, axis_t axis, dtype_t dtype)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = multiply_t<none_t,none_t,res_t>;
        return accumulate(op_t{},a,axis);
    } // cumprod

    template <typename array_t, typename axis_t>
    constexpr auto cumprod(const array_t& a, axis_t axis)
    {
        return cumprod(a,axis,None);
    } // cumprod
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_CUMPROD_HPP