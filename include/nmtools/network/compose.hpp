#ifndef NMTOOLS_NETWORK_COMPOSE_HPP
#define NMTOOLS_NETWORK_COMPOSE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/index_of.hpp"

namespace nmtools::tag
{
    struct compose_t {};
    struct compose_node_attributes_t {};
    struct compose_node_ids_t {};
}

namespace nmtools::network
{
    template <typename g_adj_list_t, typename h_adj_list_t, typename g_map_id_t, typename h_map_id_t>
    constexpr auto compose(const g_adj_list_t& g_adj_list
        , const h_adj_list_t& h_adj_list
        , const g_map_id_t& g_map_id
        , const h_map_id_t& h_map_id)
    {
        if constexpr (meta::is_maybe_v<g_adj_list_t>
            || meta::is_maybe_v<h_adj_list_t>
            || meta::is_maybe_v<g_map_id_t>
            || meta::is_maybe_v<h_map_id_t>
        ) {
            using result_t = decltype(compose(
                unwrap(g_adj_list)
                , unwrap(h_adj_list)
                , unwrap(g_map_id)
                , unwrap(h_map_id))
            );
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(g_adj_list) && has_value(h_adj_list) && has_value(g_map_id) && has_value(h_map_id)
                ? return_t{compose(
                    unwrap(g_adj_list)
                    , unwrap(h_adj_list)
                    , unwrap(g_map_id)
                    , unwrap(h_map_id))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_pair_t = meta::resolve_optype_t<tag::compose_t,g_adj_list_t,h_adj_list_t,g_map_id_t,h_map_id_t>;
            using result_t = meta::at_t<result_pair_t,0>;
            using result_map_id_t = meta::at_t<result_pair_t,1>;

            auto result_map_id = result_map_id_t {};
            auto result = result_t {};

            if constexpr (!meta::is_constant_index_array_v<result_map_id_t>
                && !meta::is_constant_adjacency_list_v<result_t>
                && !meta::is_fail_v<result_map_id_t>
                && !meta::is_fail_v<result_t>
            ) {
                // assume result & result_map_id has push_back
                using neighbors_t = typename result_t::value_type;

                auto h_num_nodes = len(h_adj_list);
                auto g_num_nodes = len(g_adj_list);

                // creat result_map_id first
                for (nm_size_t i=0; i<(nm_size_t)g_num_nodes; i++) {
                    auto node_id = at(g_map_id,i);
                    result_map_id.push_back(node_id);
                }
                for (nm_size_t j=0; j<(nm_size_t)h_num_nodes; j++) {
                    auto node_id = at(h_map_id,j);
                    if (index::index_of(result_map_id,node_id)) {
                        continue;
                    }
                    result_map_id.push_back(node_id);
                }
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(len(result_map_id));
                }

                for (nm_size_t i=0; i<(nm_size_t)g_num_nodes; i++) {
                    const auto& src_neighbors = at(g_adj_list,i);
                    auto num_neighbors = len(src_neighbors);
                    auto dst_neighbors = neighbors_t{};
                    if constexpr (meta::is_resizable_v<neighbors_t>) {
                        dst_neighbors.resize(num_neighbors);
                    }
                    for (nm_size_t j=0; j<(nm_size_t)num_neighbors; j++) {
                        at(dst_neighbors,j) = at(src_neighbors,j);
                    }
                    auto node_id = at(g_map_id,i);
                    auto idx = unwrap(index::index_of(result_map_id,node_id));
                    at(result,idx) = dst_neighbors;
                }
                [[maybe_unused]]
                auto offset = len(result);
                for (nm_size_t i=0; i<(nm_size_t)h_num_nodes; i++) {
                    const auto& src_neighbors = at(h_adj_list,i);
                    auto num_neighbors = len(src_neighbors);
                    auto node_id = at(h_map_id,i);
                    auto idx = unwrap(index::index_of(result_map_id,node_id));
                    for (nm_size_t j=0; j<(nm_size_t)num_neighbors; j++) {
                        auto src_neighbor = at(src_neighbors,j);
                        auto src_id  = at(h_map_id,src_neighbor);
                        auto src_idx = index::index_of(result_map_id,src_id);
                        auto has_src = index::index_of(at(result,idx),src_idx);
                        if (!has_value(has_src)) {
                            at(result,idx).push_back(unwrap(src_idx));
                        }
                    }
                }
                return nmtools_tuple{result,result_map_id};
            } else {
                return nmtools_tuple{result,result_map_id};
            }
        }
    }

