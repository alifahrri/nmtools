#ifndef NMTOOLS_META_BITS_TRAITS_HAS_TYPE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_TYPE_HPP

#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if type T has member type 'type'
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_type : detail::expression_check<void,expr::type,T> {};

    /**
     * @brief helper variable template to check if type T has member type 'type'
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool has_type_v = has_type<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_HAS_TYPE_HPP