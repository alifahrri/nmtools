#ifndef NMTOOLS_META_BITS_TRAITS_HAS_RESERVE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_RESERVE_HPP

#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if type `T` has member function `dim`.
     * 
     * @tparam T type to check
     */
    template <typename T, typename size_type=size_t>
    struct has_reserve : detail::expression_check<void,expr::reserve,T,size_type> {};

    /**
     * @brief helper variable template to check if type `T` has member function `dim`.
     * 
     * @tparam T type to check 
     */
    template <typename T>
    nmtools_meta_variable_attribute
    inline constexpr bool has_reserve_v = has_reserve<T>::value;
}

#endif // NMTOOLS_META_BITS_TRAITS_HAS_RESERVE_HPP