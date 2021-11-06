#ifndef NMTOOLS_META_BITS_TRAITS_IS_NUM_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_NUM_HPP

#include <type_traits>

namespace nmtools::meta
{
    /**
     * @brief Check if type T is num type.
     * 
     * Note that specializing std::is_arithmetic is undefined behaviour.
     * This traits exists to avoid UB while specializing similar concept is allowed.
     * THis is useful to allow reduce view that reduce the elements to single num.
     * The name "num" is inspired from haskell's `Num`.
     *
     * @tparam T type tot check
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_num : std::is_arithmetic<T> {};

    template <typename T>
    constexpr inline auto is_num_v = is_num<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_NUM_HPP