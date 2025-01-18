#ifndef NMTOOLS_ARRAY_VIEW_VECDOT_HPP
#define NMTOOLS_ARRAY_VIEW_VECDOT_HPP

#include "nmtools/array/core/decorator.hpp"
#include "nmtools/array/core/alias.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"
#include "nmtools/array/view/sum.hpp"

namespace nmtools::view
{
    template <typename lhs_t, typename rhs_t, typename dtype_t=none_t, typename keepdims_t=meta::false_type>
    constexpr auto vecdot(const lhs_t& lhs, const rhs_t& rhs, dtype_t dtype=dtype_t{}, keepdims_t keepdims=keepdims_t{})
    {
        auto aliased = view::aliased(lhs,rhs);

        auto a_lhs = nmtools::get<0>(aliased);
        auto a_rhs = nmtools::get<1>(aliased);

        auto axis = meta::ct_v<-1>;
        auto initial = None;

        return view::sum(
            view::multiply(a_lhs,a_rhs)
            , axis
            , dtype
            , initial
            , keepdims
        );
    } // vecdot
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_VECDOT_HPP