#ifndef NMTOOLS_META_BITS_TRAITS_IS_ADJACENCY_LIST_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_ADJACENCY_LIST_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_list.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/traits/is_index_array.hpp"
#include "nmtools/meta/bits/traits/is_constant_adjacency_list.hpp"
#include "nmtools/meta/bits/transform/get_value_type.hpp"
#include "nmtools/meta/bits/transform/at.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_adjacency_list
    {
        static constexpr auto value = [](){
            using element_t [[maybe_unused]] = get_value_type_t<T>;
            return is_index_array_v<element_t>;
        }();
    };

    template <template<typename...>typename tuple, typename...args>
    struct is_adjacency_list<tuple<args...>,enable_if_t<is_tuple_v<tuple<args...>>>>
    {
        static constexpr auto value = is_constant_adjacency_list_v<tuple<args...>> || (is_index_array_v<args> && ...);
    };

    template <typename T>
    struct is_adjacency_list<const T> : is_adjacency_list<T> {};

    template <typename T>
    struct is_adjacency_list<T&> : is_adjacency_list<T> {};

    template <typename T>
    inline constexpr auto is_adjacency_list_v = is_adjacency_list<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_ADJACENCY_LIST_HPP