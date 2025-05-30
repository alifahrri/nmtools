#ifndef NMTOOLS_META_BITS_TRAITS_IS_CONSTANT_ADJACENCY_LIST_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_CONSTANT_ADJACENCY_LIST_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/traits/is_constant_index_array.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_constant_adjacency_list : false_type {};

    template <template<typename...>typename tuple, typename...args>
    struct is_constant_adjacency_list<tuple<args...>,enable_if_t<is_tuple_v<tuple<args...>>>>
    {
        static constexpr auto value = [](){
            if constexpr ((is_constant_index_array_v<args> && ...)) {
                return true;
            } else {
                return false;
            }
        }();
    };

    template <typename T>
    struct is_constant_adjacency_list<const T> : is_constant_adjacency_list<T> {};

    template <typename T>
    struct is_constant_adjacency_list<T&> : is_constant_adjacency_list<T> {};

    template <typename T>
    constexpr inline auto is_constant_adjacency_list_v = is_constant_adjacency_list<T>::value;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_CONSTANT_ADJACENCY_LIST_HPP