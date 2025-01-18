#ifndef NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP
#define NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP

#include "nmtools/array/broadcast_to.hpp"
#include "nmtools/array/index/broadcast_shape.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/core/alias.hpp"

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
        static_assert( meta::is_tuple_v<tuple<arrays_t...>>
            , "unexpected type for aliased_broadcast_arrays, expected tuple type" );
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
        auto Sequence = meta::make_index_sequence_v<sizeof...(arrays_t)>;
        using aliased_pack_t = decltype(aliased_pack);
        if constexpr (meta::is_maybe_v<aliased_pack_t>) {
            using result_t = decltype(aliased_broadcast_arrays(unwrap(aliased_pack),Sequence));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(aliased_pack)
                ? return_t{aliased_broadcast_arrays(unwrap(aliased_pack),Sequence)}
                : return_t{meta::Nothing}
            );
        } else {
            return aliased_broadcast_arrays(aliased_pack,Sequence);
        }
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_BROADCAST_ARRAYS_HPP
#define NMTOOLS_ARRAY_ARRAY_BROADCAST_ARRAYS_HPP

#include "nmtools/array/broadcast_arrays.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly broadcast arrays
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam resolver_t=eval_result_t 
     * @tparam arrays_t 
     * @param arrays arrays to be broadcasted together
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename...arrays_t>
    constexpr auto broadcast_arrays(const arrays_t&...arrays)
    {
        auto broadcasted_pack = view::broadcast_arrays(arrays...);
        return apply_eval(broadcasted_pack
            , context_t{}
            , output_t{}
            , meta::as_value_v<resolver_t>
        );
    } // broadcast_arrays
}

#endif // NMTOOLS_ARRAY_ARRAY_BROADCAST_ARRAYS_HPP