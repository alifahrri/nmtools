#ifndef NMTOOLS_NETWORK_SUBGRAPH_HPP
#define NMTOOLS_NETWORK_SUBGRAPH_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/utl/static_map.hpp"

namespace nmtools::network
{
    struct subgraph_t {};

    template <typename adjacency_list_t, typename nodes_t>
    constexpr auto subgraph(const adjacency_list_t& adj_list, const nodes_t& nodes)
    {
        if constexpr (is_maybe_v<nodes_t>
            || is_maybe_v<adjacency_list_t>
        ) {
            using result_t = decltype(subgraph(unwrap(adj_list),unwrap(nodes)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adj_list) && has_value(nodes)
                ? return_t{subgraph(unwrap(adj_list),unwrap(nodes))}
                : return_t{Nothing}
            );
        } else {
            using result_t = resolve_optype_t<subgraph_t,adjacency_list_t,nodes_t>;

            auto result = result_t {};

            if constexpr (!is_fail_v<result_t>
                && !is_constant_adjacency_list_v<result_t>
            ) {
                [[maybe_unused]]
                auto src_num_nodes = len(adj_list);
                auto dst_num_nodes = len(nodes);

                using inner_t = get_value_type_t<result_t>;

                constexpr auto mapping_vtype = [](){
                    constexpr auto MAX_NODES = max_len_v<nodes_t>;
                    // TODO: parametrize map
                    if constexpr (MAX_NODES > 0) {
                        using type = utl::static_map<nm_size_t,nm_size_t,MAX_NODES>;
                        return as_value_v<type>;
                    } else {
                        using type = nmtools_default_map<nm_size_t,nm_size_t>;
                        return as_value_v<type>;
                    }
                }();
                using mapping_t = type_t<decltype(mapping_vtype)>;

                auto mapping = mapping_t{};
                for (nm_size_t i=0; i<(nm_size_t)dst_num_nodes; i++) {
                    auto idx = at(nodes,i);
                    mapping[idx] = i;
                }
                
                // TODO: make sure src_num_nodes > dst_num_nodes
                // TODO: check all indices of nodes < src_num_nodes

                if constexpr (is_resizable_v<result_t>) {
                    result.resize(dst_num_nodes);
                }

                for (nm_size_t i=0; i<(nm_size_t)dst_num_nodes; i++) {
                    auto idx = at(nodes,i);
                    auto neighbors = inner_t {};

                    auto src_neighbors = at(adj_list,idx);
                    for (nm_size_t j=0; j<(nm_size_t)len(src_neighbors); j++) {
                        auto neighbor = at(src_neighbors,j);
                        if (mapping.count(neighbor)) {
                            auto dst_neighbor = mapping.at(neighbor);
                            neighbors.push_back(dst_neighbor);
                        }
                    }

                    at(result,i) = neighbors;
                }
            }

            return result;
        }
    } // subgraph
}

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SUBGRAPH_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t, typename nodes_t>
    struct resolve_optype<
        void, network::subgraph_t, adjacency_list_t, nodes_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<nodes_t>
                || !is_adjacency_list_v<adjacency_list_t>
            ) {
                using type = error::SUBGRAPH_UNSUPPORTED<adjacency_list_t,nodes_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<nodes_t>
                && is_constant_adjacency_list_v<adjacency_list_t>
            ) {
                constexpr auto adj_list = to_value_v<adjacency_list_t>;
                constexpr auto nodes    = to_value_v<nodes_t>;
                constexpr auto result   = network::subgraph(adj_list,nodes);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    using init_t = type_t<decltype(init)>;
                    constexpr auto neighbors = at(result,I);
                    constexpr auto neighbors_vtype = template_reduce<len(neighbors)>([&](auto init, auto index){
                        constexpr auto J = decltype(index)::value;
                        using init_t = type_t<decltype(init)>;
                        using neighbor_t = ct<at(neighbors,J)>;
                        using type = append_type_t<init_t,neighbor_t>;
                        return as_value_v<type>;
                    }, as_value_v<nmtools_tuple<>>);
                    using neighbors_t = type_t<decltype(neighbors_vtype)>;
                    using type = append_type_t<init_t,neighbors_t>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto NUM_NODES = len_v<nodes_t>;
                [[maybe_unused]]
                constexpr auto MAX_NODES = max_len_v<nodes_t>;
                if constexpr (NUM_NODES > 0) {
                    // TODO: for multi digraph's adj list, num neighbors maybe >>> num_nodes
                    // TODO: in such case, provide tag/hint/extra argument so it can deduced to fully dynamic
                    using inner_t = nmtools_static_vector<nm_index_t,NUM_NODES>;
                    using outer_t = nmtools_array<inner_t,NUM_NODES>;
                    return as_value_v<outer_t>;
                } else if constexpr (MAX_NODES > 0) {
                    // TODO: for multi digraph's adj list, num neighbors maybe >>> num_nodes
                    // TODO: in such case, provide tag/hint/extra argument so it can deduced to fully dynamic
                    using inner_t = nmtools_static_vector<nm_index_t,MAX_NODES>;
                    using outer_t = nmtools_static_vector<inner_t,MAX_NODES>;
                    return as_value_v<outer_t>;
                } else {
                    using inner_t = nmtools_list<nm_index_t>;
                    using outer_t = nmtools_list<inner_t>;
                    return as_value_v<outer_t>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_NETWORK_SUBGRAPH_HPP