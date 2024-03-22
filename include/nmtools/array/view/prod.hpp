#ifndef NMTOOLS_ARRAY_VIEW_PROD_HPP
#define NMTOOLS_ARRAY_VIEW_PROD_HPP

#include "nmtools/array/view/ufuncs/multiply.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::view
{
    /**
     * @brief Create a view that represents product of array elements over a given axis.
     *
     * This function is equivalent to view::reduce_multiply.
     * 
     * @tparam left_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     * @param a        input array.
     * @param axis     axis or axes in which product are to be performed.
     * @param dtype    desired data type.
     * @param initial  initial value of the product.
     * @param keepdims if true, the reduced axis are kept in the results.
     * @return constexpr auto 
     */
    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t, typename keepdims_t>
    constexpr auto prod(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial, keepdims_t keepdims)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = multiply_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,initial,keepdims);
    } // prod

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t>
    constexpr auto prod(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = multiply_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,initial);
    } // prod

    template <typename left_t, typename axis_t, typename dtype_t>
    constexpr auto prod(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        return prod(a,axis,dtype,None);
    } // prod

    template <typename left_t, typename axis_t>
    constexpr auto prod(const left_t& a, const axis_t& axis)
    {
        return prod(a,axis,None,None);
    } // prod
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_PROD_HPP