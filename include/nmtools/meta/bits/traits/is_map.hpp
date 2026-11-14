#ifndef NMTOOLS_META_BITS_TRAITS_IS_MAP_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_MAP_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if given type T is a map-like type
     * (associative container, keyed by its key type).
     *
     * Unlike has_at/has_atnd (positional indexing), map-likeness
     * is not decidable structurally, so the true specialization
     * lives in the header that owns each map type.
     *
     * @tparam T type to check
     */
    template <typename>
    struct is_map : false_type {};

    template <typename T>
    struct is_map<const T> : is_map<T> {};

    template <typename T>
    struct is_map<T&> : is_map<T> {};

    /**
     * @brief helper variable template to check if T is map-like
     *
     * @tparam T type to check
     */
    template <typename T>
    constexpr inline auto is_map_v = is_map<T>::value;

    /**
     * @brief more specific is_map, only true for constant_map
     *
     * @tparam T type to check
     */
    template <typename>
    struct is_constant_map : false_type {};

    template <typename T>
    struct is_constant_map<const T> : is_constant_map<T> {};

    template <typename T>
    struct is_constant_map<T&> : is_constant_map<T> {};

    /**
     * @brief helper variable template to check if T is a constant_map
     *
     * @tparam T type to check
     */
    template <typename T>
    constexpr inline auto is_constant_map_v = is_constant_map<T>::value;
} // namespace nmtools::meta

namespace nmtools
{
    using meta::is_map_v, meta::is_constant_map_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_MAP_HPP
