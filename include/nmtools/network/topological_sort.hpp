#ifndef NMTOOLS_NETWORK_TOPOLOGICAL_SORT_HPP
#define NMTOOLS_NETWORK_TOPOLOGICAL_SORT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/network/in_degree.hpp"

namespace nmtools::tag
{
    struct topological_sort_queue_t {};
    struct topological_sort_t {};
}

namespace nmtools::network
{
    template <typename adjacency_list_t>
    constexpr auto topological_sort(const adjacency_list_t& adjacency_list)
    {
        if constexpr (meta::is_maybe_v<adjacency_list_t>) {
            using result_t = decltype(topological_sort(unwrap(adjacency_list)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adjacency_list)
                ? return_t{topological_sort(unwrap(adjacency_list))}
                : return_t{meta::Nothing}
            );
        } else {
            using queue_t  = meta::resolve_optype_t<tag::topological_sort_queue_t,adjacency_list_t>;
            using result_t = meta::resolve_optype_t<tag::topological_sort_t,adjacency_list_t>;
            // TODO: support constant adjacency list
            using return_t = nmtools_maybe<result_t>;

            [[maybe_unused]]
            auto queue  = queue_t {};
            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_index_array_v<result_t>
            ) {
                nm_size_t count = 0;

                auto in_degree = network::in_degree(adjacency_list);

                // initialize queue with input (in_degree 0)
                for (nm_size_t i=0; i<(nm_size_t)adjacency_list.size(); i++) {
                    if (in_degree[i] == 0) {
                        queue.push(i);
                    }
                }
                for (; !queue.empty();) {
                    auto node = queue.pop();
                    count++;
                    result.push_back(node);
                    for (nm_size_t j=0; j<(nm_size_t)adjacency_list[node].size(); j++) {
                        auto neighbor = adjacency_list[node][j];
                        in_degree[neighbor] -= 1;
                        if (in_degree[neighbor] == 0) {
                            queue.push(neighbor);
                        }
                    }
                }

                if (count != (nm_size_t)len(adjacency_list)) {
                    return return_t{meta::Nothing};
                } else {
                    return return_t{result};
                }
            } else {
                return result;
            }
        }
    }
} // namespace nmtools::network

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct TOPOLOGICAL_SORT_QUEUE_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct TOPOLOGICAL_SORT_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t>
    struct resolve_optype<
        void, tag::topological_sort_queue_t, adjacency_list_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>) {
                using type = error::TOPOLOGICAL_SORT_QUEUE_UNSUPPORTED<adjacency_list_t>;
                return as_value_v<type>;
            } else {
                // TODO: deduce index type from adjacency_list_t
                using index_t = nm_index_t;
                constexpr auto NUM_NODES = len_v<adjacency_list_t>;
                [[maybe_unused]]
                constexpr auto B_NUM_NODES = bounded_size_v<adjacency_list_t>;
                if constexpr (NUM_NODES > 0) {
                    using type = nmtools_static_queue<index_t,NUM_NODES>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_NUM_NODES)>) {
                    using type = nmtools_static_queue<index_t,B_NUM_NODES>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_queue<index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // tag::topological_sort_queue_t

    template <typename adjacency_list_t>
    struct resolve_optype<
        void, tag::topological_sort_t, adjacency_list_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>) {
                using type = error::TOPOLOGICAL_SORT_UNSUPPORTED<adjacency_list_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_adjacency_list_v<adjacency_list_t>) {
                constexpr auto adjacency_list = to_value_v<adjacency_list_t>;
                constexpr auto m_result = network::topological_sort(adjacency_list);
                constexpr auto result = unwrap(m_result);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                // TODO: deduce index type from adjacency_list_t
                using index_t = nm_index_t;
                constexpr auto NUM_NODES = len_v<adjacency_list_t>;
                [[maybe_unused]]
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
    }; // tag::topological_sort_t
} // namespace nmtools::meta

#endif // NMTOOLS_NETWORK_TOPOLOGICAL_SORT_HPP