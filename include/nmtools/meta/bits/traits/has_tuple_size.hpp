#ifndef NMTOOLS_META_BITS_TRAITS_HAS_TUPLE_SIZE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_TUPLE_SIZE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    // TODO: remove, use len instead
    /**
     * @brief check if std tuple_size<T> is valid for T
     * should be true for array, tuple, pair
     * 
     * @tparam T 
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct has_tuple_size : false_type {};

    /**
     * @brief helper variable template to check if std tuple_size<T> is valid
     * 
     * @todo test
     * @tparam T type to check
     */
    template <typename T>
    nmtools_meta_variable_attribute
    inline constexpr bool has_tuple_size_v = has_tuple_size<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_HAS_TUPLE_SIZE_HPP