#ifndef NMTOOLS_META_BITS_TRAITS_IS_BOUNDED_ARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_BOUNDED_ARRAY_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if T is bounded array
     * 
     * @tparam T 
     */
    template<typename T>
    struct is_bounded_array: false_type {};
    
    template<typename T, size_t N>
    struct is_bounded_array<T[N]> : true_type {};

    /**
     * @brief helper variable template to check if T is bounded array
     * 
     * @tparam T 
     */
    template <typename T>
    inline constexpr bool is_bounded_array_v = is_bounded_array<T>::value;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRAITS_IS_BOUNDED_ARRAY_HPP