#ifndef NMTOOLS_CORE_TRANSFORM_CSE_HPP
#define NMTOOLS_CORE_TRANSFORM_CSE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/invert_map.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/core/node.hpp"
#include "nmtools/core/transform/gvn.hpp"
#include "nmtools/network/base_digraph.hpp"

namespace nmtools::functional
{
    struct cse_t {};

    template <typename adjacency_list_t
        , typename node_ids_t
        , typename node_attributes_t
        , typename edge_attributes_t
        , typename multi_t>
    constexpr auto cse(
        const network::base_digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t,multi_t>& digraph
    ) {
        using result_t = resolve_optype_t<cse_t,adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t,multi_t>;

        using adjacency_list_type = get_adjacency_list_t<result_t>;
        using node_ids_type = get_node_ids_t<result_t>;

        if constexpr (!is_fail_v<result_t>
            && is_digraph_v<result_t>
            && !is_constant_adjacency_list_v<adjacency_list_type>
            && !is_constant_index_array_v<node_ids_type>
        ) {

            auto result = result_t{};

            auto id_values = gvn(digraph);

            // (id) -> hash
            // convert to (hash) -> id

            auto value_ids = index::invert_map(id_values);

            // nodes subgraph
            auto nodes_vtype = [](){
                constexpr auto MAX_LEN = max_len_v<node_ids_t>;
                if constexpr (MAX_LEN > 0) {
                    using type = nmtools_static_vector<nm_size_t,MAX_LEN>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }();
            using nodes_t = type_t<decltype(nodes_vtype)>;

            auto nodes = nodes_t{};
            for (const auto& [hash,id] : value_ids) {
                nodes.push_back(id);
            }

            // TODO: error handling
            result = unwrap(digraph.subgraph(nodes));
            auto src_adj_list = digraph.adjacency_list;
            auto src_node_ids = digraph.node_ids;

            // all edges are re-derived from the source graph below, so clear
            // the adjacency list first: edges between representatives are
            // otherwise deduplicated against the subgraph edges, dropping
            // parallel edges (multi digraph) of merged predecessor nodes
            auto num_result_nodes = len(result.adjacency_list);
            for (nm_size_t i=0; i<(nm_size_t)num_result_nodes; i++) {
                at(result.adjacency_list,i).resize(0);
            }

            auto n = len(nodes);
            for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                auto id = nodes[i];
                auto idx = index::index_of(src_node_ids,id);
                auto preds = unwrap(network::predecessors(src_adj_list,idx));

                auto m = len(preds);
                for (nm_size_t j=0; j<(nm_size_t)m; j++) {
                    auto from_idx = preds[j];
                    auto from_id  = src_node_ids.at(from_idx);

                    auto dst_id = value_ids[id_values[from_id]];
                    result.add_edge(dst_id,id);
                }
            }
            return result;
        } else if constexpr (is_digraph_v<result_t>
            && is_constant_adjacency_list_v<adjacency_list_type>
            && is_constant_index_array_v<node_ids_type>
        ) {
            using edge_attributes_type = get_edge_attributes_t<result_t>;
            auto src_node_ids = digraph.node_ids;

            constexpr auto NUM_NODES = len_v<node_ids_type>;
            auto new_nodes = template_reduce<NUM_NODES>([&](auto init, auto index){
                constexpr auto i = decltype(index)::value;
                using id_t = at_t<node_ids_type,i>;
                auto src_idx = index::index_of(src_node_ids,id_t{});
                return utility::tuple_append(init,at(digraph.node_attributes,src_idx));
            }, nmtools_tuple{});
            return network::multi_digraph(adjacency_list_type{},node_ids_type{},new_nodes,edge_attributes_type{});
        } else {
            // maybe error type
            return result_t{};
        }
    }
} // nmtools::functional

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct CSE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t
        , typename node_ids_t
        , typename node_attributes_t
        , typename edge_attributes_t
        , typename multi_t>
    struct resolve_optype<
        void, functional::cse_t, adjacency_list_t, node_ids_t, node_attributes_t, edge_attributes_t, multi_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>
                || !is_index_array_v<node_ids_t>
            ) {
                // TODO: node attributes should be container of is_buffer_node_v, is_compute_node_v, or is_value_node_v
                using type = error::CSE_UNSUPPORTED<adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t,multi_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_adjacency_list_v<adjacency_list_t>
                && is_constant_index_array_v<node_ids_t>
                && is_tuple_v<node_attributes_t> // assume tuple of compute/buffer node, no value node
                // ignore edge attributes for now
            ) {
                using digraph_t = network::base_digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t,multi_t>;
                constexpr auto digraph = to_value_v<digraph_t>;
                constexpr auto result  = functional::cse(digraph);
                using nmtools::len, nmtools::at;
                constexpr auto ids = result.nodes();
                constexpr auto N   = len(ids);
                auto node_ids_vtype = template_reduce<N>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I  = decltype(index)::value;
                    constexpr auto id = at(ids,I);
                    using type = append_type_t<init_t,ct<id>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
                using node_ids_type = type_t<decltype(node_ids_vtype)>;

                constexpr auto adjacency_list = result.adjacency_list;
                auto adjacency_list_vtype = template_reduce<N>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    using init_t = type_t<decltype(init)>;
                    constexpr auto neighbors = at(adjacency_list,I);
                    constexpr auto NUM_NEIGHBORS = len(neighbors);
                    constexpr auto neighbors_vtype = template_reduce<NUM_NEIGHBORS>([&](auto init, auto index){
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
                using adjacency_list_type = type_t<decltype(adjacency_list_vtype)>;

                using node_attributes_type = get_node_attributes_t<decltype(result)>;
                using edge_attributes_type = get_edge_attributes_t<decltype(result)>;
                using type = network::base_digraph_t<adjacency_list_type,node_ids_type,node_attributes_type,edge_attributes_type,multi_t>;
                return as_value_v<type>;
            } else {
                // TODO: handle constant adjacency list, constant node ids, compute/buffer node
                // resulting type is for subgraph, make resizable with upper bound

                constexpr auto MAX_NODES = max_len_v<node_ids_t>;
                auto node_ids_vtype = [](){
                    if constexpr (MAX_NODES > 0) {
                        using type = nmtools_static_vector<nm_index_t,MAX_NODES>;
                        return as_value_v<type>;
                    } else {
                        // TODO: use small vector
                        using type = nmtools_list<nm_index_t>;
                        return as_value_v<type>;
                    }
                }();
                using node_ids_type = type_t<decltype(node_ids_vtype)>;

                // assume node ids is integer
                auto adjacency_list_vtype = [](){
                    using inner_t = node_ids_type;
                    if constexpr (MAX_NODES > 0) {
                        using type = nmtools_static_vector<inner_t,MAX_NODES>;
                        return as_value_v<type>;
                    } else {
                        // TODO: use small vector
                        using type = nmtools_list<inner_t>;
                        return as_value_v<type>;
                    }
                }();
                using adjacency_list_type = type_t<decltype(adjacency_list_vtype)>;

                // assume node attributes is value node
                auto node_attributes_vtype = [](){
                    using node_t = typename node_attributes_t::value_type;
                    if constexpr (MAX_NODES > 0) {
                        using type = nmtools_static_vector<node_t,MAX_NODES>;
                        return as_value_v<type>;
                    } else {
                        // TODO: use small vector?
                        using type = nmtools_list<node_t>;
                        return as_value_v<type>;
                    }
                }();
                using node_attributes_type = type_t<decltype(node_attributes_vtype)>;

                // use none_t edge for now
                using edge_attributes_type = none_t;

                using type = network::base_digraph_t<adjacency_list_type,node_ids_type,node_attributes_type,edge_attributes_type,multi_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_CORE_TRANSFORM_CSE_HPP