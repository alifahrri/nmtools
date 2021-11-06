#ifndef NMTOOLS_META_BITS_TRAITS_IS_INTEGER_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_INTEGER_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief Check if type T is integer type.
     * 
     * Note that specializing std::is_integral is undefined behaviour.
     * This traits exists to avoid UB while specializing similar concept is allowed.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_integer : false_type {};

    template <typename T>
    constexpr inline auto is_integer_v = is_integer<T>::value;

    template <typename T, typename=void>
    struct is_integral : is_integer<T> {};

    template <typename T>
    constexpr inline auto is_integral_v = is_integral<T>::value;

#define NMTOOLS_IS_INTEGER_TRAIT(type) \
    template <> \
    struct is_integer<type> : true_type {};

    NMTOOLS_IS_INTEGER_TRAIT(short int)
    NMTOOLS_IS_INTEGER_TRAIT(unsigned short int)

    NMTOOLS_IS_INTEGER_TRAIT(int)
    NMTOOLS_IS_INTEGER_TRAIT(unsigned int)

    NMTOOLS_IS_INTEGER_TRAIT(long int)
    NMTOOLS_IS_INTEGER_TRAIT(unsigned long int)

    NMTOOLS_IS_INTEGER_TRAIT(long long int)
    NMTOOLS_IS_INTEGER_TRAIT(unsigned long long int)

#undef NMTOOLS_IS_INTEGER_TRAIT
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_INTEGER_HPP