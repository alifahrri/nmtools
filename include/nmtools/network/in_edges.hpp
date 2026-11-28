#ifndef NMTOOLS_NETWORK_IN_EDGES_HPP
#define NMTOOLS_NETWORK_IN_EDGES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/index_of.hpp"
#include "nmtools/network/map_ids.hpp"

namespace nmtools::tag
{
    struct in_edges_t {};
}

namespace nmtools::network
{
    // NOTE: not accepting node_ids because returning a transformed in edges will results in inconsistent indexing of src & dst
    template <typename adjacency_list_t, typename nbunch_t=none_t, typename multi_t=meta::false_type, typename node_ids_t=none_t>
    constexpr auto in_edges(const adjacency_list_t& adj_list, const nbunch_t& nbunch=nbunch_t{}, multi_t=multi_t{}, const node_ids_t& node_ids=node_ids_t{})
    {
        constexpr auto multi = multi_t{};
        if constexpr (meta::is_maybe_v<adjacency_list_t>
            || meta::is_maybe_v<nbunch_t>
            || meta::is_maybe_v<node_ids_t>
        ) {
            using result_t = decltype(in_edges(unwrap(adj_list),unwrap(nbunch),multi,unwrap(node_ids)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adj_list) && has_value(nbunch)
                ? return_t{in_edges(unwrap(adj_list),unwrap(nbunch),multi,unwrap(node_ids))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::in_edges_t,adjacency_list_t,nbunch_t,multi_t,node_ids_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_adjacency_list_v<result_t>
            ) {
                // demote constant structures so they can be indexed at runtime
                decltype(auto) m_adj_list = [&]() -> decltype(auto) {
                    if constexpr (is_constant_adjacency_list_v<adjacency_list_t>) {
                        return to_value_v<adjacency_list_t>;
                    } else {
                        return (adj_list);
                    }
                }();
                decltype(auto) m_node_ids = [&]() -> decltype(auto) {
                    if constexpr (is_none_v<node_ids_t>) {
                        return (node_ids);
                    } else if constexpr (is_constant_index_array_v<node_ids_t>) {
                        return to_value_v<node_ids_t>;
                    } else {
                        return (node_ids);
                    }
                }();

                [[maybe_unused]]
                auto num_nodes = len(m_adj_list);

                // upper bound: each adjacency entry contributes at most one edge
                auto num_edges = 0;
                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    num_edges += len(at(m_adj_list,i));
                }

                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(num_edges);
                }

                auto res_i = 0;

                // emit all (src,dst) pairs with dst == dst_idx,
                // src in ascending order, key in ascending order
                auto emit_in_edges_of = [&](auto dst_idx){
                    for (nm_size_t src_idx=0; src_idx<(nm_size_t)num_nodes; src_idx++) {
                        const auto& neighbors = at(m_adj_list,src_idx);
                        auto num_neighbors = len(neighbors);

                        // number of parallel edges src->dst
                        auto num_keys = 0;
                        for (nm_size_t j=0; j<(nm_size_t)num_neighbors; j++) {
                            if ((nm_size_t)at(neighbors,j) == (nm_size_t)dst_idx) {
                                num_keys += 1;
                            }
                        }

                        auto from = [&](){
                            if constexpr (is_none_v<node_ids_t>) {
                                return src_idx;
                            } else {
                                return unwrap(map_ids(src_idx,m_node_ids));
                            }
                        }();
                        auto to = [&](){
                            if constexpr (is_none_v<node_ids_t>) {
                                return dst_idx;
                            } else {
                                return unwrap(map_ids(dst_idx,m_node_ids));
                            }
                        }();

                        if constexpr (!multi) {
                            // plain digraph: parallel entries are the same edge
                            if (num_keys > 0) {
                                result[res_i++] = {(nm_size_t)from,(nm_size_t)to};
                            }
                        } else {
                            for (nm_size_t k=0; k<(nm_size_t)num_keys; k++) {
                                result[res_i++] = {(nm_size_t)from,(nm_size_t)to,(nm_size_t)k};
                            }
                        }
                    }
                };

                if constexpr (is_none_v<nbunch_t>) {
                    // all nodes, in ascending order
                    for (nm_size_t dst_idx=0; dst_idx<(nm_size_t)num_nodes; dst_idx++) {
                        emit_in_edges_of(dst_idx);
                    }
                } else if constexpr (meta::is_index_v<nbunch_t>) {
                    if ((nm_size_t)nbunch < (nm_size_t)num_nodes) {
                        emit_in_edges_of(nbunch);
                    }
                } else {
                    // nbunch container: keep the given order,
                    // skip duplicates and out-of-range entries
                    auto num_targets = len(nbunch);
                    for (nm_size_t t=0; t<(nm_size_t)num_targets; t++) {
                        auto dst_idx = at(nbunch,t);
                        if ((nm_size_t)dst_idx >= (nm_size_t)num_nodes) {
                            continue;
                        }
                        auto seen = false;
                        for (nm_size_t p=0; p<t; p++) {
                            seen |= ((nm_size_t)at(nbunch,p) == (nm_size_t)dst_idx);
                        }
                        if (!seen) {
                            emit_in_edges_of(dst_idx);
                        }
                    }
                }

                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(res_i);
                }
            }

