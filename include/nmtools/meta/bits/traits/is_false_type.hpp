#ifndef NMTOOLS_META_BITS_TRAITS_IS_FALSE_TYPE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_FALSE_TYPE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_false_type : false_type {};

    template <>
    struct is_false_type<false_type> : true_type {};

    template <typename T>
    struct is_false_type<const T> : is_false_type<T> {};

    template <typename T>
    struct is_false_type<T&> : is_false_type<T> {};

    template <typename T>
    constexpr inline auto is_false_type_v = is_false_type<T>::value;
} // nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_FALSE_TYPE_HPP