#ifndef NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_LINEARIZE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_LINEARIZE_HPP

#include "nmtools/core/transform/unary_fusion.hpp"
#include "nmtools/core/transform/binary_fusion.hpp"

namespace nmtools::functional
{
    template <typename graph_t>
    constexpr auto linearize(const graph_t& graph)
    {
        constexpr auto adjacency_result = utility::adjacency_list(decltype(graph.digraph){});
        constexpr auto adjacency_list   = nmtools::get<0>(adjacency_result);
        constexpr auto src_id_map       = nmtools::get<1>(adjacency_result);
        constexpr auto predecessors     = utility::predecessors(adjacency_list);

        constexpr auto unary_fusion  = find_unary_fusion(adjacency_list);
        constexpr auto binary_fusion = find_binary_fusion(adjacency_list);

        constexpr auto unary_to  = nmtools::get<1>(unary_fusion);
        constexpr auto binary_to = nmtools::get<2>(binary_fusion);

        constexpr auto binary_lhs = nmtools::get<0>(binary_fusion);
        constexpr auto binary_rhs = nmtools::get<1>(binary_fusion);

        if constexpr (unary_to >= 0) {
            constexpr auto from = nmtools::get<0>(unary_fusion);
            auto from_ct = meta::ct_v<src_id_map[from]>;
            auto to_ct   = meta::ct_v<src_id_map[unary_to]>;
            auto fused   = graph.nodes(to_ct) * graph.nodes(from_ct);
            auto g1 = utility::contracted_edge(graph,nmtools_tuple{from_ct,to_ct},to_ct,fused);
            return linearize(g1);
        } else if constexpr (
            (binary_to > 0)
            // && ((predecessors[binary_lhs].size() > 0) || (predecessors[binary_rhs].size() > 0))
        ) {
            [[maybe_unused]]
            constexpr auto check_dups = [&](auto preds, auto r_preds){
                auto check_dup = [](auto preds, auto r_pred){
                    // check if should insert dup
                    auto insert = false;
                    for (nm_size_t i=0; i<(nm_size_t)preds.size(); i++) {
                        insert = insert || (preds[i] == r_pred);
                    }
                    return insert;
                };
                auto insert = false;
                for (nm_size_t i=0; i<(nm_size_t)r_preds.size(); i++){
                    insert = insert || check_dup(preds,r_preds.at(i));
                }
                return insert;
            };

            if constexpr (predecessors[binary_lhs].size() > 0 && predecessors[binary_rhs].size() > 0) {
                auto lhs_ct = meta::ct_v<src_id_map[binary_lhs]>;
                auto rhs_ct = meta::ct_v<src_id_map[binary_rhs]>;
                auto to_ct  = meta::ct_v<src_id_map[binary_to]>;
                auto fused  = fuse_binary(graph.nodes(lhs_ct),graph.nodes(rhs_ct),graph.nodes(to_ct));

                auto g1 = utility::contracted_edge(graph,nmtools_tuple{lhs_ct,to_ct},to_ct,fused);
                auto g2 = utility::contracted_edge(g1,nmtools_tuple{rhs_ct,to_ct},to_ct,fused);
                return linearize(g2);
            } else if constexpr (predecessors[binary_lhs].size() > 0) {
                auto lhs_ct = meta::ct_v<src_id_map[binary_lhs]>;
                auto to_ct  = meta::ct_v<src_id_map[binary_to]>;

                // assume lhs is unary
                constexpr auto insert_dup = check_dups(predecessors[binary_to],predecessors[binary_lhs]);
                if constexpr (insert_dup) {
                    // TODO: select which pred to be removed
                    constexpr auto pred = predecessors[binary_lhs][0];
                    auto pred_ct = meta::ct_v<src_id_map[pred]>;
                    auto lhs_node = graph.nodes(lhs_ct);
                    constexpr auto LHS_ARITY = meta::len_v<decltype(lhs_node.operands)>;
                    auto fused = graph.nodes(to_ct) * lhs_node * combinator::bury_n<LHS_ARITY> * combinator::dup;
                    auto g1 = utility::contracted_edge(graph,nmtools_tuple{lhs_ct,to_ct},to_ct,fused);
                    auto g2 = g1.remove_edge(pred_ct,to_ct);
                    return linearize(g2);
                } else {
                    auto fused = graph.nodes(to_ct) * graph.nodes(lhs_ct);
                    auto g1 = utility::contracted_edge(graph,nmtools_tuple{lhs_ct,to_ct},to_ct,fused);
                    return linearize(g1);
                }
            } else if constexpr (predecessors[binary_rhs].size() > 0) {
                auto rhs_ct = meta::ct_v<src_id_map[binary_rhs]>;
                auto to_ct  = meta::ct_v<src_id_map[binary_to]>;

                // assume rhs is unary
                constexpr auto insert_dup = check_dups(predecessors[binary_to],predecessors[binary_rhs]);
                if constexpr (insert_dup) {
                    // TODO: select which pred to be removed
                    constexpr auto pred = predecessors[binary_rhs][0];
                    auto pred_ct = meta::ct_v<src_id_map[pred]>;
                    auto rhs_node = graph.nodes(rhs_ct);
                    constexpr auto RHS_ARITY = meta::len_v<decltype(rhs_node.operands)>;
                    auto fused = graph.nodes(to_ct) * combinator::dig_n<RHS_ARITY> * rhs_node * combinator::bury_n<RHS_ARITY> * combinator::dup;
                    auto g1 = utility::contracted_edge(graph,nmtools_tuple{rhs_ct,to_ct},to_ct,fused);
                    auto g2 = g1.remove_edge(pred_ct,to_ct);
                    return linearize(g2);
                } else {
                    auto rhs_node = graph.nodes(rhs_ct);
                    auto node = graph.nodes(to_ct);
                    constexpr auto RHS_ARITY = meta::len_v<decltype(rhs_node.operands)>;
                    auto fused = node * combinator::dig_n<RHS_ARITY> * rhs_node * combinator::bury_n<RHS_ARITY>;
                    auto g1 = utility::contracted_edge(graph,nmtools_tuple{rhs_ct,to_ct},to_ct,fused);
                    return linearize(g1);
                }
            } else {
                return graph;
            }
        } else {
            return graph;
        }
    }

