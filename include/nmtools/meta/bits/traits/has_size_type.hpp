#ifndef NMTOOLS_META_BITS_TRAITS_HAS_SIZE_TYPE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_SIZE_TYPE_HPP

#include "nmtools/meta/common.hpp"
#include <type_traits>

namespace nmtools::meta
{
    // TODO: remove metafunctions
    /**
     * @brief check if type T has member type size_type
     * 
     * @tparam T type to check
     * @tparam void 
     */
    template <typename T, typename = void>
    struct has_size_type : false_type {};

    /**
     * @brief specialization when T actually size_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_size_type<T,
        std::void_t<typename T::size_type>
    > : true_type {};

    // TODO: remove metafunctions
    /**
     * @brief helper variable template to check if T has size_type
     * 
     * @tparam T 
     */
    template <typename T>
    inline constexpr bool has_size_type_v = has_size_type<T>::value;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRAITS_HAS_SIZE_TYPE_HPP