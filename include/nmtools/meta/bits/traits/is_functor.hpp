#ifndef NMTOOLS_META_BITS_TRAITS_IS_FUNCTOR_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_FUNCTOR_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_functor : meta::false_type {};

    template <typename T>
    constexpr inline auto is_functor_v = is_functor<T>::value;

    template <typename T>
    struct is_functor<const T> : is_functor<T> {};

    template <typename T>
    struct is_functor<T&> : is_functor<T> {};
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_FUNCTOR_HPP