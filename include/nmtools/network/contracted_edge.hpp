#ifndef NMTOOLS_NETWORK_CONTRACTED_EDGE_HPP
#define NMTOOLS_NETWORK_CONTRACTED_EDGE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/contains.hpp"
#include "nmtools/index/sorted.hpp"

namespace nmtools::tag
{
    struct contracted_edge_t {};
    struct filter_contracted_ids_t {};
    struct filter_contracted_nodes_t {};
}

namespace nmtools::network
{
    template <typename adjacency_list_t, typename edge_t, typename self_loops_t>
    constexpr auto contracted_edge(const adjacency_list_t& adj_list, const edge_t& edge, self_loops_t self_loops)
    {
        if constexpr (meta::is_maybe_v<adjacency_list_t>
            || meta::is_maybe_v<edge_t>
            || meta::is_maybe_v<self_loops_t>
        ) {
            using result_t = decltype(contracted_edge(unwrap(adj_list),unwrap(edge),unwrap(self_loops)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adj_list) && has_value(edge) && has_value(self_loops)
                ? return_t{contracted_edge(unwrap(adj_list),unwrap(edge),unwrap(self_loops))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::contracted_edge_t,adjacency_list_t,edge_t,self_loops_t>;

            auto result = result_t {};

            if constexpr (!meta::is_constant_adjacency_list_v<result_t>
                && !meta::is_fail_v<result_t>
            ) {
                auto num_nodes = len(adj_list);

                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(num_nodes-1);
                }

                auto src_node = at(edge,meta::ct_v<0>);
                auto dst_node = at(edge,meta::ct_v<1>); // assume dst is to be removed

                auto to_new_node_idx = [&](auto src_idx){
                    if ((nm_index_t)src_idx >= (nm_index_t)dst_node) {
                        return (nm_index_t)src_idx - 1;
                    } else {
                        return (nm_index_t)src_idx;
                    }
                };

                // auto to_remove = dst_node;
                // auto to_keep   = src_node;
                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    auto src_idx = i;
                    auto dst_idx = to_new_node_idx(src_idx);

                    if ((nm_index_t)src_idx == (nm_index_t)dst_node) {
                        // absorb by append all dst successors to src
                        dst_idx = src_node;
                    }

                    const auto& successors = at(adj_list,src_idx);

                    for (auto src_successor : successors) {
                        auto dst_successor = to_new_node_idx(src_successor);
                        if (((nm_index_t)src_idx == (nm_index_t)src_node) || ((nm_index_t)src_idx == (nm_index_t)dst_node)) {
                            if (((nm_index_t)src_successor == (nm_index_t)src_node) || ((nm_index_t)src_successor == (nm_index_t)dst_node)) {
                                continue;
                            }
                        }
                        if (!index::contains(at(result,dst_idx),dst_successor)) {
                            if ((dst_successor != dst_idx)) {
                                at(result,dst_idx).push_back(dst_successor);
                            }
                        }
                    }
                }

                if (self_loops) {
                    // check if any self loop
                    if (index::contains(at(adj_list,src_node),dst_node)
                        && index::contains(at(adj_list,dst_node),src_node)
                    ) {
                        auto dst_idx = to_new_node_idx(src_node);
                        at(result,dst_idx).push_back(dst_idx);
                    }
                }

                // sort result
                for (nm_size_t i=0; i<(nm_size_t)len(result); i++) {
                    // TODO: use sort from array
                    auto sorted_neighbors = index::sorted(at(result,i));
                    for (nm_size_t j=0; j<(nm_size_t)len(sorted_neighbors); j++) {
                        at(at(result,i),j) = at(sorted_neighbors,j);
                    }
                }
            }

            return result;
        }
    } // namespace contracted_edge

