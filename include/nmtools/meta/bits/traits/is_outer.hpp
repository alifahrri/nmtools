#ifndef NMTOOLS_META_BITS_TRAITS_IS_OUTER_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_OUTER_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    // trait for reduction view
    template <typename T>
    struct is_outer : false_type {};

    template <typename T>
    struct is_outer<const T> : is_outer<T> {};

    template <typename T>
    struct is_outer<T&> : is_outer<T> {};

    template <typename T>
    constexpr inline auto is_outer_v = is_outer<T>::value;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_OUTER_HPP