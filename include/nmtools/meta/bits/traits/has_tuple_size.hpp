#ifndef NMTOOLS_META_BITS_TRAITS_HAS_TUPLE_SIZE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_TUPLE_SIZE_HPP

#include "nmtools/meta/common.hpp"
#include <type_traits>

namespace nmtools::meta
{
    /**
     * @brief check if std::tuple_size<T> is valid for T
     * should be true for std::array, std::tuple, std::pair
     * 
     * @tparam T 
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct has_tuple_size : false_type {};

    // TODO: remove metafunctions
    /**
     * @brief specialization of has_tuple_size when tuple_size<T> is well-formed
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_tuple_size<T, std::void_t<typename std::tuple_size<T>::type>> : true_type {};

    /**
     * @brief helper variable template to check if std::tuple_size<T> is valid
     * 
     * @todo test
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool has_tuple_size_v = has_tuple_size<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_HAS_TUPLE_SIZE_HPP