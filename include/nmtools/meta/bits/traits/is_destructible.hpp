#ifndef NMTOOLS_META_BITS_IS_DESTRUCTIBLE_HPP
#define NMTOOLS_META_BITS_IS_DESTRUCTIBLE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_destructible : false_type {};

    template<typename T>
    struct is_destructible<T,void_t<decltype(declval<T&>().~T())>> : true_type {};

    template <typename T, auto N>
    struct is_destructible<T[N]> : is_destructible<T> {};

    template <typename T>
    struct is_destructible<T[]> : is_destructible<T> {};

    template <typename T>
    inline constexpr auto is_destructible_v = is_destructible<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_IS_DESTRUCTIBLE_HPP