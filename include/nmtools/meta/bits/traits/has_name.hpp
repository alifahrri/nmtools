#ifndef NMTOOLS_META_BITS_TRAITS_HAS_NAME_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_NAME_HPP

#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct has_name : detail::expression_check<void,expr::name,T> {};

    template <typename T>
    nmtools_meta_variable_attribute
    constexpr inline auto has_name_v = has_name<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_HAS_NAME_HPP