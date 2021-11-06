#ifndef NMTOOLS_META_BITS_TRAITS_HAS_DIM_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_DIM_HPP

#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if type `T` has member function `dim`.
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_dim : detail::expression_check<void,expr::dim,T> {};

    /**
     * @brief helper variable template to check if type `T` has member function `dim`.
     * 
     * @tparam T type to check 
     */
    template <typename T>
    inline constexpr bool has_dim_v = has_dim<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_HAS_DIM_HPP