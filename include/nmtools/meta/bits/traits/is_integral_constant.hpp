#ifndef NMTOOLS_META_BITS_TRAITS_IS_INTEGRAL_CONSTANT_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_INTEGRAL_CONSTANT_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if given type T is integral_constant
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct is_integral_constant : false_type {};

    template <typename T, T v>
    struct is_integral_constant<integral_constant<T,v>> : true_type {};

    template <typename T>
    struct is_integral_constant<const T> : is_integral_constant<T> {};

    template <typename T>
    struct is_integral_constant<const T&> : is_integral_constant<T> {}; 

    // true_type and false_type is not implemented using integral constant (it is inherited from, but not an alias)
    // this make tuple of ct True/False are not considered constant index array
    template<> struct is_integral_constant<true_type> : true_type {}; 
    template<> struct is_integral_constant<false_type> : true_type {}; 

    /**
     * @brief helper inline variable to check if given type T is integral_constant
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool is_integral_constant_v = is_integral_constant<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_INTEGRAL_CONSTANT_HPP