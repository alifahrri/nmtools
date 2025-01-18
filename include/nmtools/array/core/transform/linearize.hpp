#ifndef NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_LINEARIZE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_LINEARIZE_HPP

#include "nmtools/array/core/transform/unary_fusion.hpp"
#include "nmtools/array/core/transform/binary_fusion.hpp"

namespace nmtools::functional
{
    template <typename graph_t>
    constexpr auto linearize(const graph_t& graph)
    {
        constexpr auto adjacency_result = utility::adjacency_list(decltype(graph.digraph){});
        constexpr auto adjacency_list   = nmtools::get<0>(adjacency_result);
        constexpr auto src_id_map       = nmtools::get<1>(adjacency_result);

        constexpr auto unary_fusion  = find_unary_fusion(adjacency_list);
        constexpr auto binary_fusion = find_binary_fusion(adjacency_list);

        constexpr auto unary_to  = nmtools::get<1>(unary_fusion);
        constexpr auto binary_to = nmtools::get<2>(binary_fusion);

        if constexpr ((unary_to < 0) || (binary_to < 0)) {
            return graph;
        } else if constexpr (unary_to >= 0) {
            constexpr auto from = nmtools::get<0>(unary_fusion);
            auto from_ct = meta::ct_v<src_id_map[from]>;
            auto to_ct   = meta::ct_v<src_id_map[unary_to]>;
            auto fused   = graph.nodes(to_ct) * graph.nodes(from_ct);
            auto g1 = utility::contracted_edge(graph,nmtools_tuple{from_ct,to_ct},to_ct,fused);
            return linearize(g1);
        } else {
            // binary_to >= 0
            constexpr auto lhs = nmtools::get<0>(binary_fusion);
            constexpr auto rhs = nmtools::get<1>(binary_fusion);

            auto lhs_ct = meta::ct_v<src_id_map[lhs]>;
            auto rhs_ct = meta::ct_v<src_id_map[rhs]>;
            auto to_ct  = meta::ct_v<src_id_map[binary_to]>;
            auto fused  = fuse_binary(graph.nodes(lhs_ct),graph.nodes(rhs_ct),graph.nodes(to_ct));

            auto g1 = utility::contracted_edge(graph,nmtools_tuple{lhs_ct,to_ct},to_ct,fused);
            auto g2 = utility::contracted_edge(g1,nmtools_tuple{rhs_ct,to_ct},to_ct,fused);
            return linearize(g2);
        }
    }
}

#endif // NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_LINEARIZE_HPP