    template <typename src_node_ids_t, typename edge_t>
    constexpr auto filter_contracted_ids(const src_node_ids_t& src_node_ids, const edge_t& edge)
    {
        if constexpr (meta::is_maybe_v<src_node_ids_t> || meta::is_maybe_v<edge_t>) {
            using result_t = decltype(filter_contracted_ids(unwrap(src_node_ids),unwrap(edge)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(src_node_ids) && has_value(edge)
                ? return_t{filter_contracted_ids(unwrap(src_node_ids),unwrap(edge))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::filter_contracted_ids_t,src_node_ids_t,edge_t>;
            
            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_index_array_v<result_t>
            ) {
                // TODO: what happened if from or to in edge doesn't exists in src_node_ids?

                auto num_nodes = len(src_node_ids);

                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(num_nodes);
                }

                const auto from = at(edge,meta::ct_v<0>);

                auto idx = 0;
                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    auto node_id = at(src_node_ids,i);
                    if ((nm_index_t)from == (nm_index_t)node_id) {
                        continue;
                    }
                    at(result,idx++) = node_id;
                }

                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(idx+1);
                }
            }

            return result;
        }
    } // filter_contracted_ids

    template <typename node_attributes_t, typename src_node_ids_t, typename edge_t, typename node_t=none_t>
    constexpr auto filter_contracted_nodes(const node_attributes_t& node_attributes
        , const src_node_ids_t& src_node_ids
        , const edge_t& edge
        , const node_t& node=node_t{})
    {
        if constexpr (meta::is_maybe_v<edge_t>
            || meta::is_maybe_v<node_attributes_t>
            || meta::is_maybe_v<src_node_ids_t>
            || meta::is_maybe_v<node_t>
        ) {
            using result_t = decltype(filter_contracted_nodes(
                unwrap(node_attributes)
                , unwrap(src_node_ids)
                , unwrap(edge)
                , unwrap(node)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(node_attributes) && has_value(src_node_ids) && has_value(edge) && has_value(node)
                ? return_t{filter_contracted_nodes(
                    unwrap(node_attributes)
                    , unwrap(src_node_ids)
                    , unwrap(edge)
                    , unwrap(node))
                } : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::filter_contracted_nodes_t,node_attributes_t,src_node_ids_t,edge_t,node_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>) {
                // assume len(node_attributes) == len(src_node_ids)
                const auto num_nodes = len(src_node_ids);

                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(num_nodes);
                }

                const auto from = at(edge,meta::ct_v<0>);
                const auto to   = at(edge,meta::ct_v<1>);

                auto idx = 0;
                // TODO: handle tuple
                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    auto node_id = at(src_node_ids,i);
                    auto node_i  = at(node_attributes,i);
                    if ((nm_index_t)from == (nm_index_t)node_id) {
                        continue;
                    } else if (((nm_index_t)to == (nm_index_t)node_id)) {
                        if constexpr (!is_none_v<node_t>) {
                            node_i = node;
                        }
                    }
                    at(result,idx++) = node_i;
                }

                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(idx+1);
                }
            }

            return result;
        }
    } // filter_contracted_nodes
} // namespace nmtools::network

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct CONTRACTED_EDGE_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct FILTER_CONTRACTED_IDS_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct FILTER_CONTRACTED_NODES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t, typename edge_t, typename self_loops_t>
    struct resolve_optype<
        void, tag::contracted_edge_t, adjacency_list_t, edge_t, self_loops_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (
                !is_adjacency_list_v<adjacency_list_t>
                || !is_index_array_v<edge_t>
                || !is_index_v<self_loops_t>
            ) {
                using type = error::CONTRACTED_EDGE_UNSUPPORTED<adjacency_list_t,edge_t,self_loops_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_adjacency_list_v<adjacency_list_t>
                && is_constant_index_array_v<edge_t>
                && is_constant_index_v<self_loops_t>
            ) {
                constexpr auto adjacency_list = to_value_v<adjacency_list_t>;
                constexpr auto edge       = to_value_v<edge_t>;
                constexpr auto self_loops = to_value_v<self_loops_t>;
                constexpr auto result     = network::contracted_edge(adjacency_list,edge,self_loops);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    using init_t = type_t<decltype(init)>;
                    constexpr auto neighbors = at(result,I);
                    constexpr auto neighbors_vtype = meta::template_reduce<len(neighbors)>([&](auto init, auto index){
                        constexpr auto J = decltype(index)::value;
                        using init_t = type_t<decltype(init)>;
                        using neighbor_t = ct<at(neighbors,J)>;
                        using type = append_type_t<init_t,neighbor_t>;
                        return as_value_v<type>;
                    }, as_value_v<nmtools_tuple<>>);
                    using neighbors_t = type_t<decltype(neighbors_vtype)>;
                    using type = append_type_t<init_t,neighbors_t>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto NUM_NODES = len_v<adjacency_list_t>;
                [[maybe_unused]]
                constexpr auto B_NUM_NODES = bounded_size_v<adjacency_list_t>;

                // TODO: deduce index type from adjacency_list_t
                using index_t = nm_index_t;
                if constexpr (NUM_NODES > 0) {
                    using inner_t = nmtools_static_vector<index_t,NUM_NODES*2>;
                    using outer_t = nmtools_array<inner_t,NUM_NODES-1>;
                    using type = outer_t;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_NUM_NODES)>) {
                    using inner_t = nmtools_static_vector<index_t,B_NUM_NODES*2>;
                    using outer_t = nmtools_static_vector<inner_t,B_NUM_NODES-1>;
                    using type = outer_t;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using inner_t = nmtools_list<index_t>;
                    using outer_t = nmtools_list<inner_t>;
                    using type = outer_t;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // tag::contracted_edge_t

    template <typename src_node_ids_t, typename edge_t>
    struct resolve_optype<
        void, tag::filter_contracted_ids_t, src_node_ids_t, edge_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<edge_t>
                || !is_index_array_v<src_node_ids_t>
            ) {
                using type = error::FILTER_CONTRACTED_IDS_UNSUPPORTED<src_node_ids_t,edge_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<edge_t>
                && is_constant_index_array_v<src_node_ids_t>
            ) {
                constexpr auto src_node_ids = to_value_v<src_node_ids_t>;
                constexpr auto edge     = to_value_v<edge_t>;
                constexpr auto m_result = network::filter_contracted_ids(src_node_ids,edge);
                constexpr auto result   = unwrap(m_result);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<(nm_size_t)at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                [[maybe_unused]]
                constexpr auto B_NUM_NODES = max_len_v<src_node_ids_t>;
                constexpr auto NUM_NODES   = len_v<src_node_ids_t>;
                if constexpr (NUM_NODES >= 0) {
                    using type = nmtools_array<nm_size_t,NUM_NODES-1>;
                    return as_value_v<type>;
                } else if constexpr (B_NUM_NODES >= 0) {
                    using type = nmtools_static_vector<nm_size_t,B_NUM_NODES-1>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // tag::filter_contracted_ids_t

    template <typename node_attributes_t, typename src_node_ids_t, typename edge_t, typename node_t>
    struct resolve_optype<
        void, tag::filter_contracted_nodes_t, node_attributes_t, src_node_ids_t, edge_t, node_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<edge_t>
                || !is_index_array_v<src_node_ids_t>
                || !(is_tuple_v<node_attributes_t> || has_value_type_v<node_attributes_t>)
                // TODO: constraints on node_t
            ) {
                using type = error::FILTER_CONTRACTED_NODES_UNSUPPORTED<node_attributes_t,src_node_ids_t,edge_t,node_t>;
                return as_value_v<type>;
            } else {
                // TODO: handle tuple
                using value_type = get_value_type_t<node_attributes_t>;
                [[maybe_unused]]
                constexpr auto B_NUM_NODES = max_len_v<src_node_ids_t>;
                constexpr auto NUM_NODES   = len_v<src_node_ids_t>;
                if constexpr (NUM_NODES >= 0) {
                    using type = nmtools_array<value_type,NUM_NODES-1>;
                    return as_value_v<type>;
                } else if constexpr (B_NUM_NODES >= 0) {
                    using type = nmtools_static_vector<value_type,B_NUM_NODES-1>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<value_type>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // tag::filter_contracted_nodes_t
} // namespace nmtools::meta

#endif // NMTOOLS_NETWORK_CONTRACTED_EDGE_HPP