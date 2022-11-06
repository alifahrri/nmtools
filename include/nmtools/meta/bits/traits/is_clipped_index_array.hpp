#ifndef NMTOOLS_META_BITS_TRAITS_IS_CLIPPED_INDEX_ARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_CLIPPED_INDEX_ARRAY_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/traits/is_clipped_integer.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_clipped_index_array : false_type {};

    template <template<typename...>typename Tuple, typename...Ts>
    struct is_clipped_index_array<
        Tuple<Ts...>,
        enable_if_t< is_tuple_v<Tuple<Ts...>> && (is_clipped_integer_v<Ts> && ...)>
    > : true_type {};

    template <template<typename,auto>typename Array, typename T, auto Size>
    struct is_clipped_index_array<
        Array<T,Size>,
        enable_if_t< is_clipped_integer_v<T> >
    > : true_type {};

    template <typename T>
    struct is_clipped_index_array<const T> : is_clipped_index_array<T> {};

    template <typename T>
    struct is_clipped_index_array<T&> : is_clipped_index_array<T> {};

    template <typename T>
    constexpr inline auto is_clipped_index_array_v = is_clipped_index_array<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_CLIPPED_INDEX_ARRAY_HPP