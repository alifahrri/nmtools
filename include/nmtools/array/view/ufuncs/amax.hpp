#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_AMAX_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_AMAX_HPP

#include "nmtools/array/view/ufuncs/maximum.hpp"

namespace nmtools::view
{
    /**
     * @brief Return a view that computes the maximum of an array or the maximum along the given axis.
     * 
     * This is actually an alias to reduce_maximum.
     * 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     * @param a         input array
     * @param axis      axis in to be reduced
     * @param dtype 
     * @param initial   optional initial value
     * @param keepdims  set to true if the reduced axis are to be kept
     * @return constexpr auto 
     */
    template <typename array_t, typename axis_t=none_t, typename dtype_t=none_t, typename initial_t=none_t, typename keepdims_t=meta::false_type>
    constexpr auto amax(const array_t& a, const axis_t& axis=None, dtype_t dtype=dtype_t{}, initial_t initial=initial_t{}, keepdims_t keepdims=False)
    {
        return reduce_maximum(a,axis,dtype,initial,keepdims);
    } // amax
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_AMAX_HPP