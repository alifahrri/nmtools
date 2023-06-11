#ifndef NMTOOLS_META_BITS_TRAITS_IS_HYBRID_INDEX_ARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_HYBRID_INDEX_ARRAY_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/array/bounded_size.hpp"
#include "nmtools/meta/bits/traits/is_integer.hpp"
#include "nmtools/meta/bits/traits/is_boolean.hpp"
#include "nmtools/meta/bits/traits/has_address_space.hpp"
#include "nmtools/meta/bits/transform/remove_address_space.hpp"
#include "nmtools/meta/bits/transform/get_element_type.hpp"

namespace nmtools::meta
{
    /**
     * @brief Check if type T is hybrid_index_array.
     *
     * Has max size but resizable.
     * Note that the max size represents maximum "dimension" of the array
     * instead of maximum "element" of the array.
     * Currently querying maximum "element" of an hybrid array
     * from the index/shape array is not supported.
     * 
     * @tparam T type to check
     */
    template <typename T, typename=void>
    struct is_hybrid_index_array : false_type {};

    template <typename T>
    struct is_hybrid_index_array<const T> : is_hybrid_index_array<T> {};

    template <typename T>
    struct is_hybrid_index_array<T&> : is_hybrid_index_array<T> {};

    template <typename T>
    inline constexpr auto is_hybrid_index_array_v = is_hybrid_index_array<T>::value;

    #ifdef __OPENCL_VERSION__
    template <typename T>
    struct is_hybrid_index_array<T,enable_if_t<has_address_space_v<T>>> : is_hybrid_index_array<remove_address_space_t<T>> {};
    #endif // __OPENCL_VERSION__
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_HYBRID_INDEX_ARRAY_HPP