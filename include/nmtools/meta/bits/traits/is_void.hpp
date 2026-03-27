#ifndef NMTOOLS_META_BITS_TRAITS_IS_VOID_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_VOID_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_void : false_type {};

    template <>
    struct is_void<void> : true_type {};

    template <typename T>
    constexpr inline auto is_void_v  = is_void<T>::value;
} // namespace nmtools::meta

namespace nmtools
{
    using meta::is_void_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_VOID_HPP