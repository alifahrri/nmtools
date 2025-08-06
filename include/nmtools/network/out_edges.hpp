#ifndef NMTOOLS_NETWORK_OUT_EDGES_HPP
#define NMTOOLS_NETWORK_OUT_EDGES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/index_of.hpp"
#include "nmtools/index/unique.hpp"
#include "nmtools/network/map_ids.hpp"

namespace nmtools::tag
{
    struct out_edges_t {};
}

namespace nmtools::network
{
    // NOTE: not accepting node_ids because returning a transformed out edges will results in inconsistent indexing of src & dst
    template <typename adjacency_list_t, typename nbunch_t=none_t, typename multi_t=meta::false_type, typename node_ids_t=none_t>
    constexpr auto out_edges(const adjacency_list_t& adj_list, const nbunch_t& nbunch=nbunch_t{}, multi_t=multi_t{}, const node_ids_t& node_ids=node_ids_t{})
    {
        constexpr auto multi = multi_t{};
        if constexpr (meta::is_maybe_v<adjacency_list_t>
            || meta::is_maybe_v<nbunch_t>
            || meta::is_maybe_v<node_ids_t>
        ) {
            using result_t = decltype(out_edges(unwrap(adj_list),unwrap(nbunch),multi,unwrap(node_ids)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adj_list) && has_value(nbunch)
                ? return_t{out_edges(unwrap(adj_list),unwrap(nbunch),multi,unwrap(node_ids))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::out_edges_t,adjacency_list_t,nbunch_t,multi_t,node_ids_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_adjacency_list_v<result_t>
            ) {
                [[maybe_unused]]
                auto num_nodes = len(adj_list);
                auto num_edges = 0;
                if constexpr (meta::is_tuple_v<adjacency_list_t>) {
                    constexpr auto N = meta::len_v<adjacency_list_t>;
                    meta::template_for<N>([&](auto I){
                        num_edges += len(at(adj_list,I));
                    });
                } else {
                    for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                        num_edges += len(at(adj_list,i));
                    }
                }
            
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(num_edges);
                }

                auto res_i = 0;
                auto inner_loop = [&](auto I){
                    auto node_id = I;
                    const auto& neighbors = at(adj_list,I);
                    auto num_neighbors = len(neighbors);
                    if constexpr (meta::is_index_array_v<nbunch_t>) {
                        auto node_idx = index::index_of(nbunch,node_id);
                        if (!has_value(node_idx)) {
                            return;
                        }
                    } else if constexpr (meta::is_index_v<nbunch_t>) {
                        if ((nm_size_t)nbunch != (nm_size_t)node_id) {
                            return;
                        }
                    }
                    auto from = [&](){
                        if constexpr (is_none_v<node_ids_t>) {
                            return node_id;
                        } else {
                            return unwrap(map_ids(node_id,node_ids));
                        }
                    }();
                    if constexpr (!multi) {
                        for (nm_size_t j=0; j<(nm_size_t)num_neighbors; j++) {
                            auto to = [&](){
                                if constexpr (is_none_v<node_ids_t>) {
                                    return at(neighbors,j);
                                } else {
                                    return unwrap(map_ids(at(neighbors,j),node_ids));
                                }
                            }();
                            // TODO: get the index type from result_t
                            result[res_i++] = {(nm_size_t)from,(nm_size_t)to};
                        }
                    } else {
                        auto unique_neighbors = index::unique(neighbors);
                        auto num_unique_neighbors = len(unique_neighbors);
                        for (nm_size_t j=0; j<(nm_size_t)num_unique_neighbors; j++) {
                            auto to = [&](){
                                if constexpr (is_none_v<node_ids_t>) {
                                    return at(unique_neighbors,j);
                                } else {
                                    return unwrap(map_ids(at(unique_neighbors,j),node_ids));
                                }
                            }();
                            auto dst = at(unique_neighbors,j);
                            auto num_keys = len(unwrap(index::index_of(neighbors,dst,True)));
                            for (nm_size_t k=0; k<(nm_size_t)num_keys; k++) {
                                result[res_i++] = {(nm_size_t)from,(nm_size_t)to,(nm_size_t)k};
                            }
                        }
                    }
                };

                if constexpr (meta::is_tuple_v<adjacency_list_t>) {
                    constexpr auto NUM_NODES = meta::len_v<adjacency_list_t>;
                    meta::template_for<NUM_NODES>([&](auto I){
                        inner_loop(I);
                    });
                } else {
                    for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                        inner_loop(i);
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
        struct OUT_EDGES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t, typename nbunch_t, typename multi_t, typename node_ids_t>
    struct resolve_optype<
        void, tag::out_edges_t, adjacency_list_t, nbunch_t, multi_t, node_ids_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>
                || !(is_none_v<nbunch_t> || is_index_array_v<nbunch_t> || is_index_v<nbunch_t>)
                || !(is_none_v<node_ids_t> || is_index_array_v<node_ids_t>)
            ) {
                using type = error::OUT_EDGES_UNSUPPORTED<adjacency_list_t,nbunch_t,node_ids_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_adjacency_list_v<adjacency_list_t>
                && (is_none_v<nbunch_t> || is_constant_index_array_v<nbunch_t> || is_constant_index_v<nbunch_t>)
                && (is_none_v<node_ids_t> || is_constant_index_array_v<node_ids_t>)
            ) {
                constexpr auto adjacency_list = to_value_v<adjacency_list_t>;
                constexpr auto nbunch   = to_value_v<nbunch_t>;
                constexpr auto node_ids = to_value_v<node_ids_t>;
                constexpr auto result   = network::out_edges(adjacency_list,nbunch,multi_t{},node_ids);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    constexpr auto pair = at(result,I);
                    using src_t = ct<at(pair,0)>;
                    using dst_t = ct<at(pair,1)>;
                    using type = append_type_t<init_t,nmtools_tuple<src_t,dst_t>>;
                    return as_value_v<type>;
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

#endif // NMTOOLS_NETWORK_OUT_EDGES_HPP