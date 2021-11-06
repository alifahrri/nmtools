#ifndef NMTOOLS_META_BITS_TRAITS_IS_FIXED_INDEX_ARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_FIXED_INDEX_ARRAY_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_index.hpp"

namespace nmtools::meta
{
    /**
     * @brief Check if type T is fixed index array.
     * 
     * A fixed index array represent fixed-dim index/shape.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_fixed_index_array : false_type {};

    template <typename T>
    inline constexpr auto is_fixed_index_array_v = is_fixed_index_array<T>::value;

    template <typename T, size_t N>
    struct is_fixed_index_array<T[N],enable_if_t<is_index_v<T>>> : true_type {};
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRAITS_IS_FIXED_INDEX_ARRAY_HPP