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
            auto node    = graph.nodes(to_ct);
            auto from_node = graph.nodes(from_ct);
            auto fused     = node * from_node;
            auto g1 = utility::contracted_edge(graph,nmtools_tuple{from_ct,to_ct},to_ct,fused);
            return linearize(g1);
        } else if constexpr (
            (binary_to > 0)
            // && ((predecessors[binary_lhs].size() > 0) || (predecessors[binary_rhs].size() > 0))
        ) {
            // check if any predecessor of binary_to is also the predecessors of lhs/rhs
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
            // TODO: move to index utility
            constexpr auto vector_index = [](auto vec, auto v){
                auto index = -1;
                for (nm_size_t i=0; i<(nm_size_t)vec.size(); i++) {
                    if ((nm_index_t)vec.at(i) == (nm_index_t)v) {
                        index = i;
                        break;
                    }
                }
                return index;
            };

            auto to_ct = meta::ct_v<src_id_map[binary_to]>;
            auto node = graph.nodes(to_ct);

            // find_binary_fusion can't determine which one is actually lhs or rhs
            constexpr auto operands = meta::to_value_v<decltype(node.operands)>;
            constexpr auto lhs_index = vector_index(operands,src_id_map[binary_lhs]);
            constexpr auto rhs_index = vector_index(operands,src_id_map[binary_rhs]);

            constexpr auto m_lhs = lhs_index <= rhs_index ? binary_lhs : binary_rhs;
            constexpr auto m_rhs = rhs_index >= lhs_index ? binary_rhs : binary_lhs;

            [[maybe_unused]] auto lhs_ct = meta::ct_v<src_id_map[m_lhs]>;
            [[maybe_unused]] auto rhs_ct = meta::ct_v<src_id_map[m_rhs]>;

            // TODO: read lhs / rhs from op

            if constexpr (predecessors[m_lhs].size() > 0 && predecessors[m_rhs].size() > 0) {
                auto lhs_node = graph.nodes(lhs_ct);
                auto rhs_node = graph.nodes(rhs_ct);
                auto fused = fuse_binary(lhs_node,rhs_node,node);

                auto g1 = utility::contracted_edge(graph,nmtools_tuple{lhs_ct,to_ct},to_ct,fused);
                auto g2 = utility::contracted_edge(g1,nmtools_tuple{rhs_ct,to_ct},to_ct,fused);
                return linearize(g2);
            } else if constexpr (predecessors[m_lhs].size() > 0) {
                constexpr auto insert_dup = check_dups(predecessors[binary_to],predecessors[m_lhs]);
                if constexpr (insert_dup) {
                    auto lhs_node = graph.nodes(lhs_ct);
                    constexpr auto LHS_ARITY = meta::len_v<decltype(lhs_node.operands)>;
                    auto fused = node * lhs_node * combinator::bury_n<LHS_ARITY> * combinator::dup;
                    auto g1 = utility::contracted_edge(graph,nmtools_tuple{lhs_ct,to_ct},to_ct,fused);

                    // TODO: select which pred to be removed
                    constexpr auto pred = predecessors[m_lhs][0];
                    auto pred_ct = meta::ct_v<src_id_map[pred]>;
                    auto g2 = g1.remove_edge(pred_ct,to_ct);

                    return linearize(g2);
                } else {
                    auto lhs_node = graph.nodes(lhs_ct);
                    auto fused = node * lhs_node;
                    auto g1 = utility::contracted_edge(graph,nmtools_tuple{lhs_ct,to_ct},to_ct,fused);
                    return linearize(g1);
                }
            } else if constexpr (predecessors[m_rhs].size() > 0) {
                constexpr auto insert_dup = check_dups(predecessors[binary_to],predecessors[m_rhs]);
                if constexpr (insert_dup) {
                    auto rhs_node = graph.nodes(rhs_ct);
                    constexpr auto RHS_ARITY = meta::len_v<decltype(rhs_node.operands)>;
                    // asume output of rhs_node is 1
                    // TODO: handle when rhs_node output is > 1
                    auto fused = node * combinator::swap * rhs_node * combinator::bury_n<RHS_ARITY> * combinator::dup;
                    auto g1 = utility::contracted_edge(graph,nmtools_tuple{rhs_ct,to_ct},to_ct,fused);
                    // TODO: select which pred to be removed
                    constexpr auto pred = predecessors[m_rhs][0];
                    auto pred_ct = meta::ct_v<src_id_map[pred]>;
                    auto g2 = g1.remove_edge(pred_ct,to_ct);
                    return linearize(g2);
                } else {
                    auto rhs_node = graph.nodes(rhs_ct);
                    constexpr auto RHS_ARITY = meta::len_v<decltype(rhs_node.operands)>;
                    auto fused = node * combinator::swap * rhs_node * combinator::bury_n<RHS_ARITY>;
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