    template <typename g_node_attributes_t, typename h_node_attributes_t>
    constexpr auto compose_node_attributes(const g_node_attributes_t& g_node_attributes, const h_node_attributes_t& h_node_attributes)
    {
        if constexpr (meta::is_maybe_v<g_node_attributes_t> || meta::is_maybe_v<h_node_attributes_t>) {
            using result_t = decltype(compose_node_attributes(unwrap(g_node_attributes),unwrap(h_node_attributes)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(g_node_attributes) && has_value(h_node_attributes)
                ? return_t{compose_node_attributes(unwrap(g_node_attributes),unwrap(h_node_attributes))}
                : return_t{meta::Nothing}
            );
        } else if constexpr (is_none_v<g_node_attributes_t> && is_none_v<h_node_attributes_t>) {
            return None;
        } else if constexpr (meta::is_tuple_v<g_node_attributes_t> && meta::is_tuple_v<h_node_attributes_t>) {
            return utility::tuple_cat(g_node_attributes,h_node_attributes);
        } else {
            using result_t = meta::resolve_optype_t<tag::compose_node_attributes_t,g_node_attributes_t,h_node_attributes_t>;
            
            auto result = result_t {};

            auto g_num_nodes = len(g_node_attributes);
            auto h_num_nodes = len(h_node_attributes);
            auto dst_num_nodes = g_num_nodes + h_num_nodes;
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dst_num_nodes);
            }
            for (nm_size_t i=0; i<(nm_size_t)g_num_nodes; i++) {
                at(result,i) = at(g_node_attributes,i);
            }
            for (nm_size_t i=0; i<(nm_size_t)h_num_nodes; i++) {
                at(result,i+g_num_nodes) = at(h_node_attributes,i);
            }

            return result;
        }
    }

    template <typename g_node_ids_t, typename h_node_ids_t>
    constexpr auto compose_node_ids(const g_node_ids_t& g_node_ids, const h_node_ids_t& h_node_ids)
    {
        if constexpr (meta::is_maybe_v<g_node_ids_t>
            || meta::is_maybe_v<h_node_ids_t>
        ) {
            using result_t = decltype(compose_node_ids(unwrap(g_node_ids),unwrap(h_node_ids)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(g_node_ids) && has_value(h_node_ids)
                ? return_t{compose_node_ids(unwrap(g_node_ids),unwrap(h_node_ids))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::compose_node_ids_t,g_node_ids_t,h_node_ids_t>;
            
            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_index_array_v<result_t>
            ) {
                auto g_num_nodes = len(g_node_ids);
                auto h_num_nodes = len(h_node_ids);
                auto dst_num_nodes = g_num_nodes + h_num_nodes;
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(dst_num_nodes);
                }

                for (nm_size_t i=0; i<(nm_size_t)g_num_nodes; i++) {
                    at(result,i) = at(g_node_ids,i);
                }
                for (nm_size_t i=0; i<(nm_size_t)h_num_nodes; i++) {
                    at(result,i+g_num_nodes) = at(h_node_ids,i);
                }
            }

            return result;
        }
    }
} // nmtools::network

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct COMPOSE_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct COMPOSE_NODE_ATTRIBUTES_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct COMPOSE_NODE_IDS_UNSUPPORTED : detail::fail_t {};
    }

    template <typename g_adj_list_t, typename h_adj_list_t, typename g_map_id_t, typename h_map_id_t>
    struct resolve_optype<
        void, tag::compose_t, g_adj_list_t, h_adj_list_t, g_map_id_t, h_map_id_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<g_map_id_t>
                || !is_index_array_v<h_map_id_t>
                || !is_adjacency_list_v<g_adj_list_t>
                || !is_adjacency_list_v<h_adj_list_t>
            ) {
                using type = error::COMPOSE_UNSUPPORTED<g_adj_list_t,h_adj_list_t,g_map_id_t,h_map_id_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<g_map_id_t>
                && is_constant_index_array_v<h_map_id_t>
                && is_constant_adjacency_list_v<g_adj_list_t>
                && is_constant_adjacency_list_v<h_adj_list_t>
            ) {
                constexpr auto g_map_id = to_value_v<g_map_id_t>;
                constexpr auto h_map_id = to_value_v<h_map_id_t>;
                constexpr auto g_adj_list  = to_value_v<g_adj_list_t>;
                constexpr auto h_adj_list  = to_value_v<h_adj_list_t>;
                constexpr auto result_pair = network::compose(g_adj_list,h_adj_list,g_map_id,h_map_id);

                using nmtools::at, nmtools::len;
                constexpr auto result = nmtools::get<0>(result_pair);
                constexpr auto result_map_id = nmtools::get<1>(result_pair);
                auto result_vtype = template_reduce<len(result)>([&](auto init, auto index){
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
                auto result_map_id_vtype = template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    using type = append_type_t<init_t,ct<at(result_map_id,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
                using result_t = type_t<decltype(result_vtype)>;
                using result_map_id_t = type_t<decltype(result_map_id_vtype)>;
                using type = nmtools_tuple<result_t,result_map_id_t>;
                return as_value_v<type>;
            } else {
                using index_t = nm_index_t;
                constexpr auto G_B_NUM_NODES = max_len_v<g_adj_list_t>;
                constexpr auto H_B_NUM_NODES = max_len_v<h_adj_list_t>;
                if constexpr ((G_B_NUM_NODES >= 0) && (H_B_NUM_NODES >= 0)) {
                    constexpr auto B_NUM_NODES = G_B_NUM_NODES + H_B_NUM_NODES;
                    using index_map_t = nmtools_static_vector<index_t,B_NUM_NODES>;
                    using inner_t = nmtools_static_vector<index_t,B_NUM_NODES>;
                    using outer_t = nmtools_static_vector<inner_t,B_NUM_NODES>;
                    using type = nmtools_tuple<outer_t,index_map_t>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using index_map_t = nmtools_list<index_t>;
                    using inner_t = nmtools_list<index_t>;
                    using outer_t = nmtools_list<inner_t>;
                    using type = nmtools_tuple<outer_t,index_map_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename g_node_attributes_t, typename h_node_attributes_t>
    struct resolve_optype<
        void, tag::compose_node_attributes_t, g_node_attributes_t, h_node_attributes_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!has_value_type_v<g_node_attributes_t>
                || !has_value_type_v<h_node_attributes_t>
            ) {
                using type = error::COMPOSE_NODE_ATTRIBUTES_UNSUPPORTED<g_node_attributes_t,h_node_attributes_t>;
                return as_value_v<type>;
            } else {
                using g_value_t = get_value_type_t<g_node_attributes_t>;
                using h_value_t = get_value_type_t<h_node_attributes_t>;
            
                using value_type = g_value_t;

                static_assert( is_same_v<g_value_t,h_value_t> && !is_fail_v<g_value_t>
                    , "invalid type for G's or H's node attributes" );

                constexpr auto B_NUM_G_NODES = max_len_v<g_node_attributes_t>;
                constexpr auto B_NUM_H_NODES = max_len_v<h_node_attributes_t>;
                if constexpr ((B_NUM_G_NODES >= 0) && (B_NUM_H_NODES >= 0)) {
                    using type = nmtools_static_vector<value_type,B_NUM_G_NODES+B_NUM_H_NODES>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<value_type>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename g_node_ids_t, typename h_node_ids_t>
    struct resolve_optype<
        void, tag::compose_node_ids_t, g_node_ids_t, h_node_ids_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<g_node_ids_t>
                || !is_index_array_v<h_node_ids_t>
            ) {
                using type = error::COMPOSE_NODE_IDS_UNSUPPORTED<g_node_ids_t,h_node_ids_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<g_node_ids_t>
                && is_constant_index_array_v<h_node_ids_t>
            ) {
                constexpr auto g_node_ids = to_value_v<g_node_ids_t>;
                constexpr auto h_node_ids = to_value_v<h_node_ids_t>;
                constexpr auto result = unwrap(network::compose_node_ids(g_node_ids,h_node_ids));
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                using index_t = nm_size_t;
                constexpr auto B_NUM_G_NODES = max_len_v<g_node_ids_t>;
                constexpr auto B_NUM_H_NODES = max_len_v<h_node_ids_t>;
                if constexpr ((B_NUM_G_NODES >= 0) && (B_NUM_H_NODES >= 0)) {
                    using type = nmtools_static_vector<index_t,B_NUM_G_NODES+B_NUM_H_NODES>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_NETWORK_COMPOSE_HPP