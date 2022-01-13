#ifndef NMTOOLS_META_BITS_TRAITS_IS_CLASS_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_CLASS_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/expr.hpp"
#include "nmtools/meta/bits/traits/is_union.hpp"

namespace nmtools::meta
{
    namespace expr
    {
        template <typename T>
        using member_ptr = decltype(declval<int T::*>());
    } // namespace expr

    template <typename T, typename=void>
    struct is_class : false_type {};

    template <typename T>
    struct is_class<T, enable_if_t<
        expression_check_v<expr::member_ptr,T>
        && !is_union_v<T>
    > > : true_type {};

    template <typename T>
    constexpr inline auto is_class_v = is_class<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_CLASS_HPP