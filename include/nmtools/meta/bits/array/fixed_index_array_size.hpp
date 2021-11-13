#ifndef NMTOOLS_META_BITS_ARRAY_FIXED_INDEX_ARRAY_SIZE_HPP
#define NMTOOLS_META_BITS_ARRAY_FIXED_INDEX_ARRAY_SIZE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_index.hpp"

namespace nmtools::meta
{
    // TODO: maybe simplify this trait using len_v
    // TODO: do not directly use detail::fail_t,
    // define specific error type instead
    /**
     * @brief Return the length of fixed index array.
     *
     * By default, return fail_t type.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct fixed_index_array_size
    {
        static constexpr auto value = detail::fail_t{};
    };

    template <typename T, size_t N>
    struct fixed_index_array_size<T[N],enable_if_t<is_index_v<T>>>
    {
        static constexpr auto value = N;
    };

    template <typename T>
    static constexpr auto fixed_index_array_size_v = fixed_index_array_size<T>::value;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_ARRAY_FIXED_INDEX_ARRAY_SIZE_HPP