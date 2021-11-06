#ifndef NMTOOLS_META_BITS_TRAITS_IS_BOOLEAN_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_BOOLEAN_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if type T is boolean
     * 
     * @tparam T 
     */
    template <typename T>
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
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_BOOLEAN_HPP