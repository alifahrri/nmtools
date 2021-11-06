#ifndef NMTOOLS_META_BITS_TRAITS_HAS_SHAPE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_SHAPE_HPP

#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if type `T` has member function `shape`.
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_shape : detail::expression_check<void,expr::shape,T> {};

    /**
     * @brief helper variable template to check if type `T` has member function `shape`.
     * 
     * @tparam T type to check 
     */
    template <typename T>
    inline constexpr bool has_shape_v = has_shape<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_HAS_SHAPE_HPP