#ifndef NMTOOLS_META_BITS_TRAITS_IS_INDEX_ARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_INDEX_ARRAY_HPP

#include "nmtools/meta/bits/traits/is_fixed_index_array.hpp"
#include "nmtools/meta/bits/traits/is_dynamic_index_array.hpp"
#include "nmtools/meta/bits/traits/is_constant_index_array.hpp"
#include "nmtools/meta/bits/traits/is_hybrid_index_array.hpp"

namespace nmtools::meta
{
    /**
     * @brief Check if type `T` is index array
     * 
     * @tparam T type to check
     */
    template <typename T, typename=void>
    struct is_index_array
    {
        static constexpr auto value = [](){
            return is_fixed_index_array_v<T>
                || is_dynamic_index_array_v<T>
                || is_constant_index_array_v<T>
                || is_hybrid_index_array_v<T>;
        }();
    };

    template <typename T>
    constexpr inline auto is_index_array_v = is_index_array<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_INDEX_ARRAY_HPP