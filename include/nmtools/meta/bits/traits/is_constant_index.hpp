#ifndef NMTOOLS_META_BITS_TRAITS_IS_CONSTANT_INDEX_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_CONSTANT_INDEX_HPP

#include "nmtools/meta/bits/traits/is_integral_constant.hpp"

namespace nmtools::meta
{
    /**
     * @brief Check if type T is compile-time index.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_constant_index : is_integral_constant<T> {}; 

    template <typename T>
    struct is_constant_index<const T> : is_constant_index<T> {};

    template <typename T>
    struct is_constant_index<T&> : is_constant_index<T> {};

    template <typename T>
    inline constexpr auto is_constant_index_v = is_constant_index<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_CONSTANT_INDEX_HPP