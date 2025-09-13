#ifndef NMTOOLS_NETWORK_REMOVE_NODE_HPP
#define NMTOOLS_NETWORK_REMOVE_NODE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/index_of.hpp"

namespace nmtools::tag
{
    struct remove_node_t {};
    struct remove_node_attributes_t {};
    struct remove_node_id_t {};
}

namespace nmtools::network
{
    // remove node, also remove any edge from/to that node
    template <typename adjacency_list_t, typename node_idx_t>
    constexpr auto remove_node(const adjacency_list_t& adj_list, node_idx_t node_idx)
    {
        if constexpr (meta::is_maybe_v<node_idx_t>
            || meta::is_maybe_v<adjacency_list_t>
        ) {
            using result_t = decltype(remove_node(unwrap(adj_list),unwrap(node_idx)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adj_list) && has_value(node_idx)
                ? return_t{remove_node(unwrap(adj_list),unwrap(node_idx))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::remove_node_t,adjacency_list_t,node_idx_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_adjacency_list_v<result_t>
            ) {
                auto num_nodes = len(adj_list);

                using inner_t = meta::get_value_type_t<result_t>;

                auto to_dst_node_idx = [&](auto i){
                    return ((nm_index_t)i > (nm_index_t)node_idx ? (i - 1) : i);
                };

                // assume node_idx < num_nodes
                // TODO: error handling
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(num_nodes-1);
                }

                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    if (i == (nm_size_t)node_idx) {
                        continue;
                    }
                    auto dst_i = to_dst_node_idx(i);
                    auto dst_neighbors = inner_t{};

                    const auto& src_neighbors = at(adj_list,i);

                    // assume has push_back
                    for (nm_size_t j=0; j<(nm_size_t)len(src_neighbors); j++) {
                        auto neighbor = at(src_neighbors,j);
                        if ((nm_size_t)neighbor == (nm_size_t)node_idx) {
                            continue;
                        }
                        auto dst_neighbor = to_dst_node_idx(neighbor);
                        dst_neighbors.push_back(dst_neighbor);
                    }

                    at(result,dst_i) = dst_neighbors;
                }
            }

            return result;
        }
    }

    template <typename node_ids_t, typename node_idx_t>
    constexpr auto remove_node_id(const node_ids_t& node_ids, node_idx_t node_idx)
    {
        if constexpr (meta::is_maybe_v<node_ids_t>
            || meta::is_maybe_v<node_idx_t>
        ) {
            using result_t = decltype(remove_node_id(unwrap(node_ids),unwrap(node_idx)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(node_ids) && has_value(node_idx)
                ? return_t{remove_node_id(unwrap(node_ids),unwrap(node_idx))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::remove_node_id_t,node_ids_t,node_idx_t>;

            auto result = result_t{};
        
            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_index_array_v<result_t>
            ) {
                auto num_nodes = len(node_ids);

                auto dst_num_nodes = num_nodes-1;
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(dst_num_nodes);
                }

                auto to_dst_node_idx = [&](auto i){
                    return ((nm_index_t)i > (nm_index_t)node_idx ? (i - 1) : i);
                };

                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    if (i == (nm_size_t)node_idx) {
                        continue;
                    }
                    auto dst_idx = to_dst_node_idx(i);

                    at(result,dst_idx) = at(node_ids,i);
                }
            }

            return result;
        }
    }

    template <typename node_attributes_t, typename node_idx_t>
    constexpr auto remove_node_attributes(const node_attributes_t& node_attributes, node_idx_t node_idx)
    {
        if constexpr (meta::is_maybe_v<node_attributes_t>
            || meta::is_maybe_v<node_idx_t>
        ) {
            using result_t = decltype(remove_edge_attributes(unwrap(node_attributes),unwrap(node_idx)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(node_attributes) && has_value(node_idx)
                ? return_t{remove_edge_attributes(unwrap(node_attributes),unwrap(node_idx))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::remove_node_attributes_t,node_attributes_t,node_idx_t>;

            auto result = result_t {};

            if constexpr (
                !meta::is_fail_v<result_t>
                && !is_none_v<result_t>
            ) {
                auto num_nodes = len(node_attributes);

                auto dst_num_nodes = num_nodes - 1;
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(dst_num_nodes);
                }

                auto to_dst_node_idx = [&](auto i){
                    return ((nm_index_t)i > (nm_index_t)node_idx ? (i - 1) : i);
                };

                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    if (i == (nm_size_t)node_idx) {
                        continue;
                    }
                    auto dst_idx = to_dst_node_idx(i);
                    at(result,dst_idx) = at(node_attributes,i);
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
        struct REMOVE_NODE_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct REMOVE_NODE_ID_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct REMOVE_NODE_ATTRIBUTES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t, typename node_idx_t>
    struct resolve_optype<
        void, tag::remove_node_t, adjacency_list_t, node_idx_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (
                !is_adjacency_list_v<adjacency_list_t>
                || !is_index_v<node_idx_t>
            ) {
                using type = error::REMOVE_NODE_UNSUPPORTED<adjacency_list_t,node_idx_t>;
                return as_value_v<type>;
            } else {
                constexpr auto NUM_NODES = len_v<adjacency_list_t>;
                constexpr auto B_NUM_NODES = max_len_v<adjacency_list_t>;
                if constexpr (NUM_NODES > 0) {
                    // TODO: for multi digraph's adj list, num neighbors maybe >>> num_nodes
                    using inner_t = nmtools_static_vector<nm_index_t,NUM_NODES-1>;
                    using outer_t = nmtools_array<inner_t,NUM_NODES-1>;
                    return as_value_v<outer_t>;
                } else if constexpr (B_NUM_NODES > 0) {
                    // TODO: for multi digraph's adj list, num neighbors maybe >>> num_nodes
                    using inner_t = nmtools_static_vector<nm_index_t,B_NUM_NODES-1>;
                    using outer_t = nmtools_static_vector<inner_t,B_NUM_NODES-1>;
                    return as_value_v<outer_t>;
                } else {
                    using inner_t = nmtools_list<nm_index_t>;
                    using outer_t = nmtools_list<inner_t>;
                    return as_value_v<outer_t>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename node_ids_t, typename node_idx_t>
    struct resolve_optype<
        void, tag::remove_node_id_t, node_ids_t, node_idx_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (
                !(is_index_array_v<node_ids_t> || is_none_v<node_ids_t>)
                || !is_index_v<node_idx_t>
            ) {
                using type = error::REMOVE_NODE_ID_UNSUPPORTED<node_ids_t,node_idx_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<node_ids_t>
                && is_constant_index_v<node_idx_t>
            ) {
                constexpr auto node_ids = to_value_v<node_ids_t>;
                constexpr auto node_idx = to_value_v<node_idx_t>;
                constexpr auto result = unwrap(network::remove_node_id(node_ids,node_idx));
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_none_v<node_ids_t>) {
                using type = none_t;
                return as_value_v<type>;
            } else {
                constexpr auto NUM_NODES = len_v<node_ids_t>;
                constexpr auto B_NUM_NODES = max_len_v<node_ids_t>;
                if constexpr (NUM_NODES > 0) {
                    using type = nmtools_array<nm_index_t,NUM_NODES-1>;
                    return as_value_v<type>;
                } else if constexpr (B_NUM_NODES > 0) {
                    using type = nmtools_static_vector<nm_index_t,B_NUM_NODES-1>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<nm_index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename node_attributes_t, typename node_idx_t>
    struct resolve_optype<
        void, tag::remove_node_attributes_t, node_attributes_t, node_idx_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (
                !(has_value_type_v<node_attributes_t> || is_none_v<node_attributes_t>)
                || !is_index_v<node_idx_t>
            ) {
                using type = error::REMOVE_NODE_ATTRIBUTES_UNSUPPORTED<node_attributes_t,node_idx_t>;
                return as_value_v<type>;
            } else if constexpr (is_none_v<node_attributes_t>) {
                using type = none_t;
                return as_value_v<type>;
            } else {
                constexpr auto NUM_NODES = len_v<node_attributes_t>;
                constexpr auto B_NUM_NODES = max_len_v<node_attributes_t>;

                using value_t = get_value_type_t<node_attributes_t>;
                if constexpr (NUM_NODES > 0) {
                    using type = nmtools_array<value_t,NUM_NODES-1>;
                    return as_value_v<type>;
                } else if constexpr (B_NUM_NODES > 0) {
                    using type = nmtools_static_vector<value_t,B_NUM_NODES-1>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<value_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_NETWORK_REMOVE_NODE_HPP