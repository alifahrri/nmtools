#ifndef NMTOOLS_META_BITS_TRAITS_IS_CLIPPED_INTEGER_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_CLIPPED_INTEGER_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_clipped_integer : false_type {};

    template <typename T>
    struct is_clipped_integer<const T> : is_clipped_integer<T> {};

    template <typename T>
    struct is_clipped_integer<T&> : is_clipped_integer<T> {};

    template <typename T, auto Min, auto Max>
    struct is_clipped_integer<clipped_integer_t<T,Min,Max>> : true_type {};

    template <typename T>
    constexpr inline auto is_clipped_integer_v = is_clipped_integer<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_CLIPPED_INTEGER_HPP