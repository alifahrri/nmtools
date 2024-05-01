#ifndef NMTOOLS_META_BITS_TRAITS_IS_CONSTRUCTIBLE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_CONSTRUCTIBLE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    template <typename T, typename...Args>
    struct is_constructible
        : detail::expression_check<void,expr::constructor,T,Args...> {};

    template <typename T, typename...Args>
    constexpr inline auto is_constructible_v = is_constructible<T,Args...>::value;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_CONSTRUCTIBLE_HPP