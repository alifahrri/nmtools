#ifndef NMTOOLS_META_BITS_TRAITS_IS_DYNAMIC_INDEX_ARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_DYNAMIC_INDEX_ARRAY_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief Check if type T is dynamic index array.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_dynamic_index_array : false_type {};

    template <typename T>
    inline constexpr auto is_dynamic_index_array_v = is_dynamic_index_array<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_DYNAMIC_INDEX_ARRAY_HPP