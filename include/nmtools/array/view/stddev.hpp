#ifndef NMTOOLS_ARRAY_VIEW_STDDEV_HPP
#define NMTOOLS_ARRAY_VIEW_STDDEV_HPP

#include "nmtools/array/view/var.hpp"
#include "nmtools/array/view/ufuncs/sqrt.hpp"

namespace nmtools::view
{
    /**
     * @brief Create a view that computes standard deviation.
     * 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @tparam ddof_t 
     * @tparam keepdims_t 
     * @param array     input array
     * @param axis      axis to operates in
     * @param dtype     optional datatype
     * @param ddof      delta degrees of freedom
     * @param keepdims  keep the dimension of the result, makes broadcasting with original array work properly
     * @return constexpr auto 
     */
    template <typename array_t, typename axis_t, typename dtype_t=none_t, typename ddof_t=size_t, typename keepdims_t=meta::false_type>
    constexpr auto stddev(const array_t& array, const axis_t& axis, dtype_t dtype=dtype_t{}, ddof_t ddof=ddof_t{0}, keepdims_t keepdims=keepdims_t{})
    {
        auto a = view::var(array,axis,dtype,ddof,keepdims);
        return view::sqrt(a);
    } // stddev
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_STDDEV_HPP