#ifndef NMTOOLS_RUNTIME_COMPUTATIONAL_GRAPH_HPP
#define NMTOOLS_RUNTIME_COMPUTATIONAL_GRAPH_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/runtime/def.hpp"
#include "nmtools/runtime/node.hpp"
#include "nmtools/core/computational_graph.hpp"
#include "nmtools/network/digraph.hpp"

namespace nmtools::runtime
{
    // TODO: add is_digraph metafunction, then handle variant for this
    template <typename adjacency_list_t, typename node_ids_t, typename node_attributes_t, typename edge_attributes_t>
    auto to_value(const network::digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t>& digraph)
    {
        // TODO: support edge attributes
        static_assert( is_none_v<edge_attributes_t> );

        auto dst_adjacency_list = AdjacencyList();
        auto dst_node_ids       = NodeIDs();
        auto dst_attributes     = NodeAttributes();

        constexpr auto adjacency_list = to_value_v<adjacency_list_t>;
        for (nm_size_t i=0; i<adjacency_list.size(); i++) {
            auto neighbors = nmtools_list<nm_index_t>();
            for (nm_size_t j=0; j<adjacency_list[i].size(); j++) {
                neighbors.push_back(adjacency_list[i][j]);
            }
            dst_adjacency_list.push_back(neighbors);
        }

        constexpr auto N = len_v<node_attributes_t>;
        template_for<N>([&](auto i){
            auto node = to_value(at(digraph.node_attributes,i));
            auto node_id = at(digraph.node_ids,i);
            dst_attributes.push_back(node);
            dst_node_ids.push_back(node_id);
        });

        return network::digraph(dst_adjacency_list,dst_node_ids,dst_attributes);
    } // to_value
}

namespace nmtools
{
    auto output_id(const runtime::Graph& graph);
    auto shape(const runtime::Graph& graph);
    auto type(const runtime::Graph& graph);
}

// TODO: guard the runtime implementation using macro
namespace nmtools
{
    inline
    auto output_id(const runtime::Graph& graph)
    {
        auto out_degrees = graph.out_degree();

        for (nm_size_t i=0; i<out_degrees.size(); i++) {
            const auto& [node, degree] = out_degrees[i];
            if (degree == 0) {
                return graph.node_ids.at(i);
            }
        }

        nmtools_panic( false
            , "no output node found in graph"
        );
        return (nm_index_t)0;
    }

    inline
    auto shape(const runtime::Graph& graph)
    {
        using IndexType = nmtools_list<nm_index_t>;
        auto out_degrees = graph.out_degree();

        auto num_outputs = 0ul;
        auto out_shape   = IndexType{};
        for (nm_size_t i=0; i<out_degrees.size(); i++) {
            const auto& [node, degree] = out_degrees[i];
            if (degree == 0) {
                out_shape = node.shape();
                num_outputs++;
            }
        }

        nmtools_panic( num_outputs == 1
            , "multiple output detected for this graph" );

        return out_shape;
    }

    inline
    auto type(const runtime::Graph& graph)
    {
        auto out_degrees = graph.out_degree();
        auto num_outputs = 0ul;

        runtime::DType type;
        for (nm_size_t i=0; i<out_degrees.size(); i++) {
            const auto& [node, degree] = out_degrees[i];
            if (degree == 0) {
                type = node.dtype();
                num_outputs++;
            }
        }

        nmtools_panic( num_outputs == 1
            , "multiple output detected for this graph" );

        return type;
    }
}

#endif // NMTOOLS_RUNTIME_COMPUTATIONAL_GRAPH_HPP