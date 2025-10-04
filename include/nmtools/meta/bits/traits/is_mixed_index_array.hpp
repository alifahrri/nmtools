#ifndef NMTOOLS_META_BITS_TRAITS_IS_MIXED_INDEX_ARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_MIXED_INDEX_ARRAY_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/traits/is_constant_index.hpp"
#include "nmtools/meta/bits/traits/is_index.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_mixed_index_array : false_type {};

    template <typename T>
    struct is_mixed_index_array<const T> : is_mixed_index_array<T> {};

    template <typename T>
    struct is_mixed_index_array<T&> : is_mixed_index_array<T> {};

    template <typename T>
    constexpr inline auto is_mixed_index_array_v = is_mixed_index_array<T>::value;

    template <template<typename...>typename tuple, typename...args_t>
    struct is_mixed_index_array<tuple<args_t...>,enable_if_t<is_tuple_v<tuple<args_t...>>>>
    {
        static constexpr auto value =
            (is_constant_index_v<args_t> || ...)
            && !(is_constant_index_v<args_t> && ...)
            && (is_index_v<args_t> && ...)
        ;
    };
}

namespace nmtools
{
    using meta::is_mixed_index_array_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_MIXED_INDEX_ARRAY_HPP