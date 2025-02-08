#ifndef NMTOOLS_META_BITS_TRAITS_HAS_OPERANDS_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_OPERANDS_HPP

#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct has_operands : detail::expression_check<void,expr::operands,T> {};

    template <typename T>
    struct has_operands<const T> : has_operands<T> {};

    template <typename T>
    struct has_operands<T&> : has_operands<T> {};

    template <typename T>
    inline constexpr auto has_operands_v = has_operands<T>::value;
}

#endif // NMTOOLS_META_BITS_TRAITS_HAS_OPERANDS_HPP