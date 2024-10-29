#ifndef NMTOOLS_META_BITS_TRAITS_IS_CLIPPED_INDEX_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_CLIPPED_INDEX_HPP

#include "nmtools/meta/bits/traits/is_clipped_integer.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_clipped_index : is_clipped_integer<T> {};

    template <typename T>
    constexpr inline auto is_clipped_index_v = is_clipped_index<T>::value;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_CLIPPED_INDEX_HPP