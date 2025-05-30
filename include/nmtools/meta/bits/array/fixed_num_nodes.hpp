#ifndef NMTOOLS_META_BITS_ARRAY_FIXED_NUM_NODES_HPP
#define NMTOOLS_META_BITS_ARRAY_FIXED_NUM_NODES_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_adjacency_list.hpp"
#include "nmtools/meta/bits/transform/len.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct FIXED_NUM_NODES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename T, typename=void>
    struct fixed_num_nodes
    {
        static constexpr auto value = [](){
            if constexpr (!is_adjacency_list_v<T>) {
                using type = error::FIXED_NUM_NODES_UNSUPPORTED<T>;
                return type {};
            } else {
                constexpr auto NUM_NODES = len_v<T>;
                if constexpr (NUM_NODES >= 0) {
                    return NUM_NODES;
                } else {
                    using type = error::FIXED_NUM_NODES_UNSUPPORTED<T>;
                    return type {};
                }
            }
        }();
    };

    template <typename T>
    struct fixed_num_nodes<const T> : fixed_num_nodes<T> {};

    template <typename T>
    struct fixed_num_nodes<T&> : fixed_num_nodes<T> {};

    template <typename T>
    constexpr inline auto fixed_num_nodes_v = fixed_num_nodes<T>::value;
} // nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_FIXED_NUM_NODES_HPP