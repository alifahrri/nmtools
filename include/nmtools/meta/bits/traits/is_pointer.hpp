#ifndef NMTOOLS_BITS_TRAITS_IS_POINTER_HPP
#define NMTOOLS_BITS_TRAITS_IS_POINTER_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_pointer : false_type {};

    template <typename T>
    struct is_pointer<T*> : true_type {};

    template <typename T>
    constexpr inline auto is_pointer_v = is_pointer<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_BITS_TRAITS_IS_POINTER_HPP