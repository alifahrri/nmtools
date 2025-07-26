#ifndef NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_UNARY_FUSION_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_UNARY_FUSION_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/network/cast.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/network/filter_node_arity.hpp"
#include "nmtools/network/predecessors.hpp"
#include "nmtools/core/node.hpp"

namespace nmtools::functional
{
    // find a node that has single output and single input, in which the input only used by that node
    template <typename adjacency_list_t>
    constexpr auto find_unary_fusion(const adjacency_list_t& adjacency_list)
    {
        auto sorted = utility::topological_sort(adjacency_list);
        auto predecessors = utility::predecessors(adjacency_list);

        auto from = -1;
        auto to = -1;
        for (nm_size_t i=0; i<(nm_size_t)sorted.size(); i++) {
            auto node = sorted[i];
            // "unary" means only single predecessor
            if (predecessors[node].size() != 1) {
                continue;
            }
            // make sure the predecessor in question is not an input node
            auto predecessor = predecessors[node][0];
            if ((predecessors[predecessor].size() == 0) || (adjacency_list[predecessor].size() > 1)) {
                continue;
            }
            from = predecessor;
            to = node;
            break;
        }
        return nmtools_tuple{from,to};
    } // find_unary_fusion

    template <typename graph_t, typename n_repeats_t=meta::ct<1>>
    constexpr auto transform_unary_fusion(const graph_t& graph, n_repeats_t = n_repeats_t{})
    {
        // TODO: check if graph is fn::compute_graph_t or utility::ct_digraph
        constexpr auto adjacency_result = utility::adjacency_list(decltype(graph.digraph){});
        constexpr auto adjacency_list   = nmtools::get<0>(adjacency_result);
        constexpr auto src_id_map       = nmtools::get<1>(adjacency_result);

        constexpr auto unary_fusion = find_unary_fusion(adjacency_list);
        constexpr auto from = nmtools::get<0>(unary_fusion);
        constexpr auto to   = nmtools::get<1>(unary_fusion);

        if constexpr ((from < 0) || (to < 0)) {
            return graph;
        } else {
            auto from_ct = meta::ct_v<src_id_map[from]>;
            auto to_ct   = meta::ct_v<src_id_map[to]>;
            auto fused   = graph.nodes(to_ct) * graph.nodes(from_ct);

            auto contracted = utility::contracted_edge(graph,nmtools_tuple{from_ct,to_ct},to_ct,fused);
            constexpr auto n_repeats = n_repeats_t::value;
            if constexpr ((0 < (nm_index_t)n_repeats-1) || ((nm_index_t)n_repeats < 0)) {
                return transform_unary_fusion(contracted,meta::ct_v<n_repeats-1>);
            } else {
                return contracted;
            }
        }
    }

    template <typename adjacency_list_t
        , typename node_ids_t
        , typename node_attributes_t
        , typename edge_attributes_t
        , typename n_repeats_t=meta::ct<1>>
    constexpr auto transform_unary_fusion(
        const network::digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t>& digraph
        , [[maybe_unused]] n_repeats_t n_repeats = n_repeats_t{})
    {
        // assume node_attributes is functional::Node
        // TODO: assert node_attributes is functional::Node & edge is None
        auto m_unary_nodes = network::filter_node_arity(digraph,1);
        auto unary_nodes = unwrap(m_unary_nodes);

        constexpr auto M_MAX_NUM_NODES = meta::max_len_v<adjacency_list_t>;
        constexpr auto MAX_NUM_NODES = (M_MAX_NUM_NODES >= 0 ? M_MAX_NUM_NODES : 0);

        using adjacency_list_type = meta::conditional_t<(MAX_NUM_NODES > 0)
            , nmtools_static_vector<nmtools_static_vector<nm_index_t,MAX_NUM_NODES>,MAX_NUM_NODES>
            , nmtools_list<nmtools_list<nm_index_t>>>;

        using node_ids_type = meta::conditional_t<(MAX_NUM_NODES > 0)
            , nmtools_static_vector<nm_index_t,MAX_NUM_NODES>
            , nmtools_list<nm_index_t>>;
        using attribute_type = meta::get_value_type_t<node_attributes_t>;
        using node_attributes_type = meta::conditional_t<(MAX_NUM_NODES > 0)
            , nmtools_static_vector<attribute_type,MAX_NUM_NODES>
            , nmtools_list<attribute_type>>;

        auto adj_list = network::cast<adjacency_list_type>(digraph.adjacency_list);
        auto node_ids = network::cast_node_ids<node_ids_type>(digraph.node_ids);
        auto node_attributes = network::cast_node_attributes<node_attributes_type>(digraph.node_attributes);
        auto src_digraph = network::digraph(adj_list,node_ids,node_attributes);

        if (!unary_nodes.size()) {
            return src_digraph;
        } else {
            // skip if node is buffer
            // buffer can't be fused with compute/composition/combinator
            auto to = nm_index_t{-1};
            auto from = nm_index_t{-1};
            auto valid = false;
            for (nm_size_t i=0; i<(nm_size_t)unary_nodes.size(); i++) {
                auto id = at(unary_nodes,i);
                if (digraph.nodes(id).is_buffer()) {
                    continue;
                } else {
                    // TODO: propagate error
                    to = id;
                    auto preds = network::predecessors(digraph,to);
                    from = at(unwrap(preds),meta::ct_v<0>);
                    if (digraph.nodes(from).is_buffer()) {
                        continue;
                    }
                    auto outgoing = digraph.out_edges(from);
                    if (len(unwrap(outgoing)) != 1) {
                        continue;
                    }
                    valid = true;
                    break;
                }
            }
            if (!valid) {
                return src_digraph;
            }

            // following functor, the functor evaluation is from the right to the left
            auto fused = digraph.nodes(to) * digraph.nodes(from);
            auto m_contracted = network::contracted_edge(digraph,nmtools_array{from,to},fused);

            // TODO: propagate error
            auto contracted = unwrap(m_contracted);

            auto adj_list = network::cast<adjacency_list_type>(contracted.adjacency_list);
            auto node_ids = network::cast_node_ids<node_ids_type>(contracted.node_ids);
            auto node_attributes = network::cast_node_attributes<node_attributes_type>(contracted.node_attributes);

            auto result = network::digraph(adj_list,node_ids,node_attributes);
            auto repeat = (nm_index_t)n_repeats-1;
            if (repeat != 0) {
                return transform_unary_fusion(result,repeat);
            } else {
                return result;
            }
        }
    } // transform_unary_fusion
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_UNARY_FUSION_HPP