#ifndef NMTOOLS_ARRAY_VIEW_CUMSUM_HPP
#define NMTOOLS_ARRAY_VIEW_CUMSUM_HPP

#include "nmtools/array/view/ufuncs/add.hpp"

namespace nmtools::view
{
    /**
     * @brief Create a view that represents the cumulative sum of elements along a given axis.
     *
     * This view is equivalent to view::accumulate_add.
     * 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @param a     input array.
     * @param axis  axis in which the cumulative sum is to be operated on.
     * @param dtype desired data type
     * @return constexpr auto 
     */
    template <typename array_t, typename axis_t, typename dtype_t>
    constexpr auto cumsum(const array_t& a, axis_t axis, dtype_t)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = add_t<none_t,none_t,res_t>;
        return accumulate(op_t{},a,axis);
    } // cumsum

    template <typename array_t, typename axis_t>
    constexpr auto cumsum(const array_t& a, axis_t axis)
    {
        return cumsum(a,axis,None);
    } // cumsum
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_CUMSUM_HPP