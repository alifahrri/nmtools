#ifndef NMTOOLS_META_BITS_TRAITS_IS_INDEX_ARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_INDEX_ARRAY_HPP

#include "nmtools/meta/bits/traits/is_fixed_index_array.hpp"
#include "nmtools/meta/bits/traits/is_dynamic_index_array.hpp"
#include "nmtools/meta/bits/traits/is_constant_index_array.hpp"
#include "nmtools/meta/bits/traits/is_hybrid_index_array.hpp"
#include "nmtools/meta/bits/traits/is_nullable_index_array.hpp"
#include "nmtools/meta/bits/traits/has_address_space.hpp"
#include "nmtools/meta/bits/transform/remove_address_space.hpp"

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
                || is_hybrid_index_array_v<T>
                || is_nullable_index_array_v<T>
            ;
        }();
    };

    template <typename T>
    struct is_index_array<const T,enable_if_t<!has_address_space_v<T>>> : is_index_array<T> {};

    template <typename T>
    struct is_index_array<T&> : is_index_array<T> {};

    template <typename T>
    constexpr inline auto is_index_array_v = is_index_array<T>::value;

    template <typename T>
    struct is_index_array<T,enable_if_t<has_address_space_v<T>>> : is_index_array<remove_address_space_t<T>> {};
} // namespace nmtools::meta

namespace nmtools
{
    using meta::is_index_array_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_INDEX_ARRAY_HPP