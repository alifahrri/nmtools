#ifndef NMTOOLS_NETWORK_REMOVE_EDGE_HPP
#define NMTOOLS_NETWORK_REMOVE_EDGE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/index_of.hpp"

namespace nmtools::tag
{
    struct remove_edge_t {};
    struct remove_edge_attributes_t {};
}

namespace nmtools::network
{
    template <typename adjacency_list_t, typename from_t, typename to_t, typename multi_t=meta::false_type, typename key_t=none_t>
    constexpr auto remove_edge(const adjacency_list_t& adj_list, from_t from, to_t to, multi_t multi=multi_t{}, key_t key=key_t{})
    {
        if constexpr (meta::is_maybe_v<to_t>
            || meta::is_maybe_v<from_t>
            || meta::is_maybe_v<multi_t>
            || meta::is_maybe_v<adjacency_list_t>
            || meta::is_maybe_v<key_t>
        ) {
            using result_t = decltype(remove_edge(unwrap(adj_list),unwrap(from),unwrap(from),unwrap(multi),unwrap(key)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adj_list) && has_value(from) && has_value(to) && has_value(multi) && has_value(key)
                ? return_t{remove_edge(unwrap(adj_list),unwrap(from),unwrap(from),unwrap(multi),unwrap(key))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::remove_edge_t,adjacency_list_t,from_t,to_t,multi_t,key_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_adjacency_list_v<result_t>
            ) {
                auto num_nodes = len(adj_list);

                // assume inner and outer has push_back
                using inner_t = meta::get_value_type_t<result_t>;

                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    const auto& src_neighbors = at(adj_list,i);
                    auto dst_neighbors = inner_t{};

                    auto to_remove = index::index_of(src_neighbors,to,True);
                    [[maybe_unused]] auto key_idx = 0;
                    [[maybe_unused]] auto key_id  = 0;
                    if (has_value(to_remove)) {
                        key_id = at(unwrap(to_remove),-1);
                        if constexpr (!is_none_v<key_t>) {
                            if (len(unwrap(to_remove)) > 1) {
                                key_id = key;
                            }
                        }
                    }

                    auto src_num_neighbors = len(src_neighbors);
                    auto erased = false;
                    for (nm_size_t j=0; j<(nm_size_t)src_num_neighbors; j++) {
                        auto src_to = at(src_neighbors,j);
                        if ((nm_index_t)from == (nm_index_t)i) {
                            if (
                                ((nm_index_t)src_to == (nm_index_t)to)
                                && !erased
                                && ((nm_index_t)key_id == (nm_index_t)j)
                            ) {
                                erased = multi;
                                continue;
                            }
                        }
                        dst_neighbors.push_back(src_to);
                    }
                    result.push_back(dst_neighbors);
                }
            }

            return result;
        }
    } // remove_edge

    template <typename src_adjacency_list_t, typename edge_attributes_t, typename from_t, typename to_t, typename key_t=none_t>
    constexpr auto remove_edge_attributes(const src_adjacency_list_t& src_adj_list, const edge_attributes_t& edge_attributes, from_t from, to_t to, [[maybe_unused]] key_t key=key_t{})
    {
        if constexpr (is_none_v<edge_attributes_t>) {
            return None;
        } else {
            // auto result_t = meta::resolve_optype_t<edge_attributes_t,from_t,to_t,key_t>;
            using result_t = edge_attributes_t;

            auto result = result_t {};

            // assume inner and outer has push_back

            using inner_t = meta::get_value_type_t<result_t>;
            // using value_t = meta::get_value_type_t<inner_t>;

            auto num_nodes = len(src_adj_list);

            for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                const auto& neighbor_idxs = at(src_adj_list,i);
                const auto& neighbor_edges = at(edge_attributes,i);
                auto num_edges = len(neighbor_edges);
                auto neighbors = inner_t {};

                auto to_remove = index::index_of(neighbor_idxs,to,True);
                auto key_idx = 0;
                auto key_id  = 0;
                if (has_value(to_remove)) {
                    key_id = len(unwrap(to_remove));
                    if constexpr (!is_none_v<key_t>) {
                        if (len(unwrap(to_remove)) > 1) {
                            key_id = key;
                        }
                    }
                }
                for (nm_size_t j=0; j<(nm_size_t)num_edges; j++) {
                    const auto edge_idx = at(neighbor_idxs,j);
                    const auto& edge = at(neighbor_edges,j);
                    if ((nm_index_t)from == (nm_index_t)i) {
                        if ((nm_index_t)edge_idx == (nm_index_t)to) {
                            if (key_id == key_idx++) {
                                continue;
                            }
                        }
                    }
                    neighbors.push_back(edge);
                }
                result.push_back(neighbors);
            }

            return result;
        }
    }
}

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct REMOVE_EDGE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t, typename from_t, typename to_t, typename multi_t, typename key_t>
    struct resolve_optype<
        void, tag::remove_edge_t, adjacency_list_t, from_t, to_t, multi_t, key_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_v<to_t>
                || !is_index_v<from_t>
                || !is_index_v<multi_t>
                || !is_adjacency_list_v<adjacency_list_t>
                || !(is_index_v<key_t> || is_none_v<key_t>)
            ) {
                using type = error::REMOVE_EDGE_UNSUPPORTED<adjacency_list_t,from_t,to_t,multi_t,key_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_v<to_t>
                && is_constant_index_v<from_t>
                && is_constant_index_v<multi_t>
                && is_constant_adjacency_list_v<adjacency_list_t>
                && (is_constant_index_v<key_t> || is_none_v<key_t>)
            ) {
                constexpr auto adj_list = to_value_v<adjacency_list_t>;
                constexpr auto from   = to_value_v<from_t>;
                constexpr auto to     = to_value_v<to_t>;
                constexpr auto multi  = to_value_v<multi_t>;
                constexpr auto key    = to_value_v<key_t>;
                constexpr auto result = unwrap(network::remove_edge(adj_list,from,to,multi,key));
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
                constexpr auto B_NUM_NODES = max_len_v<adjacency_list_t>;

                // TODO: deduce index type from adjacency_list_t
                using index_t = nm_index_t;
                if constexpr (NUM_NODES >= 0) {
                    constexpr auto DST_NUM_NODES = NUM_NODES;
                    using inner_t = nmtools_static_vector<index_t,DST_NUM_NODES*2>;
                    using outer_t = nmtools_static_vector<inner_t,DST_NUM_NODES>;
                    using type = outer_t;
                    return as_value_v<type>;
                } else if constexpr (B_NUM_NODES >= 0) {
                    constexpr auto DST_B_NUM_NODES = B_NUM_NODES;
                    using inner_t = nmtools_static_vector<index_t,DST_B_NUM_NODES*2>;
                    using outer_t = nmtools_static_vector<inner_t,DST_B_NUM_NODES>;
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
    };
}

#endif // NMTOOLS_NETWORK_REMOVE_EDGE_HPP