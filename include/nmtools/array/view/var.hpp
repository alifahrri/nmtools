#ifndef NMTOOLS_ARRAY_VIEW_VAR_HPP
#define NMTOOLS_ARRAY_VIEW_VAR_HPP

#include "nmtools/array/view/ufuncs/fabs.hpp"
#include "nmtools/array/view/ufuncs/square.hpp"
#include "nmtools/array/view/ufuncs/subtract.hpp"
#include "nmtools/array/view/sum.hpp"
#include "nmtools/array/view/mean.hpp"

namespace nmtools::view
{
    /**
     * @brief Create view that computes variance.
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
    constexpr auto var(const array_t& array, const axis_t& axis, dtype_t dtype=dtype_t{}, ddof_t ddof=ddof_t{0}, keepdims_t keepdims=keepdims_t{})
    {
        // must keep dimension to properly subtract
        auto a = mean(array,axis,dtype,/*keepdims=*/True);
        auto b = subtract(array, a);
        auto c = fabs(b);
        auto d = square(c);
        // no reason to start from other initial value
        auto e = sum(d,axis,dtype,/*initial=*/None,keepdims);
        // TODO: fix unwrap to handle bounded array
        #if 0
        // TODO: error handling
        auto N = detail::mean_divisor(::nmtools::shape(unwrap(array)),axis);
        #else
        auto N = detail::mean_divisor(::nmtools::shape(array),axis);
        #endif
        return divide(e,N-ddof);
    } // var
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_VAR_HPP