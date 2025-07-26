#ifndef NMTOOLS_NETWORK_COMMON_HPP
#define NMTOOLS_NETWORK_COMMON_HPP

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
}

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

#endif // NMTOOLS_NETWORK_COMMON_HPP