#ifndef NMTOOLS_ARRAY_VIEW_VECTOR_NORM_HPP
#define NMTOOLS_ARRAY_VIEW_VECTOR_NORM_HPP

#include "nmtools/array/view/ufuncs/square.hpp"
#include "nmtools/array/view/ufuncs/sqrt.hpp"
#include "nmtools/array/view/ufuncs/fabs.hpp"
#include "nmtools/array/view/ufuncs/power.hpp"
#include "nmtools/array/view/sum.hpp"

namespace nmtools::view
{
    template <typename array_t, typename axis_t=none_t, typename keepdims_t=meta::false_type, typename ord_t=nm_index_t>
    constexpr auto vector_norm(const array_t& array, const axis_t& axis=axis_t{}, keepdims_t keepdims=keepdims_t{}, ord_t ord=ord_t{2})
    {
        auto v1 = view::fabs(array);
        auto v2 = view::power(v1,ord);
        auto v3 = view::sum(v2,axis,/*dtype*/None,/*initial*/None,keepdims);
        auto v4 = view::power(v3,1.f/ord);
        return v4;
    } // vector_norm
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_VECTOR_NORM_HPP