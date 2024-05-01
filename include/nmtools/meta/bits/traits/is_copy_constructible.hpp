#ifndef NMTOOLS_META_BITS_TRAITS_IS_COPY_CONSTRUCTIBLE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_COPY_CONSTRUCTIBLE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/expr.hpp"
#include "nmtools/meta/bits/traits/is_constructible.hpp"
#include "nmtools/meta/bits/transform/add_const.hpp"
#include "nmtools/meta/bits/transform/add_reference.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_copy_constructible
        : detail::expression_check<void,expr::constructor,
            T, add_lvalue_reference_t<add_const_t<T>>>
    {};

    template <typename T>
    constexpr inline auto is_copy_constructible_v = is_copy_constructible<T>::value;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_COPY_CONSTRUCTIBLE_HPP