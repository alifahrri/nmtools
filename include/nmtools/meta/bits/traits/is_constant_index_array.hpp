#ifndef NMTOOLS_META_BITS_TRAITS_IS_CONSTANT_INDEX_ARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_CONSTANT_INDEX_ARRAY_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief Check if type T is constant index array.
     * 
     * A constant index array represent index/shape at compile-time.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_constant_index_array : false_type {};

    template <typename T>
    struct is_constant_index_array<const T> : is_constant_index_array<T> {};

    template <typename T>
    struct is_constant_index_array<T&> : is_constant_index_array<T> {};

    template <typename T>
    inline constexpr auto is_constant_index_array_v = is_constant_index_array<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_CONSTANT_INDEX_ARRAY_HPP