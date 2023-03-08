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

        // TODO: use maybe type instead
        const auto [success, bshape] = index::broadcast_shape(::nmtools::shape<true>(arrays)...);
        const auto bsize = index::broadcast_size(bshape,nmtools::size<true>(arrays)...);

        using result_t = nmtools_tuple<decltype(broadcast_to(meta::declval<arrays_t>(),bshape,bsize))...>;
        nmtools_assert_prepare_type (return_t, result_t);
        nmtools_assert (success, "cannot broadcast arrays together", return_t);

        return return_t{result_t{broadcast_to(arrays,bshape,bsize)...}};
    } // broadcast_arrays
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP