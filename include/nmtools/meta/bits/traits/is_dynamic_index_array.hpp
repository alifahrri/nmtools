#ifndef NMTOOLS_META_BITS_TRAITS_IS_DYNAMIC_INDEX_ARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_DYNAMIC_INDEX_ARRAY_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_reference.hpp"
#include "nmtools/meta/bits/traits/is_const.hpp"
#include "nmtools/meta/bits/traits/has_address_space.hpp"
#include "nmtools/meta/bits/transform/remove_address_space.hpp"

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
    struct is_dynamic_index_array<const T,enable_if_t<!is_reference_v<T>>> : is_dynamic_index_array<T> {};

    template <typename T>
    struct is_dynamic_index_array<T&,enable_if<!is_const_v<T>>> : is_dynamic_index_array<T> {};

    template <typename T>
    inline constexpr auto is_dynamic_index_array_v = is_dynamic_index_array<T>::value;

    #ifdef __OPENCL_VERSION__
    template <typename T>
    struct is_dynamic_index_array<T,enable_if_t<has_address_space_v<T>>> : is_dynamic_index_array<remove_address_space_t<T>> {};
    #endif // __OPENCL_VERSION__
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_DYNAMIC_INDEX_ARRAY_HPP