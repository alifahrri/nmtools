#ifndef NMTOOLS_META_BITS_TRAITS_IS_ATTRIBUTE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_ATTRIBUTE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_attribute : false_type {};

    template <typename T>
    constexpr inline auto is_attribute_v = is_attribute<T>::value;

    template <typename T>
    struct is_attribute<const T> : is_attribute<T> {};

    template <typename T>
    struct is_attribute<T&> : is_attribute<T> {};
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_ATTRIBUTE_HPP