            return result;
        }
    }
} // namespace nmtools::network

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct IN_EDGES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t, typename nbunch_t, typename multi_t, typename node_ids_t>
    struct resolve_optype<
        void, tag::in_edges_t, adjacency_list_t, nbunch_t, multi_t, node_ids_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>
                || !(is_none_v<nbunch_t> || is_index_array_v<nbunch_t> || is_index_v<nbunch_t>)
                || !(is_none_v<node_ids_t> || is_index_array_v<node_ids_t>)
            ) {
                using type = error::IN_EDGES_UNSUPPORTED<adjacency_list_t,nbunch_t,node_ids_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_adjacency_list_v<adjacency_list_t>
                && (is_none_v<nbunch_t> || is_constant_index_array_v<nbunch_t> || is_constant_index_v<nbunch_t>)
                && (is_none_v<node_ids_t> || is_constant_index_array_v<node_ids_t>)
            ) {
                constexpr auto adjacency_list = to_value_v<adjacency_list_t>;
                constexpr auto nbunch   = to_value_v<nbunch_t>;
                constexpr auto node_ids = to_value_v<node_ids_t>;
                constexpr auto result   = network::in_edges(adjacency_list,nbunch,multi_t{},node_ids);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    constexpr auto edge = at(result,I);
                    using src_t = ct<at(edge,0)>;
                    using dst_t = ct<at(edge,1)>;
                    if constexpr (multi_t::value) {
                        using key_t = ct<at(edge,2)>;
                        using type = append_type_t<init_t,nmtools_tuple<src_t,dst_t,key_t>>;
                        return as_value_v<type>;
                    } else {
                        using type = append_type_t<init_t,nmtools_tuple<src_t,dst_t>>;
                        return as_value_v<type>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else {
                // TODO: deduce index type from ajdacency list (e.g. keep int8 as int8)
                using index_t = nm_size_t;
                using index_pair_t = nmtools_array<index_t,2+multi_t::value>;
                [[maybe_unused]]
                constexpr auto B_NUM_NODES = max_len_v<adjacency_list_t>;
                if constexpr (is_tuple_v<adjacency_list_t>) {
                    constexpr auto NUM_NODES = len_v<adjacency_list_t>;
                    // assume worst-case: NUM_NODES * NUM_NODES
                    constexpr auto B_NUM_NEIGHBORS = NUM_NODES * NUM_NODES;
                    using type = nmtools_static_vector<index_pair_t,B_NUM_NEIGHBORS>;
                    return as_value_v<type>;
                } else if constexpr (B_NUM_NODES >= 0) {
                    // assume worst-case: NUM_NODES * NUM_NODES
                    constexpr auto B_NUM_NEIGHBORS = B_NUM_NODES * B_NUM_NODES;
                    using type = nmtools_static_vector<index_pair_t,B_NUM_NEIGHBORS>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<index_pair_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_NETWORK_IN_EDGES_HPP
