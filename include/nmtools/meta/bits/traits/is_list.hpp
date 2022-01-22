#ifndef NMTOOLS_META_BITS_TRAITS_IS_LIST_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_LIST_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_list : false_type {};

    template <typename T>
    constexpr inline auto is_list_v = is_list<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_LIST_HPP