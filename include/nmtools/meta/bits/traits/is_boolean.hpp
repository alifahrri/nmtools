#ifndef NMTOOLS_META_BITS_TRAITS_IS_BOOLEAN_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_BOOLEAN_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/has_address_space.hpp"
#include "nmtools/meta/bits/transform/remove_address_space.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if type T is boolean
     * 
     * @tparam T 
     */
    template <typename T, typename=void>
    struct is_boolean : false_type {};

    template <typename T>
    inline constexpr auto is_boolean_v = is_boolean<T>::value;

    /**
     * @brief specialization of is_boolean for actual boolean type
     * 
     * @tparam  
     */
    template <>
    struct is_boolean<bool> : true_type {};

    template <typename T>
    struct is_boolean<T,enable_if_t<has_address_space_v<T>>> : is_boolean<remove_address_space_t<T>> {};
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_BOOLEAN_HPP