#ifndef NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP
#define NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/broadcast_to.hpp"
#include "nmtools/array/index/broadcast_shape.hpp"

namespace nmtools::view
{
    /**
     * @brief broadcast arrays against each other.
     * 
     * @tparam first_t 
     * @tparam second_t 
     * @tparam rest_t 
     * @param fst 
     * @param snd 
     * @param rst 
     * @return constexpr auto 
     */
    template <typename first_t, typename second_t, typename...rest_t>
    constexpr auto broadcast_arrays(const first_t& fst, const second_t& snd, const rest_t&...rst)
    {
        auto lhs_shape = ::nmtools::shape(fst);
        auto snd_shape = ::nmtools::shape(snd);
        auto [success, broadcasted_shape] = index::broadcast_shape(lhs_shape, snd_shape, ::nmtools::shape(rst)...);
        assert (success
            // , "cannot broadcast shape"
        );
        auto lhs_view = broadcast_to(fst,broadcasted_shape);
        auto snd_view = broadcast_to(snd,broadcasted_shape);
        return std::tuple{lhs_view, snd_view, broadcast_to(rst,broadcasted_shape)...};
    } // broadcast_arrays
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP