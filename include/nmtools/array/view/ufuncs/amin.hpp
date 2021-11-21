#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_AMIN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_AMIN_HPP

#include "nmtools/array/view/ufuncs/minimum.hpp"

namespace nmtools::view
{
    /**
     * @brief Return a view that computes the minimum of an array or the minimum along the given axis.
     * 
     * This is actually an alias to reduce_minimum.
     * 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     * @param a         input array
     * @param axis      axis to be reduced
     * @param dtype 
     * @param initial   optional initial value
     * @param keepdims  set to true if the reduced axis are to be kept
     * @return constexpr auto 
     */
    template <typename array_t, typename axis_t=none_t, typename dtype_t=none_t, typename initial_t=none_t, typename keepdims_t=meta::false_type>
    constexpr auto amin(const array_t& a, const axis_t& axis=None, dtype_t dtype=dtype_t{}, initial_t initial=initial_t{}, keepdims_t keepdims=False)
    {
        return reduce_minimum(a,axis,dtype,initial,keepdims);
    } // amin
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_AMIN_HPP