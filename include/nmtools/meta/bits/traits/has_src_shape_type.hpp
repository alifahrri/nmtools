#ifndef NMTOOLS_META_BITS_HAS_SRC_SHAPE_TYPE_HPP
#define NMTOOLS_META_BITS_HAS_SRC_SHAPE_TYPE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct has_src_shape_type : false_type {};

    template <typename T>
    struct has_src_shape_type<
        T, void_t<typename T::src_shape_type>
    > : true_type {};

    template <typename T>
    inline constexpr bool has_src_shape_type_v = has_src_shape_type<T>::value;
} // nmtools::meta

#endif // NMTOOLS_META_BITS_HAS_SRC_SHAPE_TYPE_HPP