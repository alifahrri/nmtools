#ifndef NMTOOLS_META_BITS_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_constructible.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_default_constructible : is_constructible<T> {};

    template <typename T>
    constexpr inline auto is_default_constructible_v = is_default_constructible<T>::value;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP