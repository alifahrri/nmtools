#ifndef NMTOOLS_NETWORK_DIGRAPH_HPP
#define NMTOOLS_NETWORK_DIGRAPH_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/contains.hpp"
#include "nmtools/index/index_of.hpp"
#include "nmtools/network/add_edge.hpp"
#include "nmtools/network/compose.hpp"
#include "nmtools/network/filter_nodes.hpp"
#include "nmtools/network/is_directed_acyclic_graph.hpp"
#include "nmtools/network/out_edges.hpp"
#include "nmtools/network/topological_generations.hpp"
#include "nmtools/network/topological_sort.hpp"
#include "nmtools/network/map_ids.hpp"

// given a constexpr result, convert it to type
#define nmtools_adjacency_list_vtype(result) \
meta::template_reduce<len(result)>([&](auto init, auto index){ \
    using nmtools::len, nmtools::at; \
    constexpr auto I = decltype(index)::value; \
    using init_t = meta::type_t<decltype(init)>; \
    constexpr auto neighbors = at(result,I); \
    constexpr auto NUM_NEIGHBORS = len(neighbors); \
    constexpr auto neighbors_vtype = meta::template_reduce<NUM_NEIGHBORS>([neighbors](auto init, auto index){ \
        constexpr auto J = decltype(index)::value; \
        using init_t = meta::type_t<decltype(init)>; \
        using neighbor_t = meta::ct<at(neighbors,J)>; \
        using type = meta::append_type_t<init_t,neighbor_t>; \
        return meta::as_value_v<type>; \
    }, meta::as_value_v<nmtools_tuple<>>); \
    using neighbors_t = meta::type_t<decltype(neighbors_vtype)>; \
    using type = meta::append_type_t<init_t,neighbors_t>; \
    return meta::as_value_v<type>; \
}, meta::as_value_v<nmtools_tuple<>>)

namespace nmtools::network
{
    struct generate_node_ids_t {};

    template <typename adjacency_list_t>
    constexpr auto generate_node_ids(const adjacency_list_t& adj_list)
    {
        using result_t = meta::resolve_optype_t<generate_node_ids_t,adjacency_list_t>;

        auto result = result_t {};

        if constexpr (!meta::is_fail_v<result_t>
            && !meta::is_constant_index_array_v<result_t>
        ) {
            auto num_nodes = len(adj_list);
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(num_nodes);
            }

            for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                at(result,i) = i;
            }
        }

        return result;
    }

    template <typename edge_attributes_t=none_t
        , typename node_attributes_t=none_t
        , typename node_ids_t=none_t
        , typename adjacency_list_t=none_t>
    constexpr auto digraph([[maybe_unused]] const adjacency_list_t& adj_list=adjacency_list_t{}
        , const node_ids_t& node_ids=node_ids_t{}
        , [[maybe_unused]] const node_attributes_t& node_attributes=node_attributes_t{}
        , [[maybe_unused]] const edge_attributes_t& edge_attributes=edge_attributes_t{}
    );

    template <typename adjacency_list_t
        , typename node_ids_t=none_t
        , typename node_attributes_t=none_t
        , typename edge_attributes_t=none_t>
    struct digraph_t
    {
        // TODO: check with node_attributes_t which one has bounded size
        using adjacency_list_type = adjacency_list_t;
        // store mapping from node key/id to index in adjacency_list
        using node_ids_type = node_ids_t;

        static constexpr auto node_attributes_vtype = [](){
            if constexpr (is_none_v<node_attributes_t> || meta::is_tuple_v<node_attributes_t>) {
                using type = node_attributes_t;
                return meta::as_value_v<type>;
            } else if constexpr (meta::is_vtype_v<node_attributes_t>) {
                using attribute_t = meta::type_t<node_attributes_t>;
                constexpr auto NUM_NODES = meta::len_v<adjacency_list_type>;
                [[maybe_unused]]
                constexpr auto B_NUM_NODES = meta::max_len_v<adjacency_list_type>;
                if constexpr (NUM_NODES >= 0) {
                    using type = nmtools_array<attribute_t,NUM_NODES>;
                    return meta::as_value_v<type>;
                } else if constexpr (B_NUM_NODES >= 0) {
                    using type = nmtools_static_vector<attribute_t,B_NUM_NODES>;
                    return meta::as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<attribute_t>;
                    return meta::as_value_v<type>;
                }
            } else {
                using type = node_attributes_t;
                return meta::as_value_v<type>;
            }
        }();
        // TODO: check with adjacency_list which one has bounded size
        using node_attributes_type = meta::type_t<decltype(node_attributes_vtype)>;

        static constexpr auto edge_attributes_vtype = [](){
            if constexpr (is_none_v<edge_attributes_t> || meta::is_tuple_v<edge_attributes_t>) {
                using type = edge_attributes_t;
                return meta::as_value_v<type>;
            } else if constexpr (meta::is_vtype_v<edge_attributes_t>) {
                using attribute_t = meta::type_t<edge_attributes_t>;
                constexpr auto NUM_NODES = meta::len_v<adjacency_list_type>;
                [[maybe_unused]]
                constexpr auto B_NUM_NODES = meta::max_len_v<adjacency_list_type>;
                // The structure of edge attributes is similar to adjacency list (instead of like node attributes)
                if constexpr (NUM_NODES >= 0) {
                    using inner_t = nmtools_static_vector<attribute_t,NUM_NODES>;
                    using outer_t = nmtools_array<inner_t,NUM_NODES>;
                    using type = outer_t;
                    return meta::as_value_v<type>;
                } else if constexpr (B_NUM_NODES >= 0) {
                    using inner_t = nmtools_static_vector<attribute_t,B_NUM_NODES>;
                    using outer_t = nmtools_static_vector<inner_t,B_NUM_NODES>;
                    using type = outer_t;
                    return meta::as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using inner_t = nmtools_list<attribute_t>;
                    using outer_t = nmtools_list<inner_t>;
                    using type = outer_t;
                    return meta::as_value_v<type>;
                }
            } else {
                // assume a container like adjacency list
                using type = edge_attributes_t;
                return meta::as_value_v<type>;
            }
        }();
        using edge_attributes_type = meta::type_t<decltype(edge_attributes_vtype)>;

        static constexpr auto node_attribute_vtype = [](){
            if constexpr (is_none_v<node_attributes_type> || meta::is_tuple_v<node_attributes_type>) {
                // TODO: what should be attribute_type when node_attributes_t is tuple?
                // indicates that no specific types or no attribute at all
                using type = none_t;
                return meta::as_value_v<type>;
            } else {
                using type = typename node_attributes_type::value_type;
                return meta::as_value_v<type>;
            }
        }();
        using node_attribute_type = meta::type_t<decltype(node_attribute_vtype)>;

        static constexpr auto edge_attribute_vtype = [](){
            if constexpr (is_none_v<edge_attributes_type> || meta::is_tuple_v<edge_attributes_type>) {
                // TODO: what should be attribute_type when node_attributes_t is tuple?
                using type = edge_attributes_type;
                return meta::as_value_v<type>;
            } else {
                using inner_t = meta::get_value_type_t<edge_attributes_type>;
                using value_t = meta::get_value_type_t<inner_t>;
                return meta::as_value_v<value_t>;
            }
        }();
        using edge_attribute_type = meta::type_t<decltype(edge_attribute_vtype)>;


        // TODO: support None node_ids, for smaller memory footprint
        adjacency_list_type  adjacency_list;
        node_ids_type        node_ids;
        node_attributes_type node_attributes;
        edge_attributes_type edge_attributes;

        constexpr digraph_t() {}

        constexpr digraph_t(const adjacency_list_t& adjacency_list
            , const node_ids_t& node_ids=node_ids_t{}
            , const node_attributes_t& node_attributes=node_attributes_t{}
            , const edge_attributes_t& edge_attributes=edge_attributes_t{}
        )
            : adjacency_list(adjacency_list)
            , node_ids(node_ids)
            , node_attributes([&](){
                if constexpr (meta::is_vtype_v<node_attributes_t>) {
                    auto attr = node_attributes_type{};
                    if constexpr (meta::is_resizable_v<node_attribute_type>) {
                        attr.resize(len(adjacency_list));
                    }
                    return attr;
                } else {
                    return node_attributes;
                }
            }())
            , edge_attributes([&](){
                if constexpr (meta::is_vtype_v<edge_attributes_t>) {
                    auto attr = edge_attributes_type{};
                    auto num_nodes = len(adjacency_list);
                    if constexpr (meta::is_resizable_v<edge_attributes_type>) {
                        attr.resize(num_nodes);
                    }
                    // TODO: handle tuple adjacency list
                    for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                        const auto& neighbors = at(adjacency_list,i);
                        auto num_edges = len(neighbors);
                        at(attr,i).resize(num_edges);
                    }
                    return attr;
                } else {
                    return edge_attributes;
                }
            }())
        {}

        // convert constant adjacency list to compile-time value
        template <typename adj_list_t, auto extra_nodes=0, typename m_node_ids_t=none_t>
        static constexpr auto to_value()
        {
            auto src_adj_list = meta::to_value_v<adj_list_t>;
            constexpr auto NUM_NODES = meta::len_v<adj_list_t>;
            using inner_t = nmtools_static_vector<nm_size_t,NUM_NODES+extra_nodes>;
            using outer_t = nmtools_static_vector<inner_t,NUM_NODES+extra_nodes>;
            auto adj_list = outer_t{};
            adj_list.resize(NUM_NODES);
            for (nm_size_t i=0; i<(nm_size_t)NUM_NODES; i++) {
                auto neighbors = at(src_adj_list,i);
                auto num_neighbors = len(neighbors);
                for (nm_size_t j=0; j<(nm_size_t)num_neighbors; j++) {
                    at(adj_list,i).push_back(at(neighbors,j));
                }
            }
            if constexpr (is_none_v<m_node_ids_t>) {
                auto dst_adj_list = digraph(adj_list);
                return dst_adj_list;
            } else {
                auto node_ids = meta::to_value_v<m_node_ids_t>;
                auto dst_adj_list = digraph(adj_list,node_ids);
                return dst_adj_list;
            }
        }

        constexpr auto order() const noexcept
        {
            // TODO: return constant / bounded index whenever possible
            return len(adjacency_list);
        }

        constexpr auto number_of_nodes() const noexcept
        {
            return order();
        }

        constexpr auto size() const noexcept
        {
            // TODO: return constant / bounded index whenever possible
            nm_size_t num_edges = 0;
            if constexpr (meta::is_tuple_v<adjacency_list_type>) {
                constexpr auto N = meta::len_v<adjacency_list_type>;
                meta::template_for<N>([&](auto I){
                    num_edges += len(at(adjacency_list,I));
                });
            } else {
                auto num_nodes = number_of_nodes();
                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    num_edges += len(at(adjacency_list,i));
                }
            }
            return num_edges;
        }

        constexpr auto number_of_edges() const noexcept
        {
            return size();
        }

        template <typename node_id_t>
        constexpr auto has_node([[maybe_unused]] node_id_t node_id) const noexcept
        {
            if constexpr (is_none_v<node_ids_type>
                && meta::is_constant_adjacency_list_v<adjacency_list_type>
                && meta::is_constant_index_v<node_id_t>
            ) {
                constexpr auto NUM_NODES = meta::len_v<adjacency_list_type>;
                constexpr auto NODE_ID   = node_id_t::value;
                constexpr auto HAS_NODE  = ((nm_index_t)NODE_ID < (nm_index_t)NUM_NODES);
                return meta::ct_v<HAS_NODE>;
            } else if constexpr (is_none_v<node_ids_type>) {
                return ((nm_index_t)node_id < (nm_index_t)len(adjacency_list));
            } else {
                return index::contains(node_ids,node_id);
            }
        }

        template <typename id_t>
        constexpr auto get_index([[maybe_unused]] id_t id) const noexcept
        {
            if constexpr (!is_none_v<node_ids_type>) {
                return index::index_of(node_ids,id);
            } else if constexpr (is_none_v<node_ids_type>
                && meta::is_constant_index_v<id_t>
                && meta::is_constant_adjacency_list_v<adjacency_list_type>
            ) {
                constexpr auto ID = id_t::value;
                constexpr auto NUM_NODES = meta::len_v<adjacency_list_type>;
                if constexpr (ID < NUM_NODES) {
                    return meta::ct_v<ID>;
                } else {
                    return meta::detail::fail_t {};
                }
            } else {
                using result_t = nmtools_maybe<nm_index_t>;
                return (((nm_index_t)id < (nm_index_t)len(adjacency_list))
                    ? result_t{id}
                    : result_t{meta::Nothing}
                );
            }
        }

        template <typename from_t, typename to_t>
        constexpr auto has_edge(from_t from, to_t to) const noexcept
        {
            // TODO: handle None node_ids
            auto from_idx = get_index(from);
            auto to_idx   = get_index(to);

            auto has_edge = has_value(from_idx) && has_value(to_idx);
            if (has_edge) {
                // actual edge check
                const auto& neighbors = at(adjacency_list,unwrap(from_idx));
                has_edge &= index::contains(neighbors,unwrap(to_idx));
            }
            return has_edge;
        }

        template <typename node_id_t, typename attribute_t=none_t>
        constexpr decltype(auto) add_node([[maybe_unused]] node_id_t node_id
            , [[maybe_unused]] const attribute_t& attribute=attribute_t{})
        {
            if constexpr (meta::is_constant_index_v<node_id_t> &&
                meta::is_constant_adjacency_list_v<adjacency_list_type>
            ) {
                #if 0
                constexpr auto result = [](){
                    auto dst_adj_list = to_value<adjacency_list_type,1>();
                    auto NODE_ID = node_id_t::value;
                    dst_adj_list.add_node(NODE_ID);
                    return dst_adj_list;
                }();

                auto vtype = nmtools_adjacency_list_vtype(result.adjacency_list);
                using type = meta::type_t<decltype(vtype)>;
                return digraph(type{});
                #else
                auto dst_adj_list = utility::tuple_append(adjacency_list,nmtools_tuple{});
                if constexpr (!is_none_v<node_ids_type> && !is_none_v<attribute_t>) {
                    auto dst_node_ids = utility::tuple_append(node_ids,node_id);
                    auto dst_attributes = utility::tuple_append(node_attributes,attribute);
                    return digraph(dst_adj_list,dst_node_ids,dst_attributes);
                } else if constexpr (is_none_v<node_ids_type> && !is_none_v<attribute_t>) {
                    auto dst_node_ids = None;
                    auto dst_attributes = utility::tuple_append(node_attributes,attribute);
                    return digraph(dst_adj_list,dst_node_ids,dst_attributes);
                } else if constexpr (!is_none_v<node_ids_type> && !is_none_v<attribute_t>) {
                    auto dst_node_ids = utility::tuple_append(node_ids,node_id);
                    auto dst_attributes = None;
                    return digraph(dst_adj_list,dst_node_ids,dst_attributes);
                } else {
                    return digraph(dst_adj_list);
                }
                #endif
            } else {
                auto num_nodes = len(adjacency_list);
                auto dst_num_nodes = num_nodes + 1;
                if (!has_node(node_id)) {
                    if constexpr (!is_none_v<node_ids_type>) {
                        // assume has push_back
                        node_ids.push_back(node_id);
                    }
                    if constexpr (meta::is_resizable_v<adjacency_list_type>) {
                        adjacency_list.resize(dst_num_nodes);
                    }
                    // TODO: check if resized by recheck the node_id & adj_lit size
                    // panic on error
                    if constexpr (meta::is_resizable_v<node_attributes_type>) {
                        node_attributes.resize(dst_num_nodes);
                    }
                    if constexpr (!is_none_v<node_attributes_type>) {
                        if (len(node_attributes) != dst_num_nodes) {
                            nmtools_panic( false
                                , "failed to resize node_attributes"
                            );
                        }
                    }
                }

                if constexpr (!is_none_v<attribute_t>
                    && !is_none_v<node_attribute_type>
                ) {
                    at(node_attributes,-1) = attribute;
                }

                // edge attributes structure is similar to adjacency_list (2D nested container)
                // also resize here, if applicable
                // TODO: what to do with tuple?
                if constexpr (meta::is_resizable_v<edge_attributes_type>) {
                    edge_attributes.resize(dst_num_nodes);
                }

                return *this;
            }
        }

        template <typename from_t, typename to_t, typename attribute_t=edge_attribute_type>
        constexpr decltype(auto) add_edge(from_t from, to_t to
            , [[maybe_unused]] const attribute_t& attribute=attribute_t{})
        {
            if constexpr (meta::is_constant_adjacency_list_v<adjacency_list_type>) {
                #if 0
                constexpr auto result = [](){
                    auto dst_adj_list = to_value<adjacency_list_type,2>();

                    constexpr auto FROM = from_t::value;
                    constexpr auto TO   = to_t::value;
                    dst_adj_list.add_edge(FROM,TO);
                    return dst_adj_list;
                }();

                auto vtype = nmtools_adjacency_list_vtype(result.adjacency_list);
                using type = meta::type_t<decltype(vtype)>;
                return digraph(type{});
                #else
                constexpr auto HAS_FROM = decltype(has_node(from))::value;
                constexpr auto HAS_TO   = decltype(has_node(from))::value;
                auto digraph = [&](){
                    if constexpr (HAS_FROM && HAS_TO) {
                        return *this;
                    } else if constexpr (!HAS_FROM && HAS_TO) {
                        return add_node(from);
                    } else if constexpr (HAS_FROM && !HAS_TO) {
                        return add_node(to);
                    } else {
                        return add_node(from).add_node(to);
                    }
                }();
                using from_idx_t = decltype(get_index(from));
                using to_idx_t   = decltype(get_index(to));
                static_assert( meta::is_constant_index_v<from_idx_t> );
                static_assert( meta::is_constant_index_v<to_idx_t> );
                constexpr auto FROM = from_idx_t::value;
                constexpr auto TO = to_idx_t::value;
                constexpr auto src_adj_list = meta::to_value_v<decltype(digraph.adjacency_list)>;
                constexpr auto dst_adj_list = network::add_edge(src_adj_list,FROM,TO);

                auto vtype = nmtools_adjacency_list_vtype(dst_adj_list);
                using type = meta::type_t<decltype(vtype)>;
                return network::digraph(type{},digraph.node_ids,digraph.node_attributes);
                #endif
            } else {
                if (!has_node(from)) {
                    add_node(from);
                }

                if (!has_node(to)) {
                    add_node(to);
                }
    
                auto from_idx = unwrap(get_index(from));
                auto to_idx   = unwrap(get_index(to));
    
                auto& froms_neighbors = at(adjacency_list,from_idx);
                auto n_neighbors = len(froms_neighbors);
                auto dst_size = n_neighbors + 1;
                using neighbors_t = meta::remove_cvref_t<decltype(froms_neighbors)>;
                if (!index::contains(froms_neighbors,to_idx)) {
                    if constexpr (meta::is_resizable_v<neighbors_t>) {
                        froms_neighbors.resize(dst_size);
                    }
                    // add extra if to make it usable in constant expression
                    if (len(froms_neighbors) != dst_size) {
                        nmtools_panic( false
                            , "can't add more neighbors"
                        );
                    }
                    at(froms_neighbors,n_neighbors) = to_idx;
                }

                if constexpr (!is_none_v<attribute_t>
                    && !is_none_v<edge_attributes_type>
                ) {
                    auto& neighbor_edges = at(edge_attributes,from_idx);
                    if constexpr (meta::is_resizable_v<decltype(neighbor_edges)>) {
                        neighbor_edges.resize(dst_size);
                    }
                    if (len(neighbor_edges) != dst_size) {
                        nmtools_panic( false
                            , "can't add more edge attribute"
                        );
                    }
                    auto edge_idx = unwrap(index::index_of(froms_neighbors,to_idx));
                    at(neighbor_edges,edge_idx) = attribute;
                }
    
                return *this;
            }
        }

        template <typename nodes_t>
        constexpr decltype(auto) add_nodes_from(const nodes_t& nodes)
        {
            if constexpr (meta::is_tuple_v<nodes_t>) {
                constexpr auto N = meta::len_v<nodes_t>;
                meta::template_for<N>([&](auto i){
                    const auto& node = at(nodes,i);
                    add_node(node);
                });
            } else {
                auto n = len(nodes);
                for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                    const auto& node = at(nodes,i);
                    add_node(node);
                }
            }
            return *this;
        }

        template <typename edges_t>
        constexpr decltype(auto) add_edges_from(const edges_t& edges)
        {
            if constexpr (meta::is_constant_adjacency_list_v<adjacency_list_type>) {
                constexpr auto result = [&](){
                    // TODO: handle edges > 1
                    auto dst_digraph = to_value<adjacency_list_type,1>();
                    dst_digraph.add_edges_from(edges);
                    return dst_digraph;
                }();

                auto vtype = nmtools_adjacency_list_vtype(result.adjacency_list);
                using type = meta::type_t<decltype(vtype)>;
                // TODO: also return edges and nodes
                return digraph(type{});
            } else {
                constexpr auto N_PAIRS = meta::len_v<edges_t>;
                auto loop = [&](auto i){
                    const auto& edge = at(edges,i);
                        auto from = at(edge,meta::ct_v<0>);
                    auto to   = at(edge,meta::ct_v<1>);
                    add_edge(from,to);
                };
                if constexpr (N_PAIRS > 0) {
                    meta::template_for<N_PAIRS>([&](auto I){
                        loop(I);
                    });
                } else {
                    auto n_pairs = len(edges);
                    for (nm_size_t i=0; i<(nm_size_t)n_pairs; i++) {
                        loop(i);
                    }
                }
                return *this;
            }
        }

        template <typename node_id_t=none_t>
        constexpr decltype(auto) nodes(node_id_t node_id=node_id_t{}) const
        {
            if constexpr (is_none_v<node_id_t> && !is_none_v<node_ids_type>) {
                return node_ids;
            } else if constexpr (is_none_v<node_id_t>) {
                return generate_node_ids(adjacency_list);
            } else if constexpr (!is_none_v<node_attributes_type>) {
                // TODO: check if node_id is constant index if list is constant adjacency list
                auto idx = get_index(node_id);
                return at(node_attributes,unwrap(idx));
            } else {
                return None;
            }
        }

        template <typename node_id_t>
        constexpr decltype(auto) nodes(node_id_t node_id)
        {
            if constexpr (!is_none_v<node_attributes_type>) {
                // TODO: check if node_id is constant index if list is constant adjacency list
                auto idx = get_index(node_id);
                return at(node_attributes,unwrap(idx));
            } else {
                return None;
            }
        }

        template <typename from_t, typename to_t>
        constexpr decltype(auto) edges(from_t from, to_t to) const
        {
            if constexpr (!is_none_v<edge_attributes_type>) {
                auto from_idx = get_index(from);
                auto to_idx   = get_index(to);

                auto has_edge = has_value(from_idx) && has_value(to_idx);
                if (!has_edge) {
                    nmtools_panic( false
                        , "edge doesn't exists"
                    )
                }
                auto& neighbors = at(adjacency_list,unwrap(from_idx));
                auto edge_idx = index::index_of(neighbors,to_idx);
                auto& edges = at(edge_attributes,unwrap(from_idx));
                return at(edges,unwrap(edge_idx));
            } else {
                return None;
            }
        }

        template <typename from_t, typename to_t>
        constexpr decltype(auto) edges(from_t from, to_t to)
        {
            if constexpr (!is_none_v<edge_attributes_type>) {
                // TODO: handle None node_ids
                auto from_idx = get_index(from);
                auto to_idx   = get_index(to);

                auto has_edge = has_value(from_idx) && has_value(to_idx);
                if (!has_edge) {
                    nmtools_panic( false
                        , "edge doesn't exists"
                    )
                }
                auto& neighbors = at(adjacency_list,unwrap(from_idx));
                auto edge_idx = index::index_of(neighbors,to_idx);
                auto& edges = at(edge_attributes,unwrap(from_idx));
                return at(edges,unwrap(edge_idx));
            } else {
                return None;
            }
        }

        constexpr decltype(auto) out_edges() const noexcept
        {
            // TODO: support nbunch
            if constexpr (meta::is_constant_adjacency_list_v<adjacency_list_type>
                && meta::is_constant_index_array_v<node_ids_type>
            ) {
                constexpr auto result = [](){
                    auto adj_list = to_value<adjacency_list_type,0,node_ids_type>();
                    return adj_list.out_edges();
                }();

                auto vtype = nmtools_adjacency_list_vtype(result);
                using type = meta::type_t<decltype(vtype)>;
                return type{};
            } else {
                auto out_edges = [&](){
                    if constexpr (meta::is_constant_adjacency_list_v<adjacency_list_type>) {
                        constexpr auto adj_list = meta::to_value_v<adjacency_list_type>;
                        return network::out_edges(adj_list);
                    } else {
                        return network::out_edges(adjacency_list);
                    }
                }();
                return network::map_ids(out_edges,node_ids);
            }
        }
    };

    template <typename edge_attributes_t
        , typename node_attributes_t
        , typename node_ids_t
        , typename adjacency_list_t>
    constexpr auto digraph([[maybe_unused]] const adjacency_list_t& adj_list
        , [[maybe_unused]] const node_ids_t& node_ids
        , [[maybe_unused]] const node_attributes_t& node_attributes
        , [[maybe_unused]] const edge_attributes_t& edge_attributes)
    {
        if constexpr (meta::is_maybe_v<adjacency_list_t>
            || meta::is_maybe_v<node_ids_t>
            || meta::is_maybe_v<node_attributes_t>
            || meta::is_maybe_v<edge_attributes_t>
        ) {
            using result_t = decltype(digraph(unwrap(adj_list),unwrap(node_ids),unwrap(node_attributes),unwrap(edge_attributes)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adj_list) && has_value(node_ids) && has_value(node_attributes) && has_value(edge_attributes)
                ? return_t{digraph(unwrap(adj_list),unwrap(node_ids),unwrap(node_attributes),unwrap(edge_attributes))}
                : return_t{meta::Nothing}
            );
        } else if constexpr (is_none_v<adjacency_list_t>) {
            // TODO: use small vector
            using adjacency_list_type = nmtools_list<nmtools_list<nm_index_t>>;
            using node_ids_type = nmtools_list<nm_index_t>;
            using digraph_type  = digraph_t<adjacency_list_type,node_ids_type,node_attributes_t,edge_attributes_t>;
            return digraph_type{};
        } else if constexpr (meta::is_constant_index_v<adjacency_list_t>) {
            constexpr auto MAX_NODES = adjacency_list_t::value;
            // prefer static vector over array to make it easier to resize
            using inner_t = nmtools_static_vector<nm_index_t,MAX_NODES>;
            using outer_t = nmtools_static_vector<inner_t,MAX_NODES>;
            using adjacency_list_type = outer_t;
            using node_ids_type = nmtools_static_vector<nm_index_t,MAX_NODES>;
            using digraph_type  = digraph_t<adjacency_list_type,node_ids_type,node_attributes_t,edge_attributes_t>;
            return digraph_type{};
        } else if constexpr (meta::is_adjacency_list_v<adjacency_list_t>) {
            // TODO: check if adj_list and node_ids has the same length
            // and use panic to assert condition instead of return maybe
            return digraph_t{adj_list,node_ids,node_attributes,edge_attributes};
        }
    } // digraph

    template <typename adjacency_list_t, typename node_ids_t, typename node_attributes_t, typename edge_attribute_t>
    constexpr auto topological_sort(const digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attribute_t>& digraph)
    {
        auto sorted = network::topological_sort(digraph.adjacency_list);
        return network::map_ids(sorted,digraph.node_ids);
    }

    template <typename adjacency_list_t, typename node_ids_t, typename node_attributes_t, typename edge_attribute_t>
    constexpr auto topological_generations(const digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attribute_t>& digraph)
    {
        auto generations = network::topological_generations(digraph.adjacency_list);
        return network::map_ids(generations,digraph.node_ids);
    }

    template <typename g_adjacency_list_t, typename g_node_ids_t, typename g_node_attributes_t, typename g_edge_attribute_t
        , typename h_adjacency_list_t, typename h_node_ids_t, typename h_node_attributes_t, typename h_edge_attribute_t>
    constexpr auto compose(const digraph_t<g_adjacency_list_t,g_node_ids_t,g_node_attributes_t,g_edge_attribute_t>& G
        , const digraph_t<h_adjacency_list_t,h_node_ids_t,h_node_attributes_t,h_edge_attribute_t>& H
    ) {
        static_assert( is_none_v<g_edge_attribute_t> && is_none_v<h_edge_attribute_t>
            , "expected edge attributes to be none for network::compose" );

        static_assert( !is_none_v<g_node_ids_t> && !is_none_v<h_node_ids_t>
            , "can't compose two nodes with none ids" );

        auto fuse_node_attributes = [&](const auto& G, const auto& H){
            if constexpr (is_none_v<g_node_attributes_t> && is_none_v<h_node_attributes_t>) {
                return None;
            } else if constexpr (meta::is_tuple_v<g_node_attributes_t>
                && meta::is_tuple_v<h_node_attributes_t>
            ) {
                return utility::tuple_cat(G.node_attributes,H.node_attributes);
            } else {
                // assume same node type & has value_type
                auto vtype = [](){
                    using g_value_t = meta::get_value_type_t<g_node_attributes_t>;
                    using h_value_t = meta::get_value_type_t<h_node_attributes_t>;
                
                    using value_type = g_value_t;

                    static_assert( meta::is_same_v<g_value_t,h_value_t> && !meta::is_fail_v<g_value_t>
                        , "invalid type for G's or H's node attributes" );

                    constexpr auto B_NUM_G_NODES = meta::max_len_v<g_node_attributes_t>;
                    constexpr auto B_NUM_H_NODES = meta::max_len_v<h_node_attributes_t>;
                    if constexpr ((B_NUM_G_NODES >= 0) && (B_NUM_H_NODES >= 0)) {
                        using type = nmtools_static_vector<value_type,B_NUM_G_NODES+B_NUM_H_NODES>;
                        return meta::as_value_v<type>;
                    } else {
                        using type = nmtools_list<value_type>;
                        return meta::as_value_v<type>;
                    }
                }();
                using type = meta::type_t<decltype(vtype)>;

                auto attributes = type {};

                auto g_num_nodes = len(G.node_attributes);
                auto h_num_nodes = len(H.node_attributes);
                auto dst_num_nodes = g_num_nodes + h_num_nodes;
                if constexpr (meta::is_resizable_v<type>) {
                    attributes.resize(dst_num_nodes);
                }

                for (nm_size_t i=0; i<(nm_size_t)g_num_nodes; i++) {
                    at(attributes,i) = at(G.node_attributes,i);
                }
                for (nm_size_t i=0; i<(nm_size_t)h_num_nodes; i++) {
                    at(attributes,i+g_num_nodes) = at(H.node_attributes,i);
                }

                return attributes;
            }
        };
        auto fuse_node_ids = [&](const auto& G, const auto& H){
            if constexpr (meta::is_constant_index_array_v<g_node_ids_t>
                && meta::is_constant_index_array_v<h_node_ids_t>
            ) {
                return utility::tuple_cat(G.node_ids,H.node_ids);
            } else {
                auto vtype = [](){
                    using index_t = nm_size_t;
                    constexpr auto B_NUM_G_NODES = meta::max_len_v<g_node_ids_t>;
                    constexpr auto B_NUM_H_NODES = meta::max_len_v<h_node_ids_t>;
                    if constexpr ((B_NUM_G_NODES >= 0) && (B_NUM_H_NODES >= 0)) {
                        using type = nmtools_static_vector<index_t,B_NUM_G_NODES+B_NUM_H_NODES>;
                        return meta::as_value_v<type>;
                    } else {
                        using type = nmtools_list<index_t>;
                        return meta::as_value_v<type>;
                    }
                }();
                using type = meta::type_t<decltype(vtype)>;

                auto node_ids = type {};

                auto g_num_nodes = len(G.node_ids);
                auto h_num_nodes = len(H.node_ids);
                auto dst_num_nodes = g_num_nodes + h_num_nodes;
                if constexpr (meta::is_resizable_v<type>) {
                    node_ids.resize(dst_num_nodes);
                }

                for (nm_size_t i=0; i<(nm_size_t)g_num_nodes; i++) {
                    at(node_ids,i) = at(G.node_ids,i);
                }
                for (nm_size_t i=0; i<(nm_size_t)h_num_nodes; i++) {
                    at(node_ids,i+g_num_nodes) = at(H.node_ids,i);
                }

                return node_ids;
            }
        };

        auto result_pair = network::compose(G.adjacency_list,H.adjacency_list,G.node_ids,H.node_ids);
        const auto& adj_list = nmtools::get<0>(result_pair);
        const auto& node_ids = nmtools::get<1>(result_pair);

        // networkx will take the attribute of H for any overlapping node
        auto node_attributes = fuse_node_attributes(H,G);
        auto src_node_ids = fuse_node_ids(H,G);
        auto node_data = network::filter_nodes(node_attributes,src_node_ids,node_ids);
        return digraph(adj_list,node_ids,node_data);
    } // compose

    template <typename adjacency_list_t, typename node_ids_t, typename node_attributes_t, typename edge_attribute_t>
    constexpr auto is_directed_acyclic_graph(const digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attribute_t>& digraph)
    {
        return network::is_directed_acyclic_graph(digraph.adjacency_list);
    }
} // namespace nmtools::network

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct GENERATE_NODE_IDS_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t>
    struct resolve_optype<
        void, network::generate_node_ids_t, adjacency_list_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>) {
                using type = error::GENERATE_NODE_IDS_UNSUPPORTED<adjacency_list_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_adjacency_list_v<adjacency_list_t>) {
                constexpr auto adj_list = to_value_v<adjacency_list_t>;
                constexpr auto result = network::generate_node_ids(adj_list);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                // TODO: read index_t from adjacency_list_t (e.g. keep int8 as int8)
                using index_t = nm_size_t;
                [[maybe_unused]]
                constexpr auto MAX_NODES = max_len_v<adjacency_list_t>;
                constexpr auto NUM_NODES = len_v<adjacency_list_t>;
                // now -1 indicates failure, 0 may means 0-tuple
                if constexpr (NUM_NODES >= 0) {
                    using type = nmtools_array<index_t,NUM_NODES>;
                    return as_value_v<type>;
                } else if constexpr (MAX_NODES >= 0) {
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
} // namespace nmtools::meta

#if NMTOOLS_HAS_STRING
namespace nmtools::utils::impl
{
    template <typename adjacency_list_t
        , typename node_ids_t
        , typename node_attributes_t
        , typename edge_attributes_t>
    struct to_string_t<
        network::digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t>, graphviz_t
    > {
        using digraph_type = network::digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t>;
        using result_type  = nmtools_string;

        inline auto operator()(const digraph_type& digraph) const
        {
            auto graphviz = nmtools_string("digraph G");
            graphviz += "{\n";

            auto out_edges  = digraph.out_edges();
            auto edge_loop = [&](auto i){
                auto edge_string = nmtools_string();
                const auto& out_edge = at(out_edges,i);
                auto src_edge = nmtools::get<0>(out_edge);
                auto dst_edge = nmtools::get<1>(out_edge);

                edge_string += to_string(src_edge,utils::Compact);
                edge_string += " -> ";
                edge_string += to_string(dst_edge,utils::Compact);
                edge_string += ":";
                edge_string += to_string(src_edge,utils::Compact);

                const auto& edge = digraph.edges(src_edge,dst_edge);
                using edge_t = meta::remove_cvref_t<decltype(edge)>;
                if constexpr (!is_none_v<edge_t>
                    && (meta::has_to_string_v<edge_t> || meta::is_same_v<edge_t,nmtools_string>)
                ) {
                    edge_string += " [";
                    edge_string += "label=\"";
                    if constexpr (meta::has_to_string_v<edge_t>) {
                        auto edge_str = edge.to_string();
                        edge_string += edge_str;
                    } else {
                        edge_string += edge;
                    }
                    edge_string += "\"";
                    edge_string += "]";
                }

                edge_string += "\n";

                replace_string(edge_string,nmtools_string("->"),nmtools_string("[graphviz_edge_connector]"));
                replace_string(edge_string,nmtools_string("{"),nmtools_string("[open_curl_bracket]"));
                replace_string(edge_string,nmtools_string("}"),nmtools_string("[close_curl_bracket]"));
                replace_string(edge_string,nmtools_string("<"),nmtools_string("[open_angle_bracket]"));
                replace_string(edge_string,nmtools_string(">"),nmtools_string("[close_angle_bracket]"));

                replace_string(edge_string,nmtools_string("[open_curl_bracket]"),nmtools_string("\\{"));
                replace_string(edge_string,nmtools_string("[close_curl_bracket]"),nmtools_string("\\}"));
                replace_string(edge_string,nmtools_string("[open_angle_bracket]"),nmtools_string("\\<"));
                replace_string(edge_string,nmtools_string("[close_angle_bracket]"),nmtools_string("\\>"));

                replace_string(edge_string,nmtools_string("[graphviz_record_layout_open]"),nmtools_string("{"));
                replace_string(edge_string,nmtools_string("[graphviz_record_layout_close]"),nmtools_string("}"));
                replace_string(edge_string,nmtools_string("[graphviz_record_fieldid_open]"),nmtools_string("<"));
                replace_string(edge_string,nmtools_string("[graphviz_record_fieldid_close]"),nmtools_string(">"));
                replace_string(edge_string,nmtools_string("[graphviz_edge_connector]"),nmtools_string("->"));

                graphviz += edge_string;
            };
            using out_edges_t = decltype(out_edges);
            if constexpr (meta::is_tuple_v<out_edges_t>) {
                constexpr auto NUM_EDGES = meta::len_v<out_edges_t>;
                meta::template_for<NUM_EDGES>([&](auto i){
                    edge_loop(i);
                });
            } else {
                auto num_edges = len(out_edges);
                for (nm_size_t i=0; i<(nm_size_t)num_edges; i++) {
                    edge_loop(i);
                }
            }

            auto node_ids = digraph.nodes();
            auto num_nodes = len(node_ids);
            auto node_loop = [&](auto i){
                auto node_string = nmtools_string();
                auto node_id = at(node_ids,i);
                static_assert( meta::is_index_v<decltype(node_id)> );
                node_string += to_string(node_id);
                node_string += "[";
                node_string += "shape=\"record\" style=\"rounded,filled\" color=\"black\" fillcolor=\"gray93\" ";

                const auto& node = digraph.nodes(node_id);
                using node_t = meta::remove_cvref_t<decltype(node)>;
                if constexpr (!is_none_v<node_t>
                    && (meta::has_to_string_v<node_t> || meta::is_same_v<node_t,nmtools_string>)
                ) {
                    node_string += "label=\" ";
                    node_string += "id:";
                    node_string += to_string(node_id);
                    node_string += " | ";
                    if constexpr (meta::has_to_string_v<node_t>) {
                        auto node_str = node.to_string();
                        node_string += node_str;
                    } else {
                        node_string += node;
                    }
                    node_string += "\"";
                }

                node_string += "]\n";

                replace_string(node_string,nmtools_string("{"),nmtools_string("[open_curl_bracket]"));
                replace_string(node_string,nmtools_string("}"),nmtools_string("[close_curl_bracket]"));
                replace_string(node_string,nmtools_string("<"),nmtools_string("[open_angle_bracket]"));
                replace_string(node_string,nmtools_string(">"),nmtools_string("[close_angle_bracket]"));

                replace_string(node_string,nmtools_string("[open_curl_bracket]"),nmtools_string("\\{"));
                replace_string(node_string,nmtools_string("[close_curl_bracket]"),nmtools_string("\\}"));
                replace_string(node_string,nmtools_string("[open_angle_bracket]"),nmtools_string("\\<"));
                replace_string(node_string,nmtools_string("[close_angle_bracket]"),nmtools_string("\\>"));

                replace_string(node_string,nmtools_string("[graphviz_record_layout_open]"),nmtools_string("{"));
                replace_string(node_string,nmtools_string("[graphviz_record_layout_close]"),nmtools_string("}"));
                replace_string(node_string,nmtools_string("[graphviz_record_fieldid_open]"),nmtools_string("<"));
                replace_string(node_string,nmtools_string("[graphviz_record_fieldid_close]"),nmtools_string(">"));

                graphviz += node_string;
            };
            if constexpr (meta::is_tuple_v<decltype(node_ids)>) {
                constexpr auto N = meta::len_v<decltype(node_ids)>;
                meta::template_for<N>([&](auto i){
                    node_loop(i);
                });
            } else {
                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    node_loop(i);
                }
            }

            graphviz += "}";
            return graphviz;
        }
    };
}
#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_NETWORK_DIGRAPH_HPP