#ifndef NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP
#define NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/broadcast_to.hpp"
#include "nmtools/array/index/broadcast_shape.hpp"

namespace nmtools::view
{
    /**
     * @brief Broadcast two arrays against each other
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     * @param lhs 
     * @param rhs 
     * @return constexpr auto 
     */
    template <typename lhs_t, typename rhs_t>
    constexpr auto broadcast_arrays(const lhs_t& lhs, const rhs_t& rhs)
    {
        auto lhs_shape = ::nmtools::shape(lhs);
        auto rhs_shape = ::nmtools::shape(rhs);
        auto [success, broadcasted_shape] = index::broadcast_shape(lhs_shape, rhs_shape);
        assert (success
            // , "cannot broadcast shape"
        );
        auto lhs_view = broadcast_to(lhs,broadcasted_shape);
        auto rhs_view = broadcast_to(rhs,broadcasted_shape);
        return std::tuple{lhs_view, rhs_view};
    } // broadcast_arrays
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP