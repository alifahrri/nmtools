#ifndef NMTOOLS_META_BITS_TRAITS_IS_VIEW_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_VIEW_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief helper trait to check if type T is view
     * 
     * @tparam T type to check
     * @tparam typename sfinae/customization point
     */
    template <typename T, typename=void>
    struct is_view : false_type {};

    /**
     * @brief helper variable template to check if type T is view
     * 
     * @tparam T type to check
     */
    template <typename T>
    nmtools_meta_variable_attribute
    static inline constexpr bool is_view_v = is_view<T>::value;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_VIEW_HPP