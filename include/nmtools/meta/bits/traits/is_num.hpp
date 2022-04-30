#ifndef NMTOOLS_META_BITS_TRAITS_IS_NUM_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_NUM_HPP

#include "nmtools/meta/bits/traits/is_integer.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_floating_point : false_type {};

    template <typename T>
    constexpr inline auto is_floating_point_v = is_floating_point<T>::value;

#define NMTOOLS_IS_FLOATING_POINT_TRAIT(type) \
    template <> \
    struct is_floating_point<type> : true_type {};

    NMTOOLS_IS_FLOATING_POINT_TRAIT(float32_t)
    NMTOOLS_IS_FLOATING_POINT_TRAIT(float64_t)

#undef NMTOOLS_IS_FLOATING_POINT_TRAIT

    /**
     * @brief Check if type T is num type.
     * 
     * Note that specializing std is_arithmetic is undefined behaviour.
     * This traits exists to avoid UB while specializing similar concept is allowed.
     * THis is useful to allow reduce view that reduce the elements to single num.
     * The name "num" is inspired from haskell's `Num`.
     *
     * @tparam T type tot check
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_num
    {
        static constexpr auto value = is_integer_v<T> || is_floating_point_v<T>;
    };

    template <typename T>
    struct is_num<const T> : is_num<T> {};

    template <typename T>
    struct is_num<T&> : is_num<T> {};

    template <typename T>
    constexpr inline auto is_num_v = is_num<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_NUM_HPP