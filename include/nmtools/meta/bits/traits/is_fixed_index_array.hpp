#ifndef NMTOOLS_META_BITS_TRAITS_IS_FIXED_INDEX_ARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_FIXED_INDEX_ARRAY_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_index.hpp"
#include "nmtools/meta/bits/traits/is_reference.hpp"
#include "nmtools/meta/bits/traits/is_const.hpp"
#include "nmtools/meta/bits/traits/has_address_space.hpp"
#include "nmtools/meta/bits/transform/remove_address_space.hpp"

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
    struct is_fixed_index_array<const T> : is_fixed_index_array<T> {};

    template <typename T>
    struct is_fixed_index_array<T&> : is_fixed_index_array<T> {};

    template <typename T>
    inline constexpr auto is_fixed_index_array_v = is_fixed_index_array<T>::value;

    template <typename T, size_t N>
    struct is_fixed_index_array<T[N],enable_if_t<is_index_v<T>>> : true_type {};

    #ifdef __OPENCL_VERSION__
    template <typename T>
    struct is_fixed_index_array<T,enable_if_t<has_address_space_v<T>>> : is_fixed_index_array<remove_address_space_t<T>> {};
    #endif // __OPENCL_VERSION__
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRAITS_IS_FIXED_INDEX_ARRAY_HPP