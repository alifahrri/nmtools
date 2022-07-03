#ifndef NMTOOLS_META_BITS_TRAITS_IS_TRUE_TYPE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_TRUE_TYPE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_true_type : false_type {};

    template <>
    struct is_true_type<true_type> : true_type {};

    template <typename T>
    struct is_true_type<const T> : is_true_type<T> {};

    template <typename T>
    struct is_true_type<T&> : is_true_type<T> {};

    template <typename T>
    constexpr inline auto is_true_type_v = is_true_type<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_TRUE_TYPE_HPP