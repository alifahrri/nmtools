#ifndef NMTOOLS_ARRAY_VIEW_SUM_HPP
#define NMTOOLS_ARRAY_VIEW_SUM_HPP

#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::view
{
    /**
     * @brief Create a view that represents sum of array elements over a given axis.
     *
     * This function is equivalent to view::reduce_add.
     * 
     * @tparam left_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     * @param a        input array.
     * @param axis     axis or axes in which sum are to be performed.
     * @param dtype    desired data type.
     * @param initial  initial value of the sum.
     * @param keepdims if true, the reduced axis are kept in the results.
     * @return constexpr auto 
     */
    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t, typename keepdims_t>
    constexpr auto sum(const left_t& a, const axis_t& axis, dtype_t, initial_t initial, keepdims_t keepdims)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = add_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,initial,keepdims);
    } // add

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t>
    constexpr auto sum(const left_t& a, const axis_t& axis, dtype_t, initial_t initial)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = add_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,initial);
    } // add

    template <typename left_t, typename axis_t, typename dtype_t>
    constexpr auto sum(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        return view::sum(a,axis,dtype,None);
    } // add

    template <typename left_t, typename axis_t>
    constexpr auto sum(const left_t& a, const axis_t& axis)
    {
        return view::sum(a,axis,None,None);
    } // add
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_SUM_HPP