#ifndef NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_BINARY_FUSION_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_BINARY_FUSION_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/core/combinator.hpp"

namespace nmtools::functional
{
    template <typename adjacency_list_t>
    constexpr auto find_binary_fusion(const adjacency_list_t& adjacency_list)
    {
        auto sorted = utility::topological_sort(adjacency_list);
        auto predecessors = utility::predecessors(adjacency_list);

        auto lhs = -1;
        auto rhs = -1;
        auto to  = -1;

        // if lhs == rhs, combinator: dup
        // elif lhs != rhs, combinator: bury1 then dig1
        // elif rhs == -1, combinator: -
        // elif lhs == -1, combinator: bury1 then dig1

        for (nm_size_t i=0; i<(nm_size_t)sorted.size(); i++) {
            auto node = sorted[i];
            if (predecessors[node].size() != 2) {
                continue;
            }
            // unlike find_unary_fusion, here we allow returning input node
            lhs = predecessors[node][0];
            rhs = predecessors[node][1];
            to = node;
            break;
        }

        return nmtools_tuple{lhs,rhs,to};
    } // find_binary_fusion

    template <typename lhs_t, typename rhs_t, typename to_t>
    constexpr auto fuse_binary(const lhs_t& lhs, const rhs_t& rhs, const to_t& to)
    {
        auto fused = to * combinator::dig1 * rhs * combinator::bury1 * lhs;
        return fused;
    }

    template <typename graph_t>
    constexpr auto transform_binary_fusion(const graph_t& graph)
    {
        // TODO: check if graph is fn::compute_graph_t or utility::ct_digraph
        constexpr auto adjacency_result = utility::adjacency_list(decltype(graph.digraph){});
        constexpr auto adjacency_list   = nmtools::get<0>(adjacency_result);
        constexpr auto src_id_map       = nmtools::get<1>(adjacency_result);

        constexpr auto binary_fusion = find_binary_fusion(adjacency_list);
        [[maybe_unused]] constexpr auto lhs = nmtools::get<0>(binary_fusion);
        [[maybe_unused]] constexpr auto rhs = nmtools::get<1>(binary_fusion);
        [[maybe_unused]] constexpr auto to  = nmtools::get<2>(binary_fusion);

        if constexpr (to < 0) {
            return graph;
        } else {
            auto lhs_ct = meta::ct_v<src_id_map[lhs]>;
            auto rhs_ct = meta::ct_v<src_id_map[rhs]>;
            auto to_ct  = meta::ct_v<src_id_map[to]>;
            auto fused  = fuse_binary(graph.nodes(lhs_ct),graph.nodes(rhs_ct),graph.nodes(to_ct));

            auto g1 = utility::contracted_edge(graph,nmtools_tuple{lhs_ct,to_ct},to_ct,fused);
            auto g2 = utility::contracted_edge(g1,nmtools_tuple{rhs_ct,to_ct},to_ct,fused);
            return g2;
        }
    }
}

#endif // NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_BINARY_FUSION_HPP