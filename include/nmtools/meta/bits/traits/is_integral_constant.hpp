#ifndef NMTOOLS_META_BITS_TRAITS_IS_INTEGRAL_CONSTANT_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_INTEGRAL_CONSTANT_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if given type T is std::integral_constant
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct is_integral_constant : false_type {};

    template <typename T>
    struct is_integral_constant<const T> : is_integral_constant<T> {};

    template <typename T>
    struct is_integral_constant<const T&> : is_integral_constant<T> {}; 

    /**
     * @brief helper inline variable to check if given type T is std::integral_constant
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool is_integral_constant_v = is_integral_constant<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_INTEGRAL_CONSTANT_HPP