    // template <typename nodes_t, typename edges_t, typename node_data_t>
    // constexpr auto get_function(const compute_graph_t<nodes_t,edges_t,node_data_t>& graph)
    template <typename compute_graph_t, meta::enable_if_t<!meta::is_view_v<decltype(unwrap(meta::declval<compute_graph_t>()))>,int> = 0>
    constexpr auto get_function(const compute_graph_t& graph)
    {
        auto nodes = graph.nodes();

        constexpr auto N = meta::len_v<decltype(nodes)>;
        auto function_nodes = meta::template_reduce<N>([&](auto init, auto I){
            auto index = at(nodes,I);
            auto f = graph.nodes(index);
            using fun_t = decltype(f);
            if constexpr (meta::is_num_v<fun_t> || meta::is_pointer_v<fun_t>) {
                return init;
            } else {
                return utility::tuple_append(init,index);
            }
        },nmtools_tuple{});

        static_assert( meta::len_v<decltype(function_nodes)> == 1 );

        return graph.nodes(at(function_nodes,meta::ct_v<0>));
    }

    // template <typename nodes_t, typename edges_t, typename node_data_t>
    // constexpr auto get_operands(const compute_graph_t<nodes_t,edges_t,node_data_t>& graph)
    template <typename compute_graph_t, meta::enable_if_t<!meta::is_view_v<meta::remove_cvref_pointer_t<decltype(unwrap(meta::declval<compute_graph_t>()))>>,int> = 0>
    constexpr auto get_operands(const compute_graph_t& graph)
    {
        auto nodes = graph.nodes();

        constexpr auto N = meta::len_v<decltype(nodes)>;
        auto input_nodes = meta::template_reduce<N>([&](auto init, auto I){
            auto index = at(nodes,I);
            auto inp = graph.nodes(index);
            using inp_t = decltype(inp);
            if constexpr (meta::is_num_v<inp_t> || meta::is_pointer_v<inp_t>) {
                return utility::tuple_append(init,index);
            } else {
                return init;
            }
        },nmtools_tuple{});

        return meta::template_reduce<meta::len_v<decltype(input_nodes)>>([&](auto init, auto I){
            auto index = at(input_nodes,I);
            return utility::tuple_append(init,graph.nodes(index));
        },nmtools_tuple{});
    }
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_LINEARIZE_HPP