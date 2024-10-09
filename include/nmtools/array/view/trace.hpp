#ifndef NMTOOLS_ARRAY_VIEW_TRACE_HPP
#define NMTOOLS_ARRAY_VIEW_TRACE_HPP

#include "nmtools/array/view/diagonal.hpp"
#include "nmtools/array/view/sum.hpp"

namespace nmtools::view
{
    template <typename array_t, typename offset_t=meta::ct<0>, typename axis1_t=meta::ct<0>, typename axis2_t=meta::ct<1>, typename dtype_t=none_t>
    constexpr auto trace(const array_t& array, offset_t offset=offset_t{}, axis1_t axis1=axis1_t{}, axis2_t axis2=axis2_t{}, dtype_t dtype=dtype_t{})
    {
        auto axis = meta::ct_v<-1>;
        auto initial = None;
        auto keepdims = False;
        auto diagonal = view::diagonal(array,offset,axis1,axis2);
        return view::sum(diagonal,axis,dtype,initial,keepdims);
    }
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_TRACE_HPP