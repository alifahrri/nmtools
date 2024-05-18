#ifndef NMTOOLS_META_BITS_TRAITS_IS_CONST_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_CONST_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_const : false_type {};

    template <typename T>
    struct is_const<const T> : true_type {};

    template <typename T>
    struct is_const<T&> : is_const<T> {};

    template <typename T>
    constexpr inline auto is_const_v = is_const<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_CONST_HPP