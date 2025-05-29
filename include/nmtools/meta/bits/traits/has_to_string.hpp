#ifndef NMTOOLS_BITS_TRAITS_HAS_TO_STRING_HPP
#define NMTOOLS_BITS_TRAITS_HAS_TO_STRING_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    namespace expr
    {
        template <typename T>
        using to_string = decltype(declval<T>().to_string());
    }

    template <typename T>
    struct has_to_string : detail::expression_check<void,expr::to_string,T> {};

    template <typename T>
    struct has_to_string<const T> : has_to_string<T> {};

    template <typename T>
    struct has_to_string<T&> : has_to_string<T> {};

    template <typename T>
    constexpr inline auto has_to_string_v = has_to_string<T>::value;
}

#endif // NMTOOLS_BITS_TRAITS_HAS_TO_STRING_HPP