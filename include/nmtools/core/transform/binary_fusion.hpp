#ifndef NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_BINARY_FUSION_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_BINARY_FUSION_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/core/combinator.hpp"
#include "nmtools/index/contains.hpp"

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
            auto m_lhs = predecessors[node][0];
            auto m_rhs = predecessors[node][1];
            // if both lhs and rhs is inputs skip
            if ((predecessors[m_lhs].size() == 0) && (predecessors[m_rhs].size() == 0)) {
                continue;
            }
            lhs = m_lhs;
            rhs = m_rhs;
            to = node;
            break;
        }

        // NOTE: the order is from topological sort, not the actual operands order for node
        // can't do lexicographical sort for operand order either because no information on node
        return nmtools_tuple{lhs,rhs,to};
    } // find_binary_fusion

    template <typename lhs_t, typename rhs_t, typename to_t>
    constexpr auto fuse_binary(const lhs_t& lhs, const rhs_t& rhs, const to_t& to)
    {
        auto fused = to * combinator::dig1 * rhs * combinator::bury1 * lhs;
        return fused;
    }

    template <typename graph_t, typename n_repeats_t=meta::ct<1>>
    constexpr auto transform_binary_fusion(const graph_t& graph, n_repeats_t = n_repeats_t{})
    {
        // TODO: check if graph is fn::compute_graph_t or utility::ct_digraph
        constexpr auto adjacency_result = utility::adjacency_list(decltype(graph.digraph){});
        constexpr auto adjacency_list   = nmtools::get<0>(adjacency_result);
        constexpr auto src_id_map       = nmtools::get<1>(adjacency_result);
        constexpr auto predecessors     = utility::predecessors(adjacency_list);

        constexpr auto binary_fusion = find_binary_fusion(adjacency_list);
        [[maybe_unused]] constexpr auto lhs = nmtools::get<0>(binary_fusion);
        [[maybe_unused]] constexpr auto rhs = nmtools::get<1>(binary_fusion);
        [[maybe_unused]] constexpr auto to  = nmtools::get<2>(binary_fusion);

        if constexpr (to < 0) {
            return graph;
        } else {
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
            // find the index of predecessor of binary_to that is also predecessors of lhs/rhs
            // useful to remove edge
            // currently assume only single edge that is relevant
            // TODO: generalize to more edges
            constexpr auto index_dups = [&](auto preds, auto r_preds){
                auto index_dup = [](auto preds, auto r_pred){
                    // check if should insert dup
                    auto index = -1;
                    for (nm_size_t i=0; i<(nm_size_t)preds.size(); i++) {
                        if (preds[i] == r_pred) {
                            index = i;
                            break;
                        };
                    }
                    return index;
                };
                auto index = -1;
                for (nm_size_t i=0; i<(nm_size_t)r_preds.size(); i++){
                    if (auto idx = index_dup(preds,r_preds.at(i)); idx > -1) {
                        index = idx;
                        break;
                    }
                }
                // return index of predecessors of lhs/rhs (not binary_to ones)
                return index;
            };
            auto to_ct  = meta::ct_v<src_id_map[to]>;
            auto node = graph.nodes(to_ct);

            // find_binary_fusion can't determine which one is actually lhs or rhs
            constexpr auto operands = meta::to_value_v<decltype(node.operands)>;
            constexpr auto lhs_index = [&](){
                if constexpr (meta::is_fail_v<decltype(operands)>) {
                    return 0;
                } else {
                    return vector_index(operands,src_id_map[lhs]);
                }
            }();
            constexpr auto rhs_index = [&](){
                if constexpr (meta::is_fail_v<decltype(operands)>) {
                    return 1;
                } else {
                    return vector_index(operands,src_id_map[rhs]);
                }
            }();

            constexpr auto m_lhs = lhs_index <= rhs_index ? lhs : rhs;
            constexpr auto m_rhs = rhs_index >= lhs_index ? rhs : lhs;

            [[maybe_unused]] auto lhs_ct = meta::ct_v<src_id_map[m_lhs]>;
            [[maybe_unused]] auto rhs_ct = meta::ct_v<src_id_map[m_rhs]>;

            if constexpr (predecessors[m_lhs].size() > 0 && predecessors[m_rhs].size()) {
                auto lhs_node = graph.nodes(lhs_ct);
                auto rhs_node = graph.nodes(rhs_ct);

                [[maybe_unused]]
                constexpr auto order = utility::topological_sort(adjacency_list);

                constexpr auto m_lhs_idx = vector_index(order,m_lhs);
                constexpr auto m_rhs_idx = vector_index(order,m_rhs);

                auto fuse_operands = [](auto fst, auto snd){
                    constexpr auto FST = meta::to_value_v<decltype(fst)>;
                    constexpr auto N = meta::len_v<decltype(snd)>;
                    return meta::template_reduce<N>([&](auto init, auto I){
                        auto operand = at(snd,I);
                        if constexpr (index::contains(FST,decltype(operand)::value)) {
                            return init;
                        } else {
                            return utility::tuple_append(init,operand);
                        }
                    },fst);
                };

                // assume lhs & rhs is unary
                // TODO: handle lhs & rhs with arbitrary arity
                auto fused = [&](){
                    if constexpr (m_lhs_idx < m_rhs_idx) {
                        auto fused = [&](){
                            constexpr auto index_dup = index_dups(predecessors[to],predecessors[m_rhs]);
                            if constexpr (index_dup >= 0) {
                                constexpr auto rhs_arity = meta::len_v<decltype(rhs_node.operands)>;
                                constexpr auto RHS_ARITY = rhs_arity > 0 ? rhs_arity : 1;
                                return node * combinator::dig_n<RHS_ARITY> * rhs_node * combinator::bury_n<RHS_ARITY> * combinator::dup * lhs_node;
                            } else {
                                return node * combinator::dig1 * rhs_node * combinator::bury1 * lhs_node;
                            }
                        }();
                        if constexpr (meta::is_same_v<meta::remove_cvref_t<decltype(fused.operands)>,meta::empty_operands_t>) {
                            return fused;
                        } else {
                            auto op1 = fuse_operands(lhs_node.operands,rhs_node.operands);
                            auto op2 = utility::tuple_filter(op1,[&](auto value){
                                constexpr auto VALUE = decltype(value)::value;
                                constexpr auto pred = (VALUE != src_id_map[m_lhs]) && (VALUE != src_id_map[m_rhs]);
                                return meta::ct_v<pred>;
                            });
                            auto new_operands = op2;
                            return fused.set_operands(new_operands);
                        }
                    } else {
                        auto fused = [&](){
                            constexpr auto index_dup = index_dups(predecessors[to],predecessors[m_lhs]);
                            if constexpr (index_dup >= 0) {
                                constexpr auto lhs_arity = meta::len_v<decltype(lhs_node.operands)>;
                                constexpr auto LHS_ARITY = lhs_arity > 0 ? lhs_arity : 1;
                                return node * combinator::dig_n<LHS_ARITY> * lhs_node * combinator::bury_n<LHS_ARITY> * combinator::dup * rhs_node;
                            } else {
                                return node * lhs_node * combinator::bury1 * rhs_node;
                            }
                        }();
                        if constexpr (meta::is_same_v<meta::remove_cvref_t<decltype(fused.operands)>,meta::empty_operands_t>) {
                            return fused;
                        } else {
                            auto op1 = fuse_operands(rhs_node.operands,lhs_node.operands);
                            auto op2 = utility::tuple_filter(op1,[&](auto value){
                                constexpr auto VALUE = decltype(value)::value;
                                constexpr auto pred = (VALUE != src_id_map[m_lhs]) && (VALUE != src_id_map[m_rhs]);
                                return meta::ct_v<pred>;
                            });
                            auto new_operands = op2;
                            return fused.set_operands(new_operands);
                        }
                    }
                }();

                auto g1 = utility::contracted_edge(graph,nmtools_tuple{lhs_ct,to_ct},to_ct,fused);
                auto g2 = utility::contracted_edge(g1,nmtools_tuple{rhs_ct,to_ct},to_ct,fused);

                constexpr auto n_repeats = n_repeats_t::value;
                if constexpr ((0 < (nm_index_t)n_repeats-1) || ((nm_index_t)n_repeats < 0)) {
                    return transform_binary_fusion(g2,meta::ct_v<n_repeats-1>);
                } else {
                    return g2;
                }
            } else if constexpr (predecessors[m_lhs].size() > 0) {
                constexpr auto index_dup = index_dups(predecessors[to],predecessors[m_lhs]);
                if constexpr (index_dup >= 0) {
                    constexpr auto pred = predecessors[m_lhs][index_dup];
                    auto pred_ct  = meta::ct_v<src_id_map[pred]>;
                    auto lhs_node = graph.nodes(lhs_ct);
                    // TODO: check if node has operands
                    constexpr auto LHS_ARITY = meta::len_v<decltype(lhs_node.operands)>;
                    auto fused = node.remove_operand(pred_ct) * lhs_node * combinator::bury_n<LHS_ARITY> * combinator::dup;
                    auto g1 = utility::contracted_edge(graph,nmtools_tuple{lhs_ct,to_ct},to_ct,fused);
                    auto g2 = g1.remove_edge(pred_ct,to_ct);

                    constexpr auto n_repeats = n_repeats_t::value;
                    if constexpr ((0 < (nm_index_t)n_repeats-1) || ((nm_index_t)n_repeats < 0)) {
                        return transform_binary_fusion(g2,meta::ct_v<n_repeats-1>);
                    } else {
                        return g2;
                    }
                } else {
                    auto lhs_node = graph.nodes(lhs_ct);
                    auto fused = node.remove_operand(lhs_ct) * lhs_node;
                    auto g1 = utility::contracted_edge(graph,nmtools_tuple{lhs_ct,to_ct},to_ct,fused);
                    
                    constexpr auto n_repeats = n_repeats_t::value;
                    if constexpr ((0 < (nm_index_t)n_repeats-1) || ((nm_index_t)n_repeats < 0)) {
                        return transform_binary_fusion(g1,meta::ct_v<n_repeats-1>);
                    } else {
                        return g1;
                    }
                }
            } else if constexpr (predecessors[m_rhs].size() > 0) {
                constexpr auto index_dup = index_dups(predecessors[to],predecessors[m_rhs]);
                if constexpr (index_dup >= 0) {
                    constexpr auto pred = predecessors[m_rhs][index_dup];
                    auto pred_ct  = meta::ct_v<src_id_map[pred]>;
                    auto rhs_node = graph.nodes(rhs_ct);

                    // TODO: check if node has operands
                    constexpr auto RHS_ARITY = meta::len_v<decltype(rhs_node.operands)>;
                    auto fused = (node * combinator::swap * rhs_node * combinator::bury_n<RHS_ARITY> * combinator::dup).set_operands(rhs_node.operands);
                    auto g1 = utility::contracted_edge(graph,nmtools_tuple{rhs_ct,to_ct},to_ct,fused);
                    auto g2 = g1.remove_edge(pred_ct,to_ct);

                    constexpr auto n_repeats = n_repeats_t::value;
                    if constexpr ((0 < (nm_index_t)n_repeats-1) || ((nm_index_t)n_repeats < 0)) {
                        return transform_binary_fusion(g2,meta::ct_v<n_repeats-1>);
                    } else {
                        return g2;
                    }
                } else {
                    auto rhs_node = graph.nodes(rhs_ct);
                    // TODO: check if node has operands
                    constexpr auto RHS_ARITY = meta::len_v<decltype(rhs_node.operands)>;
                    auto fused = node * combinator::swap * rhs_node * combinator::bury_n<RHS_ARITY>;
                    auto g1 = utility::contracted_edge(graph,nmtools_tuple{rhs_ct,to_ct},to_ct,fused);

                    constexpr auto n_repeats = n_repeats_t::value;
                    if constexpr ((0 < (nm_index_t)n_repeats-1) || ((nm_index_t)n_repeats < 0)) {
                        return transform_binary_fusion(g1,meta::ct_v<n_repeats-1>);
                    } else {
                        return g1;
                    }
                }
            } else {
                return graph;
            }
            #if 0
            auto fused  = fuse_binary(graph.nodes(lhs_ct),graph.nodes(rhs_ct),graph.nodes(to_ct));

            auto g1 = utility::contracted_edge(graph,nmtools_tuple{lhs_ct,to_ct},to_ct,fused);
            auto g2 = utility::contracted_edge(g1,nmtools_tuple{rhs_ct,to_ct},to_ct,fused);
            return g2;
            #endif
        }
    }
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_BINARY_FUSION_HPP