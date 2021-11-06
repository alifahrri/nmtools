#ifndef NMTOOLS_META_BITS_TRAITS_IS_MAYBE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_MAYBE_HPP

#include "nmtools/meta/common.hpp"

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
    constexpr inline auto is_maybe_v = is_maybe<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_MAYBE_HPP