#ifndef NMTOOLS_BITS_TRAITS_IS_CONTEXT_HPP
#define NMTOOLS_BITS_TRAITS_IS_CONTEXT_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_context : false_type {};

    template <typename T>
    struct is_context<const T> : is_context<T> {};

    template <typename T>
    struct is_context<T&> : is_context<T> {};

    template <typename T>
    constexpr inline auto is_context_v = is_context<T>::value;
}

namespace nmtools
{
    using meta::is_context_v;
}

#endif // NMTOOLS_BITS_TRAITS_IS_CONTEXT_HPP