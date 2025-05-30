#ifndef NMTOOLS_NETWORK_HAS_PATH_HPP
#define NMTOOLS_NETWORK_HAS_PATH_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/contains.hpp"

namespace nmtools::tag
{
    struct has_path_visited_t {};
    struct has_path_stack_t {};
}

namespace nmtools::network
{
    template <typename adjacency_list_t, typename start_t, typename end_t>
    constexpr auto has_path(const adjacency_list_t& adj_list, start_t start_node, end_t end_node)
    {
        if constexpr (meta::is_maybe_v<adjacency_list_t>
            || meta::is_maybe_v<start_t>
            || meta::is_maybe_v<end_t>
        ) {
            using result_t = decltype(has_path(unwrap(adj_list),unwrap(start_node),unwrap(end_node)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adj_list) && has_value(start_node) && has_value(end_node)
                ? return_t{has_path(unwrap(adj_list),unwrap(start_node),unwrap(end_node))}
                : return_t{meta::Nothing}
            );
        } else {
            using visited_t = meta::resolve_optype_t<tag::has_path_visited_t,adjacency_list_t,start_t,end_t>;
            using stack_t   = meta::resolve_optype_t<tag::has_path_stack_t,adjacency_list_t,start_t,end_t>;

            // TODO: handle visited_t and stack_t failure

            auto visited = visited_t {};
            auto stack   = stack_t {};

            if (len(adj_list)) {
                stack.push(start_node);
            }

            auto has_path = false;
            while (!stack.empty()) {
                auto current_node = stack.pop();
                if (current_node == end_node) {
                    has_path = true;
                    break;
                }
                if (!index::contains(visited,current_node)) {
                    visited.push_back(current_node);

                    // const auto& neighbors = at(adj_list,current_node);
                    // for (const auto& neighbor : neighbors) {
                    for (auto neighbor : adj_list[current_node]) {
                        if (!index::contains(visited,neighbor)) {
                            stack.push(neighbor);
                        }
                    }
                }
            }
            return has_path;
        }
    } // has_path
} // namespace nmtools::network

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct HAS_PATH_VISITED_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct HAS_PATH_STACK_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t, typename start_t, typename end_t>
    struct resolve_optype<
        void, tag::has_path_visited_t, adjacency_list_t, start_t, end_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>
                || !is_index_v<start_t> || !is_index_v<end_t>
            ) {
                using type = error::HAS_PATH_VISITED_UNSUPPORTED<adjacency_list_t,start_t,end_t>;
                return as_value_v<type>;
            } else {
                // TODO: deduce index type from adjacency_list_t
                using index_t = nm_index_t;
                constexpr auto NUM_NODES = len_v<adjacency_list_t>;
                // TODO: properly support bounded_size_v for std::array<static_vector<T,M>,N>
                [[maybe_unused]]
                constexpr auto B_NUM_NODES = bounded_size_v<adjacency_list_t>;
                if constexpr (NUM_NODES > 0) {
                    using type = nmtools_static_vector<index_t,NUM_NODES>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_NUM_NODES)>) {
                    using type = nmtools_static_vector<index_t,B_NUM_NODES>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename adjacency_list_t, typename start_t, typename end_t>
    struct resolve_optype<
        void, tag::has_path_stack_t, adjacency_list_t, start_t, end_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>
                || !is_index_v<start_t> || !is_index_v<end_t>
            ) {
                using type = error::HAS_PATH_STACK_UNSUPPORTED<adjacency_list_t,start_t,end_t>;
                return as_value_v<type>;
            } else {
                // TODO: deduce index type from adjacency_list_t
                using index_t = nm_index_t;
                constexpr auto NUM_NODES = len_v<adjacency_list_t>;
                // TODO: properly support bounded_size_v for std::array<static_vector<T,M>,N>
                [[maybe_unused]]
                constexpr auto B_NUM_NODES = bounded_size_v<adjacency_list_t>;
                if constexpr (NUM_NODES > 0) {
                    // worst-case is all connected graph
                    constexpr auto N = NUM_NODES * NUM_NODES;
                    using type = nmtools_static_stack<index_t,N>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_NUM_NODES)>) {
                    // worst-case is all connected graph
                    constexpr auto N = B_NUM_NODES * B_NUM_NODES;
                    using type = nmtools_static_stack<index_t,N>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_stack<index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_NETWORK_HAS_PATH_HPP