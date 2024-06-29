#ifndef NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP
#define NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP

#include "nmtools/array/view/broadcast_to.hpp"
#include "nmtools/array/index/broadcast_shape.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/array/view/alias.hpp"

namespace nmtools::view
{
    /**
     * @brief broadcast arrays against each other.
     * 
     * @tparam arrays_t 
     * @param arrays 
     * @return constexpr auto 
     */
    template <template<typename...>typename tuple, typename...arrays_t, auto...Is>
    constexpr auto aliased_broadcast_arrays(const tuple<arrays_t...>& arrays, meta::index_sequence<Is...>)
    {
        static_assert( sizeof...(arrays_t) >= 2
            , "please provide at least two arrays for broadcast_arrays");

        auto bcast_shape = index::broadcast_shape(shape<true>(nmtools::get<Is>(arrays))...);
        auto bcast_size  = index::broadcast_size(bcast_shape,size<true>(nmtools::get<Is>(arrays))...);
        if constexpr (meta::is_maybe_v<decltype(bcast_shape)>) {
            // avoid tuple<maybe<...>...> because not usable in constexpr evaluation
            using bcast_shape_t = meta::get_maybe_type_t<decltype(bcast_shape)>;
            using bcast_size_t  = meta::get_maybe_type_t<decltype(bcast_size)>;
            using result_t = nmtools_tuple<decltype(unwrap(view::broadcast_to(nmtools::get<Is>(arrays),meta::declval<bcast_shape_t>(),meta::declval<bcast_size_t>())))...>;
            using return_t = nmtools_maybe<result_t>;
            return (static_cast<bool>(bcast_shape)
                ? return_t{nmtools_tuple{unwrap(view::broadcast_to(nmtools::get<Is>(arrays),*bcast_shape,*bcast_size))...}}
                : return_t{meta::Nothing}
            );
        } else {
            // unwrap to avoid construction of tuple<maybe<...>...> at compile-time
            return nmtools_tuple{unwrap(view::broadcast_to(nmtools::get<Is>(arrays),bcast_shape,bcast_size))...};
        }
    } // broadcast_arrays

    template <typename...arrays_t>
    constexpr auto broadcast_arrays(const arrays_t&...arrays)
    {
        auto aliased_pack = view::aliased(arrays...);
        return aliased_broadcast_arrays(aliased_pack,meta::make_index_sequence_v<sizeof...(arrays_t)>);
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP