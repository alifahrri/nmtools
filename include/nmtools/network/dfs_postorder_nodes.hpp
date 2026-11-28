#ifndef NMTOOLS_NETWORK_DFS_POSTORDER_NODES_HPP
#define NMTOOLS_NETWORK_DFS_POSTORDER_NODES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/cast.hpp"
#include "nmtools/index/contains.hpp"

namespace nmtools::tag
{
    struct dfs_postorder_nodes_t {};
}

namespace nmtools::network
{
    template <typename adjacency_list_t, typename source_idx_t>
    constexpr auto dfs_postorder_nodes([[maybe_unused]] const adjacency_list_t& adjacency_list
        , [[maybe_unused]] const source_idx_t& sources)
    {
        if constexpr (is_maybe_v<adjacency_list_t> || is_maybe_v<source_idx_t>) {
            using result_t = decltype(dfs_postorder_nodes(unwrap(adjacency_list),unwrap(sources)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adjacency_list) && has_value(sources)
                ? return_t{dfs_postorder_nodes(unwrap(adjacency_list),unwrap(sources))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = resolve_optype_t<tag::dfs_postorder_nodes_t,adjacency_list_t,source_idx_t>;

            if constexpr (!is_fail_v<result_t>
                && !is_constant_index_array_v<result_t>
            ) {
                using index_t = nm_size_t;
                auto id_list_vtype = [](){
                    constexpr auto MAX_NODES = max_len_v<adjacency_list_t>;
                    if constexpr (MAX_NODES >= 0) {
                        using type = nmtools_static_vector<index_t,MAX_NODES>;
                        return as_value_v<type>;
                    } else {
                        // TODO: use small vector
                        using type = nmtools_list<index_t>;
                        return as_value_v<type>;
                    }
                }();
                using id_list_t = type_t<decltype(id_list_vtype)>;
                using flag_list_t = replace_value_type_t<id_list_t,nm_bool_t>;

                decltype(auto) adj_list = [&](){
                    if constexpr (is_constant_adjacency_list_v<adjacency_list_t>) {
                        return to_value_v<adjacency_list_t>;
                    } else {
                        return (adjacency_list);
                    }
                }();

                auto n = len(adjacency_list);
                auto visited = flag_list_t {};
                visited.resize(n);
                for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                    visited[i] = false;
                }
                decltype(auto) m_sources = [&](){
                    if constexpr (is_num_v<source_idx_t>) {
                        return nmtools_array{sources};
                    } else {
                        return (sources);
                    }
                }();

                using return_t = nmtools_maybe<result_t>;

                auto valid = (n > 0);
                for (nm_size_t i=0; (i<(nm_size_t)len(m_sources)) && valid; i++) {
                    valid &= ((nm_size_t)m_sources[i] < (nm_size_t)n);
                }

                if (!valid) {
                    return return_t{meta::Nothing};
                }

                auto result = result_t{};

                auto stack_nodes = id_list_t {};
                auto stack_pos   = id_list_t {};

                for (nm_size_t i=0; i<(nm_size_t)len(m_sources); i++) {
                    auto seed = m_sources[i];
                    if (visited[seed]) {
                        continue;
                    }
                    visited[seed] = true;
                    stack_nodes.push_back(seed);
                    stack_pos.push_back(0);

                    while (stack_nodes.size()) {
                        auto u   = stack_nodes.back();
                        auto pos = stack_pos.back();
                        auto row = adj_list[u];
                        if (pos < (nm_size_t)len(row)) {
                            stack_pos.back() = pos + 1;
                            auto v = row[pos];
                            if (!visited[v]) {
                                visited[v] = true;
                                stack_nodes.push_back(v);
                                stack_pos.push_back(0);
                            }
                        } else {
                            result.push_back(u);
                            stack_nodes.pop_back();
                            stack_pos.pop_back();
                        }
                    }
                }

                return return_t{result};
            } else {
                auto result = result_t {};
                return result;
            }
        }
    }
} // nmtools::network

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct DFS_POSTORDER_NODES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t, typename sources_t>
    struct resolve_optype<
        void, tag::dfs_postorder_nodes_t, adjacency_list_t, sources_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>
                || !(is_index_v<sources_t> || is_index_array_v<sources_t>)
            ) {
                using type = error::DFS_POSTORDER_NODES_UNSUPPORTED<adjacency_list_t,sources_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_adjacency_list_v<adjacency_list_t>
                && (is_constant_index_array_v<sources_t> || is_constant_index_v<sources_t>)
            ) {
                constexpr auto adjacency_list = to_value_v<adjacency_list_t>;
                constexpr auto sources  = to_value_v<sources_t>;
                constexpr auto m_result = network::dfs_postorder_nodes(adjacency_list,sources);
                if constexpr (has_value(m_result)) {
                    constexpr auto result = unwrap(m_result);
                    using nmtools::at, nmtools::len;
                    return template_reduce<len(result)>([&](auto init, auto index){
                        constexpr auto I = decltype(index)::value;
                        using init_t = type_t<decltype(init)>;
                        using type = append_type_t<init_t,ct<at(result,I)>>;
                        return as_value_v<type>;
                    }, as_value_v<nmtools_tuple<>>);
                } else {
                    // invalid constant input (empty graph or out-of-range
                    // source): there is no constant result to fold. Fall back
                    // to the runtime container type so the invalid path can
                    // still return Nothing.
                    constexpr auto MAX_NODES = max_len_v<adjacency_list_t>;
                    using index_t = nm_size_t;
                    if constexpr (MAX_NODES >= 0) {
                        using type = nmtools_static_vector<index_t,MAX_NODES>;
                        return as_value_v<type>;
                    } else {
                        // TODO: use small vector
                        using type = nmtools_list<index_t>;
                        return as_value_v<type>;
                    }
                }
            } else {
                constexpr auto MAX_NODES = max_len_v<adjacency_list_t>;
                using index_t = nm_size_t;
                if constexpr (MAX_NODES >= 0) {
                    using type = nmtools_static_vector<index_t,MAX_NODES>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_NETWORK_DFS_POSTORDER_NODES_HPP
