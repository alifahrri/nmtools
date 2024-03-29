#ifndef NMTOOLS_META_BITS_TRAITS_HAS_SIZE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_SIZE_HPP

#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if type `T` has member function `size`.
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_size : detail::expression_check<void,expr::size,T> {};

    template <typename T>
    struct has_size<const T> : has_size<T> {};

    template <typename T>
    struct has_size<T&> : has_size<T> {};

    /**
     * @brief helper variable template to check if type `T` has member function `size`.
     * 
     * @tparam T type to check 
     */
    template <typename T>
    nmtools_meta_variable_attribute
    inline constexpr bool has_size_v = has_size<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_HAS_SIZE_HPP