#ifndef NMTOOLS_META_BITS_TRAITS_HAS_RESULT_TYPE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_RESULT_TYPE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if type T has member type result_type
     * 
     * @tparam T type to check
     * @tparam void 
     */
    template <typename T, typename = void>
    struct has_result_type : false_type {};

    /**
     * @brief specialization when T actually result_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_result_type<T,
        void_t<typename T::result_type>
    > : true_type {};

    /**
     * @brief helper variable template to check if T has result_type
     * 
     * @tparam T 
     */
    template <typename T>
    nmtools_meta_variable_attribute
    inline constexpr bool has_result_type_v = has_result_type<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_HAS_RESULT_TYPE_HPP