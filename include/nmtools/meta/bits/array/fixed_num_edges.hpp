#ifndef NMTOOLS_META_BITS_ARRAY_FIXED_NUM_EDGES_HPP
#define NMTOOLS_META_BITS_ARRAY_FIXED_NUM_EDGES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/meta/bits/traits/is_adjacency_list.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/array/fixed_num_nodes.hpp"
#include "nmtools/meta/bits/transform/get_value_type.hpp"
#include "nmtools/meta/bits/transform/len.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct FIXED_NUM_EDGES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename T, typename=void>
    struct fixed_num_edges
    {
        static constexpr auto value = [](){
            using error_type [[maybe_unused]] = error::FIXED_NUM_EDGES_UNSUPPORTED<T>;
            using value_type [[maybe_unused]] = get_value_type_t<T>;
            [[maybe_unused]] constexpr auto NUM_NODES = fixed_num_nodes_v<T>;
            if constexpr (!is_adjacency_list_v<T> || is_fail_v<decltype(NUM_NODES)>) {
                // non fixed num nodes can't have fixed num edges
                return error_type {};
            } else if constexpr (is_tuple_v<T>) {
                nm_size_t num_edges = 0;
                meta::template_for<NUM_NODES>([&](auto I){
                    constexpr auto i = decltype(I)::value;
                    using neighbors_t = at_t<T,i>;
                    num_edges += len_v<neighbors_t>;
                });
                return num_edges;
            } else if constexpr (!is_fail_v<value_type>) {
                // array
                constexpr auto NUM_NEIGHBORS = len_v<value_type>;
                if constexpr (NUM_NEIGHBORS > 0) {
                    // total number of edges
                    return NUM_NODES * NUM_NEIGHBORS;
                } else {
                    return error_type {};
                }
            } else {
                return error_type {};
            }
        }();
    };

    template <typename T>
    struct fixed_num_edges<const T> : fixed_num_edges<T> {};

    template <typename T>
    struct fixed_num_edges<T&> : fixed_num_edges<T> {};

    template <typename T>
    constexpr inline auto fixed_num_edges_v = fixed_num_edges<T>::value;
}

#endif // NMTOOLS_META_BITS_ARRAY_FIXED_NUM_EDGES_HPP