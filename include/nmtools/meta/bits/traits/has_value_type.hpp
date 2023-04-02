#ifndef NMTOOLS_META_BITS_TRAITS_HAS_VALUE_TYPE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_VALUE_TYPE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    
    /**
     * @brief check if T has member type value_type
     * 
     * @tparam T type to check
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct has_value_type : false_type {};

    // TODO: cleanup metafunctions
    /**
     * @brief specialization when T actually has value_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_value_type<T, void_t<typename T::value_type> > : true_type {};

    /**
     * @brief helper variable template to check if T has member type value_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    nmtools_meta_variable_attribute
    inline constexpr bool has_value_type_v = has_value_type<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_HAS_VALUE_TYPE_HPP