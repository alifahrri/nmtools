#ifndef NMTOOLS_META_BITS_TRAITS_IS_BROADCAST_VIEW_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_BROADCAST_VIEW_HPP

#include "nmtools/meta/common.hpp"

// TODO: generalize to parametrized check
namespace nmtools::meta
{
    template <typename T>
    struct is_broadcast_view : meta::false_type {};

    template <typename T>
    constexpr inline auto is_broadcast_view_v = is_broadcast_view<T>::value;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_BROADCAST_VIEW_HPP