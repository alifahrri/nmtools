#ifndef NMTOOLS_META_BITS_TRAITS_HAS_DST_SHAPE_TYPE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_DST_SHAPE_TYPE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct has_dst_shape_type : false_type {};

    template <typename T>
    struct has_dst_shape_type<
        T, void_t<typename T::dst_shape_type>
    > : true_type {};

    template <typename T>
    inline constexpr bool has_dst_shape_type_v = has_dst_shape_type<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_HAS_DST_SHAPE_TYPE_HPP