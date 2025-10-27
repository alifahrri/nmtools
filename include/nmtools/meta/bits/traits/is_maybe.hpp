#ifndef NMTOOLS_META_BITS_TRAITS_IS_MAYBE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_MAYBE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/has_address_space.hpp"
#include "nmtools/meta/bits/transform/remove_address_space.hpp"

namespace nmtools::meta
{
    /**
     * @brief Check if type T is optional type.
     *
     * The name is from haskell's Maybe type.
     * 
     * @tparam T type to check
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_maybe : false_type {};

    template <typename T>
    struct is_maybe<const T> : is_maybe<T> {};

    template <typename T>
    struct is_maybe<T&> : is_maybe<T> {};

    template <typename T>
    constexpr inline auto is_maybe_v = is_maybe<T>::value;
} // namespace nmtools::meta

namespace nmtools
{
    using meta::is_maybe_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_MAYBE_HPP