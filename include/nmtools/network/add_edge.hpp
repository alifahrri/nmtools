#ifndef NMTOOLS_NETWORK_ADD_EDGE_HPP
#define NMTOOLS_NETWORK_ADD_EDGE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/contains.hpp"

namespace nmtools::tag
{
    struct add_edge_t {};
}

namespace nmtools::network
{
    template <typename adjacency_list_t, typename from_t, typename to_t, typename multi_t=meta::false_type>
    constexpr auto add_edge(const adjacency_list_t& adj_list, from_t from, to_t to, multi_t multi=multi_t{})
    {
        if constexpr (meta::is_maybe_v<to_t> 
            || meta::is_maybe_v<from_t> 
            || meta::is_maybe_v<adjacency_list_t>
            || meta::is_maybe_v<multi_t>
        ) {
            using result_t = decltype(add_edge(unwrap(adj_list),unwrap(from),unwrap(to),unwrap(multi)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adj_list) && has_value(from) && has_value(to) && has_value(multi)
                ? return_t{add_edge(unwrap(adj_list),unwrap(from),unwrap(to),unwrap(multi))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::add_edge_t,adjacency_list_t,from_t,to_t,multi_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_adjacency_list_v<result_t>
            ) {
                auto num_nodes = len(adj_list);

                auto dst_num_nodes = num_nodes;

                if ((nm_index_t)from >= (nm_index_t)num_nodes) {
                    dst_num_nodes += (from - num_nodes + 1);
                }
                if ((nm_index_t)to >= (nm_index_t)dst_num_nodes) {
                    dst_num_nodes += (to - dst_num_nodes + 1);
                }

                // TODO: add from & to if not exists already
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(dst_num_nodes);
                }

                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    const auto& src_neighbors = at(adj_list,i);
                    auto& dst_neighbors = at(result,i);

                    auto src_num_neighbors = len(src_neighbors);
                    auto dst_num_neighbors = src_num_neighbors;
                    if (i == (nm_size_t)from) {
                        if (!(index::contains(src_neighbors,to)) || multi) {
                            dst_num_neighbors += 1;
                        }
                    }

                    if constexpr (meta::is_resizable_v<decltype(dst_neighbors)>) {
                        dst_neighbors.resize(dst_num_neighbors);
                    }

                    for (nm_size_t j=0; j<(nm_size_t)src_num_neighbors; j++) {
                        at(dst_neighbors,j) = at(src_neighbors,j);
                    }
                    if ((dst_num_neighbors > src_num_neighbors)) {
                        at(dst_neighbors,dst_num_neighbors-1) = to;
                    }
                }

                // add edge from non-existent node
                if ((nm_index_t)from >= (nm_index_t)num_nodes) {
                    at(result,from).push_back(to);
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
        struct ADD_EDGE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t, typename from_t, typename to_t, typename multi_t>
    struct resolve_optype<
        void, tag::add_edge_t, adjacency_list_t, from_t, to_t, multi_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_v<to_t>
                || !is_index_v<from_t>
                || !is_adjacency_list_v<adjacency_list_t>
                || !is_index_v<multi_t>
            ) {
                using type = error::ADD_EDGE_UNSUPPORTED<adjacency_list_t,from_t,to_t,multi_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_v<to_t>
                && is_constant_index_v<from_t>
                && is_constant_adjacency_list_v<adjacency_list_t>
                && is_constant_index_v<multi_t>
            ) {
                constexpr auto adj_list = to_value_v<adjacency_list_t>;
                constexpr auto from  = to_value_v<from_t>;
                constexpr auto to    = to_value_v<to_t>;
                constexpr auto multi = to_value_v<multi_t>;
                constexpr auto m_result = network::add_edge(adj_list,from,to,multi);
                constexpr auto result   = unwrap(m_result);
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
                    constexpr auto DST_NUM_NODES = NUM_NODES + 2;
                    using inner_t = nmtools_static_vector<index_t,DST_NUM_NODES*2>;
                    using outer_t = nmtools_static_vector<inner_t,DST_NUM_NODES>;
                    using type = outer_t;
                    return as_value_v<type>;
                } else if constexpr (B_NUM_NODES >= 0) {
                    constexpr auto DST_B_NUM_NODES = B_NUM_NODES + 2;
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

#endif // NMTOOLS_NETWORK_ADD_EDGE_HPP