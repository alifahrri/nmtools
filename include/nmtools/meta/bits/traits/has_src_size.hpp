#ifndef NMTOOLS_META_BITS_TRAITS_HAS_SRC_SIZE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_SRC_SIZE_HPP

#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct has_src_size : detail::expression_check<void,expr::src_size,T> {};

    template <typename T>
    struct has_src_size<const T> : has_src_size<T> {};

    template <typename T>
    struct has_src_size<T&> : has_src_size<T> {};

    template <typename T>
    nmtools_meta_variable_attribute
    inline constexpr bool has_src_size_v = has_src_size<T>::value;
}

#endif // NMTOOLS_META_BITS_TRAITS_HAS_SRC_SIZE_HPP