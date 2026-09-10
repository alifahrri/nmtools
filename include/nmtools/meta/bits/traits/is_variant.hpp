#ifndef NMTOOLS_META_BITS_TRAITS_IS_VARIANT_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_VARIANT_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_variant : false_type {};

    template <typename T>
    struct is_variant<const T> : is_variant<T> {};

    template <typename T>
    struct is_variant<T&> : is_variant<T> {};

    template <typename T>
    constexpr inline auto is_variant_v = is_variant<T>::value;
}

namespace nmtools
{
    using meta::is_variant_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_VARIANT_HPP