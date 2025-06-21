#ifndef NMTOOLS_NETWORK_IS_DIRECTED_ACYCLIC_GRAPH_HPP
#define NMTOOLS_NETWORK_IS_DIRECTED_ACYCLIC_GRAPH_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"

namespace nmtools::tag
{
    struct is_directed_acyclic_graph_t {};
}

namespace nmtools::network
{
    template <typename adjacency_list_t>
    constexpr auto is_directed_acyclic_graph(const adjacency_list_t& adj_list)
    {
        if constexpr (meta::is_maybe_v<adjacency_list_t>) {
            using result_t = decltype(is_directed_acyclic_graph(unwrap(adj_list)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adj_list)
                ? return_t{is_directed_acyclic_graph(unwrap(adj_list))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::is_directed_acyclic_graph_t,adjacency_list_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_index_v<result_t>
            ) {
                result = true;

                auto visited_vtype = [](){
                    constexpr auto B_NUM_NODES = meta::max_len_v<adjacency_list_t>;
                    using index_t = nm_size_t;
                    if constexpr (B_NUM_NODES >= 0) {
                        using type = nmtools_static_vector<index_t,B_NUM_NODES>;
                        return meta::as_value_v<type>;
                    } else {
                        // TODO: use small vector?
                        using type = nmtools_list<index_t>;
                        return meta::as_value_v<type>;
                    }
                }();
                using visited_t = meta::type_t<decltype(visited_vtype)>;

                auto stack_vtype = [](){
                    constexpr auto B_NUM_NODES = meta::max_len_v<adjacency_list_t>;
                    using index_t = nm_size_t;
                    if constexpr (B_NUM_NODES >= 0) {
                        // TODO: should be only B_NUM_NODES max?
                        using type = nmtools_static_stack<index_t,B_NUM_NODES*B_NUM_NODES>;
                        return meta::as_value_v<type>;
                    } else {
                        // TODO: use small vector?
                        using type = nmtools_stack<index_t>;
                        return meta::as_value_v<type>;
                    }
                }();
                using stack_t = meta::type_t<decltype(stack_vtype)>;

                constexpr auto WHITE = 0;
                constexpr auto GRAY  = 1;
                constexpr auto BLACK = 2;

                auto color = visited_t {};

                auto num_nodes = len(adj_list);
                if constexpr (meta::is_resizable_v<visited_t>) {
                    color.resize(num_nodes);
                }

                for (nm_size_t i=0; (i<(nm_size_t)num_nodes) && result; i++) {
                    if ((nm_size_t)at(color,i) == (nm_size_t)WHITE) {
                        auto stack = stack_t {};

                        stack.push(i);
                        while (!stack.empty() && result) {
                            auto node = stack.top();

                            if ((nm_size_t)at(color,node) == (nm_size_t)WHITE) {
                                at(color,node) = GRAY;
                            }

                            auto has_white_neighbor = false;
                            const auto& neighbors = at(adj_list,node);
                            for (nm_size_t i=0; i<(nm_size_t)len(neighbors) && result; i++) {
                                auto neighbor = at(neighbors,i);
                                if ((nm_size_t)at(color,neighbor) == (nm_size_t)GRAY) {
                                    result = false;
                                    break;
                                }
                                if ((nm_size_t)at(color,neighbor) == (nm_size_t)WHITE) {
                                    stack.push(neighbor);
                                    has_white_neighbor = true;
                                    break;
                                }
                            }
                            if (!has_white_neighbor) {
                                at(color,node) = BLACK;
                                stack.pop();
                            }
                        }
                    }
                }
            }

            return result;
        }
    }
}

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct IS_DIRECTED_ACYCLIC_GRAPH_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t>
    struct resolve_optype<
        void, tag::is_directed_acyclic_graph_t, adjacency_list_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>) {
                using type = error::IS_DIRECTED_ACYCLIC_GRAPH_UNSUPPORTED<adjacency_list_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_adjacency_list_v<adjacency_list_t>) {
                constexpr auto adj_list = to_value_v<adjacency_list_t>;
                constexpr auto result = network::is_directed_acyclic_graph(adj_list);
                using type = ct<unwrap(result)>;
                return as_value_v<type>;
            } else {
                using type = nm_bool_t;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_NETWORK_IS_DIRECTED_ACYCLIC_GRAPH_HPP