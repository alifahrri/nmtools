#ifndef NMTOOLS_META_BITS_TRAITS_HAS_TUPLE_SIZE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_TUPLE_SIZE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"

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

    // TODO: enable
    #if 0
    template <template<typename...>typename tuple, typename...Ts>
    struct has_tuple_size<tuple<Ts...>
        , enable_if_t<is_tuple_v<tuple<Ts...>>>
    > : true_type {};
    #endif

    template <typename T>
    struct has_tuple_size<const T> : has_tuple_size<T> {};

    template <typename T>
    struct has_tuple_size<T&> : has_tuple_size<T> {};

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