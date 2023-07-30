#ifndef NMTOOLS_META_BITS_TRAITS_IS_REDUCTION_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_REDUCTION_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    // trait for reduction view
    template <typename T>
    struct is_reduction : false_type {};

    template <typename T>
    struct is_reduction<const T> : is_reduction<T> {};

    template <typename T>
    struct is_reduction<T&> : is_reduction<T> {};

    template <typename T>
    constexpr inline auto is_reduction_v = is_reduction<T>::value;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_REDUCTION_HPP