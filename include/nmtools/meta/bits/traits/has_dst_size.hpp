#ifndef NMTOOLS_META_BITS_TRAITS_HAS_DST_SIZE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_DST_SIZE_HPP

#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct has_dst_size : detail::expression_check<void,expr::dst_size,T> {};

    template <typename T>
    struct has_dst_size<const T> : has_dst_size<T> {};

    template <typename T>
    struct has_dst_size<T&> : has_dst_size<T> {};

    template <typename T>
    nmtools_meta_variable_attribute
    inline constexpr bool has_dst_size_v = has_dst_size<T>::value;
}

#endif // NMTOOLS_META_BITS_TRAITS_HAS_DST_SIZE_HPP