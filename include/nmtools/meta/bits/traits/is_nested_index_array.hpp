#ifndef NMTOOLS_META_BITS_TRAITS_IS_NESTED_INDEX_ARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_NESTED_INDEX_ARRAY_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/traits/is_fixed_index_array.hpp"
#include "nmtools/meta/bits/traits/is_dynamic_index_array.hpp"
#include "nmtools/meta/bits/traits/is_constant_index_array.hpp"
#include "nmtools/meta/bits/traits/is_hybrid_index_array.hpp"
#include "nmtools/meta/bits/traits/is_nullable_index_array.hpp"
// NOTE: avoid using this directly to avoid circular include
// #include "nmtools/meta/bits/traits/is_index_array.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_nested_index_array : false_type {};

    template <typename T>
    struct is_nested_index_array<const T> : is_nested_index_array<T> {};

    template <typename T>
    struct is_nested_index_array<T&> : is_nested_index_array<T> {};

    template <template<typename...>typename tuple, typename...args_t>
    struct is_nested_index_array<
        tuple<args_t...>
        , enable_if_t<is_tuple_v<tuple<args_t...>>>
    > {
        static constexpr auto value = ((is_fixed_index_array_v<args_t> || is_dynamic_index_array_v<args_t> || is_constant_index_array_v<args_t> || is_hybrid_index_array_v<args_t> || is_nullable_index_array_v<args_t>) || ...);
    };

    template <typename T>
    constexpr inline auto is_nested_index_array_v = is_nested_index_array<T>::value;
}

namespace nmtools
{
    using meta::is_nested_index_array_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_NESTED_INDEX_ARRAY_HPP