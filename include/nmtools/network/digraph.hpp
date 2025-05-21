#ifndef NMTOOLS_NETWORK_DIGRAPH_HPP
#define NMTOOLS_NETWORK_DIGRAPH_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/contains.hpp"
#include "nmtools/index/index_of.hpp"
#include "nmtools/network/out_edges.hpp"
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

        #if 0
        auto node_ids_vtype = [](){
            constexpr auto NUM_NODES = meta::len_v<adjacency_list_t>;
            [[maybe_unused]]
            constexpr auto B_NUM_NODES = meta::bounded_size_v<adjacency_list_t>;
            if constexpr (NUM_NODES > 0) {
                // prefer static vector over array to make it easier to resize
                using type = nmtools_static_vector<nm_index_t,NUM_NODES>;
                return meta::as_value_v<type>;
            } else if constexpr (!meta::is_fail_v<decltype(B_NUM_NODES)>) {
                using type = nmtools_static_vector<nm_index_t,B_NUM_NODES>;
                return meta::as_value_v<type>;
            } else {
                // TODO: use small vector
                using type = nmtools_list<nm_index_t>;
                return meta::as_value_v<type>;
            }
        }();
        using node_ids_type = meta::type_t<decltype(node_ids_vtype)>;

        auto node_ids = node_ids_type {};

        auto num_nodes = len(adj_list);
        if constexpr (meta::is_resizable_v<node_ids_type>) {
            node_ids.resize(num_nodes);
        }

        for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
            at(node_ids,i) = i;
        }
        #endif
    }

    template <typename attributes_t=none_t, typename node_ids_t=none_t, typename adjacency_list_t=none_t>
    constexpr auto digraph([[maybe_unused]] const adjacency_list_t& adj_list=adjacency_list_t{}
        , const node_ids_t& node_ids=node_ids_t{}
        , [[maybe_unused]] const attributes_t& attributes=attributes_t{}
    );

    template <typename adjacency_list_t, typename node_ids_t, typename attributes_t=none_t>
    struct digraph_t
    {
        // TODO: check with attributes_t which one has bounded size
        using adjacency_list_type = adjacency_list_t;
        // store mapping from node key/id to index in adjacency_list
        // using id_buffer_type = meta::resolve_optype_t<generate_node_ids_t,adjacency_list_t>;
        using node_ids_type = node_ids_t;

        static constexpr auto attributes_vtype = [](){
            if constexpr (is_none_v<attributes_t> || meta::is_tuple_v<attributes_t>) {
                using type = attributes_t;
                return meta::as_value_v<type>;
            } else if constexpr (meta::is_vtype_v<attributes_t>) {
                using attribute_t = meta::type_t<attributes_t>;
                // TODO: check id_buffer / adjacency list if has bounded size nodes
                using type = nmtools_list<attribute_t>;
                return meta::as_value_v<type>;
            } else {
                using type = attributes_t;
                return meta::as_value_v<type>;
            }
        }();
        // TODO: check with adjacency_list which one has bounded size
        using attributes_type = meta::type_t<decltype(attributes_vtype)>;
        
        static constexpr auto attribute_vtype = [](){
            if constexpr (is_none_v<attributes_t> || meta::is_tuple_v<attributes_t>) {
                // indicates that no specific types or no attribute at all
                using type = none_t;
                return meta::as_value_v<type>;
            } else {
                using type = typename attributes_t::value_type;
                return meta::as_value_v<type>;
            }
        }();
        using attribute_type = meta::type_t<decltype(attribute_vtype)>;

        adjacency_list_type adjacency_list;
        node_ids_type      node_ids;
        attributes_type     attributes;

        constexpr digraph_t() {}

        constexpr digraph_t(const adjacency_list_t& adjacency_list
            , const node_ids_t& node_ids
            , const attributes_t& attributes=attributes_t{}
        )
            : adjacency_list(adjacency_list)
            , node_ids(node_ids)
            , attributes(attributes)
        {}

        // convert constant adjacency list to compile-time value
        template <typename adj_list_t, auto extra_nodes=0>
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
            auto dst_adj_list = digraph(adj_list);
            return dst_adj_list;
        }

        template <typename node_id_t, typename attribute_t=none_t>
        constexpr decltype(auto) add_node([[maybe_unused]] node_id_t node_id
            , [[maybe_unused]] const attribute_t& attribute=attribute_t{})
        {
            static_assert(
                is_none_v<attribute_t> || meta::is_same_v<attribute_t,attribute_type>
                , "unsupported attribute type"
            );
            if constexpr (meta::is_constant_adjacency_list_v<adjacency_list_type>) {
                constexpr auto result = [](){
                    auto dst_adj_list = to_value<adjacency_list_type,1>();
                    auto NODE_ID = node_id_t::value;
                    dst_adj_list.add_node(NODE_ID);
                    return dst_adj_list;
                }();

                auto vtype = nmtools_adjacency_list_vtype(result.adjacency_list);
                using type = meta::type_t<decltype(vtype)>;
                return digraph(type{});
            } else {
                if (!index::contains(node_ids,node_id)) {
                    node_ids.push_back(node_id);
                    auto num_nodes = len(node_ids);
                    if (len(adjacency_list) < num_nodes) {
                        if constexpr (meta::is_resizable_v<adjacency_list_type>) {
                            adjacency_list.resize(num_nodes);
                        }
                    }
                }

                if constexpr (!is_none_v<attribute_type>) {
                    auto num_nodes = len(node_ids);
                    if (len(attributes) != num_nodes) {
                        if constexpr (meta::is_resizable_v<attributes_type>) {
                            attributes.resize(num_nodes);
                        }
                    }
                    if (len(attributes) != num_nodes) {
                        nmtools_panic( false
                            , "failed to resize attributes"
                        );
                    }
                    at(attributes,-1) = attribute;
                }

                return *this;
            }
        }

        template <typename from_t, typename to_t>
        constexpr decltype(auto) add_edge(from_t from, to_t to)
        {
            if constexpr (meta::is_constant_adjacency_list_v<adjacency_list_type>) {
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
            } else {
                if (!index::contains(node_ids,from)) {
                    auto n_nodes  = len(node_ids);
                    auto dst_size = n_nodes + 1;
                    if constexpr (meta::is_resizable_v<node_ids_type>) {
                        node_ids.resize(dst_size);
                    }
                    // add extra if to make it usable in constant expression
                    if (len(node_ids) != dst_size) {
                        nmtools_panic( false
                            , "can't add more edge"
                        );
                    }
                    at(node_ids,n_nodes) = from;
                    if constexpr (meta::is_resizable_v<adjacency_list_type>) {
                        adjacency_list.resize(dst_size);
                    }
                }
    
                if (!index::contains(node_ids,to)) {
                    auto n_nodes  = len(node_ids);
                    auto dst_size = n_nodes + 1;
                    if constexpr (meta::is_resizable_v<node_ids_type>) {
                        node_ids.resize(dst_size);
                    }
                    // add extra if to make it usable in constant expression
                    if (len(node_ids) != dst_size) {
                        nmtools_panic( false
                            , "can't add more edge"
                        );
                    }
                    at(node_ids,n_nodes) = to;
                    if constexpr (meta::is_resizable_v<adjacency_list_type>) {
                        adjacency_list.resize(dst_size);
                    }
                }
    
                auto from_idx = unwrap(index::index_of(node_ids,from));
                auto to_idx   = unwrap(index::index_of(node_ids,to));
    
                auto& froms_neigbors = at(adjacency_list,from_idx);
                using neighbors_t = meta::remove_cvref_t<decltype(froms_neigbors)>;
                if (!index::contains(froms_neigbors,to_idx)) {
                    auto n_neighbors = len(froms_neigbors);
                    auto dst_size = n_neighbors + 1;
                    if constexpr (meta::is_resizable_v<neighbors_t>) {
                        froms_neigbors.resize(dst_size);
                    }
                    // add extra if to make it usable in constant expression
                    if (len(froms_neigbors) != dst_size) {
                        nmtools_panic( false
                            , "can't add more neighbors"
                        );
                    }
                    at(froms_neigbors,n_neighbors) = to_idx;
                }
    
                return *this;
            }
        }

        template <typename pair_t>
        constexpr decltype(auto) add_nodes_from(const pair_t& pair)
        {
            // TODO: check if index array of size 2
            auto from = at(pair,meta::ct_v<0>);
            auto to   = at(pair,meta::ct_v<1>);
            return add_edge(from,to);
        }

        template <typename edges_t>
        constexpr decltype(auto) add_edges_from(const edges_t& edges)
        {
            if constexpr (meta::is_constant_adjacency_list_v<adjacency_list_type>) {

            } else {
                constexpr auto N_PAIRS = meta::len_v<edges_t>;
                if constexpr (N_PAIRS > 0) {
                    meta::template_for<N_PAIRS>([&](auto I){
                        const auto& edge = at(edges,I);
                        auto from = at(edge,meta::ct_v<0>);
                        auto to   = at(edge,meta::ct_v<1>);
                        add_edge(from,to);
                    });
                } else {
                    auto n_pairs = len(edges);
                    for (nm_size_t i=0; i<(nm_size_t)n_pairs; i++) {
                        const auto& edge = at(edges,i);
                        auto from = at(edge,meta::ct_v<0>);
                        auto to   = at(edge,meta::ct_v<1>);
                        add_edge(from,to);
                    }
                }
                return *this;
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
        constexpr decltype(auto) nodes(node_id_t node_id) const
        {
            if constexpr (!is_none_v<attributes_type>) {
                // TODO: check if node_id is constant index if list is constant adjacency list
                auto idx = index::index_of(node_ids,node_id);
                return attributes[unwrap(idx)];
            }
        }

        template <typename node_id_t>
        constexpr decltype(auto) nodes(node_id_t node_id)
        {
            if constexpr (!is_none_v<attributes_type>) {
                // TODO: check if node_id is constant index if list is constant adjacency list
                auto idx = index::index_of(node_ids,node_id);
                return attributes[unwrap(idx)];
            }
        }

        constexpr decltype(auto) out_edges() const noexcept
        {
            // TODO: support nbunch
            if constexpr (meta::is_constant_adjacency_list_v<adjacency_list_type>
                && meta::is_constant_index_array_v<node_ids_type>
            ) {
                constexpr auto result = [](){
                    auto adj_list = to_value<adjacency_list_type>();
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

    template <typename attributes_t, typename node_ids_t, typename adjacency_list_t>
    constexpr auto digraph([[maybe_unused]] const adjacency_list_t& adj_list
        , [[maybe_unused]] const node_ids_t& node_ids
        , [[maybe_unused]] const attributes_t& attributes)
    {
        if constexpr (is_none_v<adjacency_list_t>) {
            // TODO: use small vector
            using adjacency_list_type = nmtools_list<nmtools_list<nm_index_t>>;
            using node_ids_type = nmtools_list<nm_index_t>;
            return digraph_t<adjacency_list_type,node_ids_type,attributes_t>{};
        } else if constexpr (meta::is_constant_index_v<adjacency_list_t>) {
            constexpr auto MAX_NODES = adjacency_list_t::value;
            // prefer static vector over array to make it easier to resize
            using inner_t = nmtools_static_vector<nm_index_t,MAX_NODES>;
            using outer_t = nmtools_static_vector<inner_t,MAX_NODES>;
            using adjacency_list_type = outer_t;
            using node_ids_type = nmtools_static_vector<nm_index_t,MAX_NODES>;
            return digraph_t<adjacency_list_type,node_ids_type,attributes_t>{};
        } else if constexpr (meta::is_adjacency_list_v<adjacency_list_t>) {
            if constexpr (!is_none_v<node_ids_t>) {
                // TODO: check if adj_list and node_ids has the same length
                // and use panic to assert condition instead of return maybe
                return digraph_t{adj_list,node_ids,attributes};
            } else {
                auto m_node_ids = generate_node_ids(adj_list);
                return digraph_t{adj_list,m_node_ids,attributes};
            }
        }
    } // digraph

    template <typename adjacency_list_t, typename attributes_t>
    constexpr auto topological_sort(const digraph_t<adjacency_list_t,attributes_t>& digraph)
    {
        auto sorted = network::topological_sort(digraph.adjacency_list);
        auto result = network::map_ids(sorted,digraph.node_ids);
        return result;
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
}

#if NMTOOLS_HAS_STRING
namespace nmtools::utils::impl
{
    template <typename adjacency_list_t, typename attributes_t>
    struct to_string_t<
        network::digraph_t<adjacency_list_t,attributes_t>, graphviz_t
    > {
        using digraph_type = network::digraph_t<adjacency_list_t,attributes_t>;
        using result_type  = nmtools_string;

        inline auto operator()(const digraph_type& digraph) const noexcept
        {
            auto graphviz = nmtools_string("digraph G");
            graphviz += "{\n";

            auto out_edges  = digraph.out_edges();
            auto inner_loop = [&](auto i){
                const auto& out_edge = at(out_edges,i);
                auto src_edge = nmtools::get<0>(out_edge);
                auto dst_edge = nmtools::get<1>(out_edge);

                graphviz += to_string(src_edge,utils::Compact);
                graphviz += " -> ";
                graphviz += to_string(dst_edge,utils::Compact);
                graphviz += ":";
                graphviz += to_string(src_edge,utils::Compact);
                graphviz += "\n";
            };
            using out_edges_t = decltype(out_edges);
            if constexpr (meta::is_tuple_v<out_edges_t>) {
                constexpr auto NUM_EDGES = meta::len_v<out_edges_t>;
                meta::template_for<NUM_EDGES>([&](auto i){
                    inner_loop(i);
                });
            } else {
                auto num_edges = len(out_edges);
                for (nm_size_t i=0; i<(nm_size_t)num_edges; i++) {
                    inner_loop(i);
                }
            }

            graphviz += "}";
            return graphviz;
        }
    };
}
#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_NETWORK_DIGRAPH_HPP