#ifndef NMTOOLS_NETWORK_TOPOLOGICAL_GENERATIONS_HPP
#define NMTOOLS_NETWORK_TOPOLOGICAL_GENERATIONS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/network/in_degree.hpp"

namespace nmtools::tag
{
    struct topological_generations_queue_t {};
    struct topological_generations_t {};
}

namespace nmtools::network
{
    template <typename adjacency_list_t>
    constexpr auto topological_generations(const adjacency_list_t& adjacency_list)
    {
        if constexpr (meta::is_maybe_v<adjacency_list_t>) {
            using result_t = decltype(topological_generation(unwrap(adjacency_list)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adjacency_list)
                ? return_t{topological_generation(unwrap(adjacency_list))}
                : return_t{meta::Nothing}
            );
        } else {
            using queue_t  = meta::resolve_optype_t<tag::topological_generations_queue_t,adjacency_list_t>;
            using result_t = meta::resolve_optype_t<tag::topological_generations_t,adjacency_list_t>;

            auto result = result_t {}; // all generations

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_adjacency_list_v<result_t>
            ) {
                using return_t = nmtools_maybe<result_t>;

                auto in_degree = network::in_degree(adjacency_list);

                [[maybe_unused]]
                auto current = queue_t {};  // current generations
                // initialize queue with input (in_degree = 0)
                for (nm_size_t i=0; i<(nm_size_t)adjacency_list.size(); i++) {
                    if (in_degree[i] == 0) {
                        current.push_back(i);
                    }
                }

                nm_size_t count = 0;

                for (; current.size(); ) {
                    // next generation
                    auto next = queue_t {};
                    auto gen_id = result.size();
                    if constexpr (meta::is_resizable_v<result_t>) {
                        auto dst_size = gen_id + 1;
                        result.resize(dst_size);
                    }
                    // TODO: sort current
                    for (nm_size_t i=0; i<(nm_size_t)current.size(); i++) {
                        auto node = at(current,i);
                        count++;
                        at(result,gen_id).push_back(node);
                        const auto& neighbors = at(adjacency_list,node);
                        for (nm_size_t j=0; j<(nm_size_t)neighbors.size(); j++) {
                            auto v = at(neighbors,j);
                            if (at(in_degree,v) > 0) {
                                at(in_degree,v) -= 1;
                                if (at(in_degree,v) == 0) {
                                    next.push_back(v);
                                }
                            }
                        }
                    }
                    current = next;
                }

                if (count != (nm_size_t)len(adjacency_list)) {
                    // cycle
                    return return_t{meta::Nothing};
                } else {
                    return return_t{result};
                }
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
        struct TOPOLOGICAL_GENERATIONS_QUEUE_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct TOPOLOGICAL_GENERATIONS_UNSUPPORTED : detail::fail_t {};
    }

    template <typename adjacency_list_t>
    struct resolve_optype<
        void, tag::topological_generations_queue_t, adjacency_list_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>) {
                using type = error::TOPOLOGICAL_GENERATIONS_QUEUE_UNSUPPORTED<adjacency_list_t>;
                return as_value_v<type>;
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
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // tag::topological_generations_queue_t

    template <typename adjacency_list_t>
    struct resolve_optype<
        void, tag::topological_generations_t, adjacency_list_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>) {
                using type = error::TOPOLOGICAL_GENERATIONS_UNSUPPORTED<adjacency_list_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_adjacency_list_v<adjacency_list_t>) {
                constexpr auto adjacency_list = to_value_v<adjacency_list_t>;
                constexpr auto m_result = network::topological_generations(adjacency_list);
                constexpr auto result = unwrap(m_result);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
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
            } else {
                using index_t = nm_index_t;
                constexpr auto NUM_NODES = len_v<adjacency_list_t>;
                [[maybe_unused]]
                constexpr auto B_NUM_NODES = max_len_v<adjacency_list_t>;
                if constexpr (NUM_NODES >= 0) {
                    using inner_t = nmtools_static_vector<index_t,NUM_NODES>;
                    using outer_t = nmtools_static_vector<inner_t,NUM_NODES>;
                    using type = outer_t;
                    return as_value_v<type>;
                } else if constexpr (B_NUM_NODES >= 0) {
                    using inner_t = nmtools_static_vector<index_t,B_NUM_NODES>;
                    using outer_t = nmtools_static_vector<inner_t,B_NUM_NODES>;
                    using type = outer_t;
                    return as_value_v<type>;
                } else {
                    using inner_t = nmtools_list<index_t>;
                    using outer_t = nmtools_list<inner_t>;
                    using type = outer_t;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_NETWORK_TOPOLOGICAL_GENERATIONS_HPP