#ifndef NMTOOLS_NETWORK_GREEDY_COLOR_HPP
#define NMTOOLS_NETWORK_GREEDY_COLOR_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/network/degree.hpp"
#include "nmtools/network/is_undirected.hpp"
#include "nmtools/index/compute_offset.hpp"
#include "nmtools/index/compute_strides.hpp"

namespace nmtools::tag
{
    struct greedy_color_t {};
}

namespace nmtools::network
{
    // Greedy graph coloring with the DSATUR strategy, matching networkx
    // greedy_color(G, strategy="DSATUR") on undirected graphs.
    template <typename adjacency_list_t>
    constexpr auto greedy_color(const adjacency_list_t& adj_list)
    {
        if constexpr (is_maybe_v<adjacency_list_t>) {
            using result_t = decltype(greedy_color(unwrap(adj_list)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adj_list)
                ? return_t{greedy_color(unwrap(adj_list))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = resolve_optype_t<tag::greedy_color_t,adjacency_list_t>;

            if constexpr (!is_fail_v<result_t>
                && !is_constant_index_array_v<result_t>
            ) {
                // demote constant structures so they can be indexed at runtime
                decltype(auto) adj = [&]() -> decltype(auto) {
                    if constexpr (is_constant_adjacency_list_v<adjacency_list_t>) {
                        return to_value_v<adjacency_list_t>;
                    } else {
                        return (adj_list);
                    }
                }();
                using return_t = nmtools_maybe<result_t>;

                auto num_nodes = len(adj);

                auto result = result_t {};
                if constexpr (is_resizable_v<result_t>) {
                    result.resize(num_nodes);
                }
                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    at(result,i) = 0;
                }

                auto m_deg = degree(adj);

                // networkx silently produces a wrong coloring for directed
                // input; refuse it instead. An undirected list cannot hold a
                // dangling target, so no further bounds checks are needed.
                auto valid = has_value(m_deg) && is_undirected(adj);
                if (!valid) {
                    return return_t{meta::Nothing};
                }
                auto deg = unwrap(m_deg);

                using degree_t    = decltype(deg);
                using color_t     = replace_value_type_t<degree_t,nm_index_t>;
                auto matrix_vtype = [](){
                    using bool_t = nm_bool_t;
                    [[maybe_unused]]
                    constexpr auto MAX_NODES = max_len_v<adjacency_list_t>;
                    constexpr auto NUM_NODES = len_v<adjacency_list_t>;
                    if constexpr (NUM_NODES > 0) {
                        using type = nmtools_array<bool_t,NUM_NODES*NUM_NODES>;
                        return as_value_v<type>;
                    } else if constexpr (MAX_NODES >= 0) {
                        using type = nmtools_static_vector<bool_t,MAX_NODES*MAX_NODES>;
                        return as_value_v<type>;
                    } else {
                        // TODO: use small vector
                        using type = nmtools_list<bool_t>;
                        return as_value_v<type>;
                    }
                }();
                using matrix_t = type_t<decltype(matrix_vtype)>;
                auto m_shape   = nmtools_array{num_nodes,num_nodes};
                auto m_stride  = index::compute_strides(m_shape);
                auto offset    = [&](auto i, auto j){
                    return index::compute_offset(nmtools_array{i,j},m_shape,m_stride);
                };

                auto sat   = degree_t {};
                auto color = color_t {};
                auto seen  = matrix_t {};

                if constexpr (is_resizable_v<degree_t>) {
                    sat.resize(num_nodes);
                }
                if constexpr (is_resizable_v<color_t>) {
                    color.resize(num_nodes);
                }
                if constexpr (is_resizable_v<matrix_t>) {
                    seen.resize(num_nodes*num_nodes);
                }

                for (auto& s : sat) {
                    s = 0;
                }
                for (auto& c : color) {
                    c = -1; // UNCOLORED
                }
                for (auto& s : seen) {
                    s = false;
                }

                auto remaining = (nm_index_t)num_nodes;

                auto assign = [&](auto u) {
                    if (u < 0) {
                        return;
                    }
                    auto c = 0;
                    while (seen[offset(u,c)]) {
                        c++;
                    }
                    color[u] = c;
                    remaining -= 1;

                    for (const auto& v : adj[u]) {
                        if ((v != u) && (color[v] == -1) && !seen[offset(v,c)]) {
                            seen[offset(v,c)] = true;
                            sat[v] += 1;
                        }
                    }
                };

                while (remaining > 0) {
                    // argmax of the (saturation, degree) tuple over uncolored
                    // nodes, compared lexicographically like networkx max().
                    // Scanning ascending means the lowest index wins ties. In
                    // the first round every saturation is zero, so this also
                    // covers the initial highest degree pick.
                    auto best = (nm_index_t)-1;
                    for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                        if ((color[i] == -1)
                            && ((best < 0)
                                || (sat[i] > sat[best])
                                || ((sat[i] == sat[best]) && (deg[i] > deg[best]))
                            )
                        ) {
                            best = i;
                        }
                    }
                    assign(best);
                }

                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    result[i] = color[i];
                }

                return valid ? return_t{result} : return_t{meta::Nothing};
            } else {
                auto result = result_t {};
                return result;
            }
        }
    } // greedy_color
} // namespace nmtools::network

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct GREEDY_COLOR_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct GREEDY_COLOR_DIRECTED : detail::fail_t {};
    }

    template <typename adjacency_list_t>
    struct resolve_optype<
        void, tag::greedy_color_t, adjacency_list_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>) {
                using type = error::GREEDY_COLOR_UNSUPPORTED<adjacency_list_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_adjacency_list_v<adjacency_list_t>) {
                constexpr auto adj_list = to_value_v<adjacency_list_t>;
                if constexpr (!network::is_undirected(adj_list)) {
                    // NOTE: follows the TO_UNDIRECTED_INVALID decision; a graph
                    // that cannot be colored is a compile time error, not a value
                    using type = error::GREEDY_COLOR_DIRECTED<adjacency_list_t>;
                    return as_value_v<type>;
                } else {
                    constexpr auto m_result = network::greedy_color(adj_list);
                    if constexpr (has_value(m_result)) {
                        constexpr auto result = unwrap(m_result);
                        using nmtools::at, nmtools::len;
                        return template_reduce<len(result)>([&](auto init, auto index){
                            using init_t = type_t<decltype(init)>;
                            constexpr auto I = decltype(index)::value;
                            using type = append_type_t<init_t,ct<at(result,I)>>;
                            return as_value_v<type>;
                        }, as_value_v<nmtools_tuple<>>);
                    } else {
                        using type = error::GREEDY_COLOR_DIRECTED<adjacency_list_t>;
                        return as_value_v<type>;
                    }
                }
            } else {
                constexpr auto NUM_NODES = len_v<adjacency_list_t>;
                [[maybe_unused]]
                constexpr auto B_NUM_NODES = max_len_v<adjacency_list_t>;
                if constexpr (NUM_NODES >= 0) {
                    using type = nmtools_array<nm_size_t,NUM_NODES>;
                    return as_value_v<type>;
                } else if constexpr (B_NUM_NODES >= 0) {
                    using type = nmtools_static_vector<nm_size_t,B_NUM_NODES>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // tag::greedy_color_t
} // namespace nmtools::meta

#endif // NMTOOLS_NETWORK_GREEDY_COLOR_HPP
