#ifndef NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP
#define NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP

#include "nmtools/array/view/broadcast_to.hpp"
#include "nmtools/array/index/broadcast_shape.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/assert.hpp"

namespace nmtools::view
{
    /**
     * @brief broadcast arrays against each other.
     * 
     * @tparam arrays_t 
     * @param arrays 
     * @return constexpr auto 
     */
    template <typename...arrays_t>
    constexpr auto broadcast_arrays(const arrays_t&...arrays)
    {
        static_assert( sizeof...(arrays_t) >= 2
            , "please provide at least two arrays for broadcast_arrays");

        auto [success, broadcasted_shape] = index::broadcast_shape(::nmtools::shape(arrays)...);

        // easiest way to get result type
        using result_t = decltype(std::tuple{broadcast_to(arrays,broadcasted_shape)...});
        nmtools_assert_prepare_type (return_t, result_t);
        nmtools_assert (success, "cannot broadcast shape", return_t);

        return return_t{std::tuple{broadcast_to(arrays,broadcasted_shape)...}};
    } // broadcast_arrays
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP