#ifndef NMTOOLS_NETWORK_PREDECESSORS_HPP
#define NMTOOLS_NETWORK_PREDECESSORS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"

namespace nmtools::tag
{
    struct predecessors_t {};
}

namespace nmtools::network
{
    template <typename adjacency_list_t>
    constexpr auto predecessors(const adjacency_list_t& adj_list)
    {
        if constexpr (meta::is_maybe_v<adjacency_list_t>) {
            using result_t = decltype(predecessors(unwrap(adj_list)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adj_list)
                ? return_t{predecessors(unwrap(adj_list))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::predecessors_t,adjacency_list_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_adjacency_list_v<result_t>
            ) {
                [[maybe_unused]]
                auto num_nodes = len(adj_list);
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(num_nodes);
                }

                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    const auto& edges = at(adj_list,i);
                    for (nm_size_t j=0; j<(nm_size_t)len(edges); j++) {
                        auto edge = at(edges,j);
                        at(result,edge).push_back(i);
                    }
                }
            }

            return result;
        }
    } // predecessors

    template <typename adjacency_list_t, typename node_idx_t>
    constexpr auto predecessors(const adjacency_list_t& adj_list, node_idx_t node_idx)
    {
        if constexpr (meta::is_maybe_v<adjacency_list_t>
            || meta::is_maybe_v<node_idx_t>
        ) {
            using result_t = decltype(predecessors(unwrap(adj_list),unwrap(node_idx)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adj_list) && has_value(node_idx)
                ? return_t{predecessors(unwrap(adj_list),unwrap(node_idx))}
                : return_t{meta::Nothing}
            );
        } else {
            auto num_nodes = len(adj_list);
            
            auto all_nodes = predecessors(adj_list);
            using result_t = meta::remove_cvref_t<decltype(at(all_nodes,node_idx))>;
            // TODO: check if NUM_NODES is constant & node_idx is constant index
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;

            return (((nm_size_t)node_idx < (nm_size_t)num_nodes)
                ? return_t{at(all_nodes,node_idx)}
                : return_t{meta::Nothing}
            );
        }
    }
} // namespace nmtools::network

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct PREDECESSORS_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t>
    struct resolve_optype<
        void, tag::predecessors_t, adjacency_list_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>) {
                using type = error::PREDECESSORS_UNSUPPORTED<adjacency_list_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_adjacency_list_v<adjacency_list_t>) {
                constexpr auto adjacency_list = to_value_v<adjacency_list_t>;
                constexpr auto result = network::predecessors(adjacency_list);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    constexpr auto neighbors = at(result,I);
                    auto inner_vtype = template_reduce<len(neighbors)>([&](auto init, auto index){
                        using init_t = type_t<decltype(init)>;
                        constexpr auto J = decltype(index)::value;
                        using type = append_type_t<init_t,ct<at(neighbors,J)>>;
                        return as_value_v<type>;
                    }, as_value_v<nmtools_tuple<>>);
                    using inner_t = type_t<decltype(inner_vtype)>;
                    using type = append_type_t<init_t,inner_t>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                // TODO: handle constant adjacency list

                constexpr auto NUM_NODES = len_v<adjacency_list_t>;
                constexpr auto B_NUM_NODES = max_len_v<adjacency_list_t>;

                // TODO: deduce index type from adjacency_list_t
                using index_t = nm_index_t;

                if constexpr (NUM_NODES >= 0) {
                    using inner_type = nmtools_static_vector<index_t,NUM_NODES>;
                    using outer_type = nmtools_array<inner_type,NUM_NODES>;
                    using type = outer_type;
                    return as_value_v<type>;
                } else if constexpr (B_NUM_NODES >= 0) {
                    using inner_type = nmtools_static_vector<index_t,B_NUM_NODES>;
                    using outer_type = nmtools_static_vector<inner_type,B_NUM_NODES>;
                    using type = outer_type;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using inner_type = nmtools_list<index_t>;
                    using outer_type = nmtools_list<inner_type>;
                    using type = outer_type;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // tag::predecessors_t
} // namespace nmtools::meta

#endif // NMTOOLS_NETWORK_PREDECESSORS_HPP