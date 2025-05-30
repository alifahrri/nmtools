#ifndef NMTOOLS_NETWORK_IN_DEGREE_HPP
#define NMTOOLS_NETWORK_IN_DEGREE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"

namespace nmtools::tag
{
    struct in_degree_t {};
}

namespace nmtools::network
{
    template <typename adjacency_list_t>
    constexpr auto in_degree(const adjacency_list_t& list)
    {
        if constexpr (meta::is_maybe_v<adjacency_list_t>) {
            using result_t = decltype(in_degree(unwrap(list)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(list)
                ? return_t{in_degree(unwrap(list))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::in_degree_t,adjacency_list_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_index_array_v<result_t>
            ) {
                auto num_nodes = len(list);

                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(num_nodes);
                }

                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    at(result,i) = 0;
                }

                if constexpr (meta::is_tuple_v<adjacency_list_t>) {
                    constexpr auto NUM_NODES = meta::len_v<adjacency_list_t>;
                    meta::template_for<NUM_NODES>([&](auto I){
                        auto n = len(at(list,I));
                        for (nm_size_t j=0; j<(nm_size_t)n; j++) {
                            auto node_id = at(at(list,I),j);
                            at(result,node_id)++;
                        }
                    });
                } else {
                    for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                        for (nm_size_t j=0; j<(nm_size_t)at(list,i).size(); j++) {
                            auto node_id = at(at(list,i),j);
                            at(result,node_id)++;
                        }
                    }
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
        struct IN_DEGREE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t>
    struct resolve_optype<
        void, tag::in_degree_t, adjacency_list_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>) {
                using type = error::IN_DEGREE_UNSUPPORTED<adjacency_list_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_adjacency_list_v<adjacency_list_t>) {
                constexpr auto adj_list = to_value_v<adjacency_list_t>;
                constexpr auto result = network::in_degree(adj_list);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
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
    };
}

#endif // NMTOOLS_NETWORK_IN_DEGREE_HPP