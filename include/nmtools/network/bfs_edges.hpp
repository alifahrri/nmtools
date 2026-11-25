#ifndef NMTOOLS_NETWORK_BFS_EDGES_HPP
#define NMTOOLS_NETWORK_BFS_EDGES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/network/predecessors.hpp"
#include "nmtools/index/cast.hpp"
#include "nmtools/index/contains.hpp"

namespace nmtools::tag
{
    struct bfs_edges_t {};
}

namespace nmtools::network
{
    template <typename adjacency_list_t, typename source_idx_t, typename reverse_t=meta::false_type>
    constexpr auto bfs_edges([[maybe_unused]] const adjacency_list_t& adjacency_list
        , [[maybe_unused]] source_idx_t source_idx
        , [[maybe_unused]] reverse_t reverse=reverse_t{})
    {
        if constexpr (is_maybe_v<adjacency_list_t> || is_maybe_v<source_idx_t> || is_maybe_v<reverse_t>) {
            using result_t = decltype(bfs_edges(unwrap(adjacency_list),unwrap(source_idx),unwrap(reverse)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adjacency_list) && has_value(source_idx) && has_value(reverse)
                ? return_t{bfs_edges(unwrap(adjacency_list),unwrap(source_idx),unwrap(reverse))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = resolve_optype_t<tag::bfs_edges_t,adjacency_list_t,source_idx_t,reverse_t>;

            // the resulting pair will strictly 2 element
            // so index array is appropriate
            // though assume has push back with pair

            if constexpr (!is_fail_v<result_t>
                && !is_constant_adjacency_list_v<result_t>
                && !is_constant_index_array_v<result_t>
            ) {
                auto result = result_t {};

                using index_t = nm_size_t;
                auto id_list_vtype = [](){
                    constexpr auto MAX_NODES = max_len_v<adjacency_list_t>;
                    if constexpr (MAX_NODES > 0) {
                        using type = nmtools_static_vector<index_t,MAX_NODES>;
                        return as_value_v<type>;
                    } else {
                        // TODO: use small vector
                        using type = nmtools_list<index_t>;
                        return as_value_v<type>;
                    }
                }();
                using id_list_t = type_t<decltype(id_list_vtype)>;
                using return_t = nmtools_maybe<result_t>;

                auto visited  = id_list_t{};
                auto frontier = id_list_t{};

                // assume has push_back

                visited.push_back(source_idx);
                frontier.push_back(source_idx);

                decltype(auto) adj_list = [&](){
                    if constexpr (is_constant_adjacency_list_v<adjacency_list_t>) {
                        return to_value_v<adjacency_list_t>;
                    } else {
                        return (adjacency_list);
                    }
                }();
                [[maybe_unused]]
                const auto m_preds = predecessors(adj_list);
                auto valid = has_value(m_preds);

                if (!valid) {
                    return return_t{meta::Nothing};
                }
                auto preds = unwrap(m_preds);

                auto neighbors = [&](auto u) -> id_list_t {
                    if (reverse) {
                        return index::cast<id_list_t>(at(preds,u));
                    } else {
                        return index::cast<id_list_t>(at(adj_list,u));
                    }
                };

                auto num_nodes = len(adj_list);

                valid &= (index_t)source_idx < (index_t)num_nodes;

                while (frontier.size() && valid) {
                    auto next = id_list_t {};

                    for (const auto& u : frontier) {
                        for (const auto& w : neighbors(u)) {
                            if (!index::contains(visited,w)) {
                                visited.push_back(w);
                                result.push_back({(index_t)u,(index_t)w});
                                next.push_back(w);
                            }
                        }
                    }

                    frontier = next;
                }

                if (valid) {
                    return return_t{result};
                } else {
                    return return_t{meta::Nothing};
                }
            } else {
                auto result = result_t {};
                return result;
            }
        }
    }
} // namespace nmtools::network

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct BFS_EDGES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t, typename source_idx_t, typename reverse_t>
    struct resolve_optype<
        void, tag::bfs_edges_t, adjacency_list_t, source_idx_t, reverse_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_v<source_idx_t>
                || !is_adjacency_list_v<adjacency_list_t>
                || !is_index_v<reverse_t>
            ) {
                using type = error::BFS_EDGES_UNSUPPORTED<adjacency_list_t,source_idx_t,reverse_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_v<reverse_t>
                && is_constant_adjacency_list_v<adjacency_list_t>
                && is_constant_index_v<source_idx_t>
            ) {
                constexpr auto adjacency_list = to_value_v<adjacency_list_t>;
                constexpr auto source_idx = to_value_v<source_idx_t>;
                constexpr auto reverse = to_value_v<reverse_t>;
                constexpr auto result  = unwrap(network::bfs_edges(adjacency_list,source_idx,reverse));
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    using init_t = type_t<decltype(init)>;
                    constexpr auto pair = at(result,I);
                    // assume len(neighbors) == 2
                    constexpr auto discoverer = at(pair,0);
                    constexpr auto discovered = at(pair,1);
                    using pair_t = nmtools_tuple<ct<discoverer>,ct<discovered>>;
                    using type = append_type_t<init_t,pair_t>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto MAX_NODES = max_len_v<adjacency_list_t>;
                using index_t = nm_size_t;
                using pair_t  = nmtools_array<index_t,2>;
                if constexpr (MAX_NODES > 0) {
                    using type = nmtools_static_vector<pair_t,MAX_NODES>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<pair_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_NETWORK_BFS_EDGES_HPP