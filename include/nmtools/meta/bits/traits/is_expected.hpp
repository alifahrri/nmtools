#ifndef NMTOOLS_META_BITS_TRAITS_IS_EXPECTED_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_EXPECTED_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_expected : false_type {};

    template <typename T>
    struct is_expected<const T> : is_expected<T> {};

    template <typename T>
    struct is_expected<T&> : is_expected<T> {};

    template <typename T>
    constexpr inline auto is_expected_v = is_expected<T>::value;
}

namespace nmtools
{
    using meta::is_expected_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_EXPECTED_HPP