#ifndef NMTOOLS_NETWORK_NUMBER_OF_EDGES_HPP
#define NMTOOLS_NETWORK_NUMBER_OF_EDGES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"

namespace nmtools::tag
{
    struct number_of_edges_t {};
}

namespace nmtools::network
{
    template <typename adjacency_list_t, typename from_t=none_t, typename to_t=none_t>
    constexpr auto number_of_edges(const adjacency_list_t& adj_list, from_t from=from_t{}, to_t to=to_t{})
    {
        if constexpr (meta::is_maybe_v<to_t>
            || meta::is_maybe_v<from_t>
            || meta::is_maybe_v<adjacency_list_t>
        ) {
            using result_t = decltype(number_of_edges(unwrap(adj_list),unwrap(from),unwrap(to)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adj_list) && has_value(from) && has_value(to)
                ? return_t{number_of_edges(unwrap(adj_list),unwrap(from),unwrap(to))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::number_of_edges_t,adjacency_list_t,from_t,to_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_index_v<result_t>
            ) {
                auto num_nodes = len(adj_list);

                if constexpr (is_none_v<from_t> && is_none_v<to_t>) {
                    for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                        result += len(at(adj_list,i));
                    }
                } else {
                    const auto& neighbor_edges = at(adj_list,from);
                    auto num_edges = len(neighbor_edges);
                    for (nm_size_t i=0; i<(nm_size_t)num_edges; i++) {
                        auto edge = at(num_edges,i);
                        if ((nm_index_t)edge == (nm_index_t)to) {
                            result += 1;
                        }
                    }
                }
            }

            return result;
        }
    } // number_of_edges
}

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct NUMBER_OF_EDGES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t, typename from_t, typename to_t>
    struct resolve_optype<
        void, tag::number_of_edges_t, adjacency_list_t, from_t, to_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>
                || !(is_index_v<from_t> || is_none_v<from_t>)
                || !(is_index_v<to_t> || is_none_v<to_t>)
            ) {
                using type = error::NUMBER_OF_EDGES_UNSUPPORTED<adjacency_list_t,from_t,to_t>;
                return as_value_v<type>;
            } else if constexpr ((is_constant_index_v<to_t> || is_none_v<to_t>)
                && (is_constant_index_v<from_t> || is_none_v<from_t>)
                && is_constant_adjacency_list_v<adjacency_list_t>
            ) {
                constexpr auto adj_list = to_value_v<adjacency_list_t>;
                constexpr auto from     = to_value_v<from_t>;
                constexpr auto to       = to_value_v<to_t>;
                constexpr auto result   = unwrap(network::number_of_edges(adj_list,from,to));
                return as_value_v<ct<result>>;
            } else {
                using type = nm_size_t;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_NETWORK_NUMBER_OF_EDGES_HPP