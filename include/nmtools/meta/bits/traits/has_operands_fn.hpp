#ifndef NMTOOLS_META_BITS_TRAITS_HAS_OPERANDS_FN_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_OPERANDS_FN_HPP

#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct has_operands_fn : detail::expression_check<void,expr::operands_fn,T> {};

    template <typename T>
    nmtools_meta_variable_attribute
    constexpr inline auto has_operands_fn_v = has_operands_fn<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_HAS_OPERANDS_FN_HPP