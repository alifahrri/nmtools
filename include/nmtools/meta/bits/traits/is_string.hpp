#ifndef NMTOOLS_META_BITS_TRAITS_IS_STRING_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_STRING_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename>
    struct is_string : false_type {};

    template <typename T>
    struct is_string<const T> : is_string<T> {};

    template <typename T>
    struct is_string<T&> : is_string<T> {};

    template <typename T>
    constexpr inline auto is_string_v = is_string<T>::value;
}

namespace nmtools
{
    using meta::is_string_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_STRING_HPP