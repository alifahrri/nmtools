#ifndef NMTOOLS_META_BITS_TRAITS_IS_NULLABLE_INDEX_ARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_NULLABLE_INDEX_ARRAY_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_nullable_index_array : false_type {};

    template <typename T>
    struct is_nullable_index_array<const T> : is_nullable_index_array<T> {};

    template <typename T>
    struct is_nullable_index_array<T&> : is_nullable_index_array<T> {};

    template <typename T>
    constexpr inline auto is_nullable_index_array_v = is_nullable_index_array<T>::value;
}

namespace nmtools
{
    using meta::is_nullable_index_array_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_NULLABLE_INDEX_ARRAY_HPP