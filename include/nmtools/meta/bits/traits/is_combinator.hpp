#ifndef NMTOOLS_META_BITS_TRAITS_IS_COMBINATOR_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_COMBINATOR_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_combinator : false_type {};

    template <typename T>
    constexpr inline auto is_combinator_v = is_combinator<T>::value;

    template <typename T>
    struct is_combinator<const T> : is_combinator<T> {};

    template <typename T>
    struct is_combinator<T&> : is_combinator<T> {};
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_COMBINATOR_HPP