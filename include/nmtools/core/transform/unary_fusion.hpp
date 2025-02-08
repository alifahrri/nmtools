#ifndef NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_UNARY_FUSION_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_UNARY_FUSION_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/core/functor.hpp"

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
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_UNARY_FUSION_HPP