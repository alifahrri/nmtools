#ifndef NMTOOLS_ARRAY_VIEW_STACK_HPP
#define NMTOOLS_ARRAY_VIEW_STACK_HPP

#include "nmtools/array/view/concatenate.hpp"
#include "nmtools/array/view/expand_dims.hpp"

namespace nmtools::view
{
    template <typename lhs_t, typename rhs_t, typename axis_t=meta::ct<0>>
    constexpr auto stack(const lhs_t& lhs, const rhs_t& rhs, axis_t axis=axis_t{})
    {
        return concatenate(
              expand_dims(lhs,axis)
            , expand_dims(rhs,axis)
            , axis
        );
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_STACK_HPP