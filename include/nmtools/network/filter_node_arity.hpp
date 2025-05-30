#ifndef NMTOOLS_NETWORK_FILTER_NODE_ARITY_HPP
#define NMTOOLS_NETWORK_FILTER_NODE_ARITY_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/network/topological_sort.hpp"
#include "nmtools/network/predecessors.hpp"

namespace nmtools::tag
{
    struct filter_node_arity_t {};
}

namespace nmtools::network
{
    // topologically sorted node filtering by arity
    template <typename adjacency_list_t, typename arity_t>
    constexpr auto filter_node_arity(const adjacency_list_t& adjacency_list, arity_t arity)
    {
        if constexpr (meta::is_maybe_v<arity_t>
            || meta::is_maybe_v<adjacency_list_t>
        ) {
            using result_t = decltype(filter_node_arity(unwrap(adjacency_list),unwrap(arity)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adjacency_list) && has_value(arity)
                ? return_t{filter_node_arity(unwrap(adjacency_list),unwrap(arity))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::filter_node_arity_t,adjacency_list_t,arity_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_index_array_v<result_t>
            ) {
                using return_t = nmtools_maybe<result_t>;
                auto m_sorted = network::topological_sort(adjacency_list);
                if (!has_value(m_sorted)) {
                    return return_t{meta::Nothing};
                }
                auto sorted = unwrap(m_sorted);
                using sorted_t = decltype(sorted);

                auto predecessors = network::predecessors(adjacency_list);

                auto inner_loop = [&](auto i){
                    auto node = at(sorted,i);
                    // TODO: read index type from adjacency list
                    if ((nm_index_t)len(at(predecessors,node)) == (nm_index_t)arity) {
                        // assume has push_back
                        result.push_back(node);
                    }
                };

                if constexpr (meta::is_tuple_v<sorted_t>) {
                    meta::template_for<meta::len_v<sorted_t>>([&](auto I){
                        inner_loop(I);
                    });
                } else {
                    for (nm_size_t i=0; i<(nm_size_t)len(sorted); i++) {
                        inner_loop(i);
                    }
                }

                return return_t{result};
            } else {
                return result;
            }
        }
    }
}

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct FILTER_NODE_ARITY_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t, typename arity_t>
    struct resolve_optype<
        void, tag::filter_node_arity_t, adjacency_list_t, arity_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>
                || !is_index_v<arity_t>
            ) {
                using type = error::FILTER_NODE_ARITY_UNSUPPORTED<adjacency_list_t,arity_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_adjacency_list_v<adjacency_list_t>
                && is_constant_index_v<arity_t>
            ) {
                constexpr auto adjacency_list = to_value_v<adjacency_list_t>;
                constexpr auto arity  = to_value_v<arity_t>;
                constexpr auto m_result = network::filter_node_arity(adjacency_list,arity);
                constexpr auto result = unwrap(m_result);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                // TODO: read index type from adjacency list
                using index_t = nm_index_t;
                constexpr auto NUM_NODES = len_v<adjacency_list_t>;
                constexpr auto B_NUM_NODES = max_len_v<adjacency_list_t>;
                if constexpr (NUM_NODES >= 0) {
                    using type = nmtools_static_vector<index_t,NUM_NODES>;
                    return as_value_v<type>;
                } else if constexpr (B_NUM_NODES >= 0) {
                    using type = nmtools_static_vector<index_t,B_NUM_NODES>;
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

#endif // NMTOOLS_NETWORK_FILTER_NODE_ARITY_HPP