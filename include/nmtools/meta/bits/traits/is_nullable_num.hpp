#ifndef NMTOOLS_META_BITS_TRAITS_IS_NULLABLE_NUM_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_NULLABLE_NUM_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_nullable_num : false_type {};

    template <typename T>
    struct is_nullable_num<const T> : is_nullable_num<T> {};

    template <typename T>
    struct is_nullable_num<T&> : is_nullable_num<T> {};

    template <typename T>
    struct is_nullable_num<nullable_num<T>> : true_type {};

    template <typename T>
    constexpr inline auto is_nullable_num_v = is_nullable_num<T>::value;
}

namespace nmtools
{
    using meta::is_nullable_num_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_NULLABLE_NUM_HPP