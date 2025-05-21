#ifndef NMTOOLS_META_BITS_ARRAY_BOUNDED_NUM_EDGES_HPP
#define NMTOOLS_META_BITS_ARRAY_BOUNDED_NUM_EDGES_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/array/fixed_num_edges.hpp"
#include "nmtools/meta/bits/array/bounded_size.hpp"
#include "nmtools/meta/bits/traits/is_adjacency_list.hpp"
#include "nmtools/meta/bits/transform/len.hpp"
#include "nmtools/meta/bits/transform/max_len.hpp"
#include "nmtools/meta/bits/transform/get_value_type.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct BOUNDED_NUM_EDGES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename T, typename=void>
    struct bounded_num_edges
    {
        static constexpr auto value = [](){
            using value_type [[maybe_unused]] = get_value_type_t<T>;
            using error_type [[maybe_unused]] = error::BOUNDED_NUM_EDGES_UNSUPPORTED<T>;
            [[maybe_unused]] constexpr auto NUM_NODES = len_v<T>;
            [[maybe_unused]] constexpr auto NUM_EDGES = fixed_num_edges_v<T>;
            [[maybe_unused]] constexpr auto B_NUM_NODES = max_len_v<T>;
            if constexpr (!is_adjacency_list_v<T>) {
                return error_type {};
            } else if constexpr (!is_fail_v<decltype(NUM_EDGES)>) {
                return NUM_EDGES;
            } else {
                // fixed num nodes adj list can still be bounded on edges
                // worst-case is bounded nodes ^ 2
                // read each element/value type to determine max size
                if constexpr (is_tuple_v<T>) {
                    return template_reduce<NUM_NODES>([](auto init, auto index){
                        constexpr auto I = decltype(index)::value;
                        using neighbor_t = at_t<T,I>;
                        constexpr auto B_NUM_NEIGHBORS = bounded_size_v<neighbor_t>;
                        if constexpr (is_fail_v<decltype(B_NUM_NEIGHBORS)>) {
                            return error_type {};
                        } else if constexpr (!is_fail_v<decltype(init)>) {
                            return init + B_NUM_NEIGHBORS;
                        } else {
                            return init;
                        }
                    }, 0);
                } else if constexpr (!is_fail_v<value_type> && (B_NUM_NODES > 0)) {
                    constexpr auto B_NUM_NEIGHBORS = bounded_size_v<value_type>;
                    if constexpr (!is_fail_v<decltype(B_NUM_NEIGHBORS)>) {
                        return B_NUM_NODES * B_NUM_NEIGHBORS;
                    } else {
                        return B_NUM_NODES * B_NUM_NODES;
                    }
                } else {
                    return error_type {};
                }
            }
        }();
    };

    template <typename T>
    struct bounded_num_edges<const T> : bounded_num_edges<T> {};

    template <typename T>
    struct bounded_num_edges<T&> : bounded_num_edges<T> {};

    template <typename T>
    constexpr inline auto bounded_num_edges_v = bounded_num_edges<T>::value;
}

#endif // NMTOOLS_META_BITS_ARRAY_BOUNDED_NUM_EDGES_HPP