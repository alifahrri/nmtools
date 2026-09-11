#ifndef NMTOOLS_CORE_TRANSFORM_CSE_HPP
#define NMTOOLS_CORE_TRANSFORM_CSE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/core/node.hpp"
#include "nmtools/core/transform/gvn.hpp"

namespace nmtools::functional
{
    struct cse_t {};

    template <typename adjacency_list_t
        , typename node_ids_t
        , typename node_attributes_t
        , typename edge_attributes_t>
    constexpr auto cse(
        const network::digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t>& digraph
    ) {
        auto id_values = gvn(digraph);

        // (id) -> hash
        // convert to (hash) -> id

        // assuming node_ids_t is not none_t
        auto value_ids_vtype = [](){
            constexpr auto MAX_LEN = max_len_v<node_ids_t>;
            if constexpr (MAX_LEN > 0) {
                using type = utl::static_map<nm_size_t,nm_size_t,MAX_LEN>;
                return as_value_v<type>;
            } else {
                using type = nmtools_default_map<nm_size_t,nm_size_t>;
                return as_value_v<type>;
            }
        }();
        using value_ids_t = type_t<decltype(value_ids_vtype)>;

        auto value_ids = value_ids_t{};
        for (const auto& [key,value] : id_values) {
            value_ids[value] = key;
        }

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
        auto subgraph = unwrap(digraph.subgraph(nodes));
        auto src_adj_list = digraph.adjacency_list;
        auto src_node_ids = digraph.node_ids;

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
                if (!subgraph.has_edge(dst_id,id)) {
                    subgraph.add_edge(dst_id,id);
                }
            }
        }

        return subgraph;
    }
}

#endif // NMTOOLS_CORE_TRANSFORM_CSE_HPP