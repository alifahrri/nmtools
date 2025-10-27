#ifndef NMTOOLS_META_BITS_TRAITS_IS_NULLABLE_INDEX_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_NULLABLE_INDEX_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_integer.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_nullable_index : false_type {};

    template <typename T>
    struct is_nullable_index<nullable_num<T>> : is_integer<T> {};

    template <typename T>
    struct is_nullable_index<const T> : is_nullable_index<T> {};

    template <typename T>
    struct is_nullable_index<T&> : is_nullable_index<T> {};

    template <typename T>
    constexpr inline auto is_nullable_index_v = is_nullable_index<T>::value;
}

namespace nmtools
{
    using meta::is_nullable_index_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_NULLABLE_INDEX_HPP