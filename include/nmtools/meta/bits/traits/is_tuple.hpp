#ifndef NMTOOLS_META_BITS_TRAITS_IS_TUPLE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_TUPLE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if given type is tuple kind.
     *
     * Note that this is not necessarily std tuple,
     * this is intended to be more like tuple in concept.
     * The choice of the name, tuple, is from haskell Tuple.
     */
    template <typename>
    struct is_tuple : false_type {};

    // const and ref should be ok, most use case check for tuple do not care if it's const or ref
    template <typename T>
    struct is_tuple<const T> : is_tuple<T> {};

    template <typename T>
    struct is_tuple<T&> : is_tuple<T> {};

    /**
     * @brief helper variable template to check if given type is tuple
     * 
     */
    template <typename ...Args>
    nmtools_meta_variable_attribute
    inline constexpr bool is_tuple_v = is_tuple<Args...>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_TUPLE_HPP