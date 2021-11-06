#ifndef NMTOOLS_META_BITS_TRAITS_IS_EITHER_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_EITHER_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief Check if type T is either type (variant with exactly 2 type).
     * 
     * The name is from haskell's Either type with Left and Right.
     *
     * @tparam T type to check
     * @tparam typename sfinae point
     */
    template <typename T, typename=void>
    struct is_either : false_type{};

    template <typename T>
    constexpr inline auto is_either_v = is_either<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_EITHER_HPP