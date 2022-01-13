#ifndef NMTOOLS_META_BITS_TRAITS_IS_UNION_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_UNION_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    // assume no union for now
    // TODO: implement union
    template <typename T>
    struct is_union : false_type {};

    template <typename T>
    constexpr inline auto is_union_v = is_union<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_UNION_HPP