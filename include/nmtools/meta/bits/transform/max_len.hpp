#ifndef NMTOOLS_META_BITS_TRANSFORM_MAX_LEN_HPP
#define NMTOOLS_META_BITS_TRANSFORM_MAX_LEN_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/transform/len.hpp"

namespace nmtools::meta
{
    // TODO: change bounded_size usages to max_len
    // like len but find bounded/max size
    // should not care if T is ndarray or not
    template <typename T, typename=void>
    struct max_len : len<T> {};

    template <typename T>
    struct max_len<const T> : max_len<T> {};

    template <typename T>
    struct max_len<T&> : max_len<T> {};

    template <typename T>
    constexpr inline auto max_len_v = max_len<T>::value;
}

namespace nmtools
{
    using meta::max_len_v;
}

#endif // NMTOOLS_META_BITS_TRANSFORM_MAX_LEN_HPP