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

        const auto result = index::broadcast_shape(::nmtools::shape<true>(arrays)...);
        [[maybe_unused]] const auto success = static_cast<bool>(result);

        using bcast_result_t = meta::get_maybe_type_t<decltype(result)>;
        using bsize_t  = meta::resolve_optype_t<index::broadcast_size_t,bcast_result_t,decltype(nmtools::size<true>(arrays))...>;

        using result_t = nmtools_tuple<decltype(view::broadcast_to(meta::declval<arrays_t>(),meta::declval<bcast_result_t>(),meta::declval<bsize_t>()))...>;
        nmtools_assert_prepare_type (return_t, result_t);
        nmtools_assert (success, "cannot broadcast arrays together", return_t);

        const auto bsize = index::broadcast_size(*result,nmtools::size<true>(arrays)...);

        return return_t{result_t{view::broadcast_to(arrays,*result,bsize)...}};
    } // broadcast_arrays
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP