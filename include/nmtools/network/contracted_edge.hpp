#ifndef NMTOOLS_NETWORK_CONTRACTED_EDGE_HPP
#define NMTOOLS_NETWORK_CONTRACTED_EDGE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/contains.hpp"
#include "nmtools/index/sorted.hpp"

namespace nmtools::tag
{
    struct contracted_edge_t {};
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
} // namespace nmtools::network

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct CONTRACTED_EDGE_UNSUPPORTED : detail::fail_t {};
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
} // namespace nmtools::meta

#endif // NMTOOLS_NETWORK_CONTRACTED_EDGE_HPP