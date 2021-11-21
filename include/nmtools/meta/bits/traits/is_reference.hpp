#ifndef NMTOOLS_META_BITS_TRAITS_IS_REFERENCE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_REFERENCE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_lvalue_reference : false_type {};

    template <typename T>
    struct is_lvalue_reference<T&> : true_type {};

    template <typename T>
    constexpr inline auto is_lvalue_reference_v = is_lvalue_reference<T>::value;

    template <typename T>
    struct is_rvalue_reference : false_type {};

    template <typename T>
    struct is_rvalue_reference<T&&> : true_type {};

    template <typename T>
    constexpr inline auto is_rvalue_reference_v = is_rvalue_reference<T>::value;
}
#endif // NMTOOLS_META_BITS_TRAITS_IS_REFERENCE_HPP