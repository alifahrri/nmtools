#ifndef NMTOOLS_META_BITS_TRAITS_HAS_SRC_SIZE_TYPE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_SRC_SIZE_TYPE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct has_src_size_type : false_type {};

    template <typename T>
    struct has_src_size_type<
        T, void_t<typename T::src_size_type>
    > : true_type {};

    template <typename T>
    inline constexpr bool has_src_size_type_v = has_src_size_type<T>::value;
}
#endif // NMTOOLS_META_BITS_TRAITS_HAS_SRC_SIZE_TYPE_HPP