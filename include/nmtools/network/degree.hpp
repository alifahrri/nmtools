#ifndef NMTOOLS_NETWORK_DEGREE_HPP
#define NMTOOLS_NETWORK_DEGREE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/network/predecessors.hpp"

namespace nmtools::tag
{
    struct degree_t {};
}

namespace nmtools::network
{
    template <typename adjacency_list_t>
    constexpr auto degree(const adjacency_list_t& adj_list)
    {
        if constexpr (is_maybe_v<adjacency_list_t>) {
            using result_t = decltype(degree(unwrap(adj_list)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adj_list)
                ? return_t{degree(unwrap(adj_list))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = resolve_optype_t<tag::degree_t,adjacency_list_t>;

            if constexpr (!is_fail_v<result_t>
                && !is_constant_index_array_v<result_t>
            ) {
                decltype(auto) adj = [&]() -> decltype(auto) {
                    if constexpr (is_constant_adjacency_list_v<adjacency_list_t>) {
                        return to_value_v<adjacency_list_t>;
                    } else {
                        return (adj_list);
                    }
                }();

                auto num_nodes = len(adj);

                auto result = result_t {};
                if constexpr (is_resizable_v<result_t>) {
                    result.resize(num_nodes);
                }
                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    at(result,i) = 0;
                }

                auto valid = true;

                auto flag_list_vtype = [](){
                    constexpr auto MAX_NODES = max_len_v<adjacency_list_t>;
                    if constexpr (MAX_NODES >= 0) {
                        using type = nmtools_static_vector<nm_bool_t,MAX_NODES>;
                        return as_value_v<type>;
                    } else {
                        // TODO: use small vector
                        using type = nmtools_list<nm_bool_t>;
                        return as_value_v<type>;
                    }
                }();
                using flag_list_t = type_t<decltype(flag_list_vtype)>;

                // TODO: propagate error
                auto m_preds = predecessors(adj);

                valid &= has_value(m_preds);

                for (nm_size_t i=0; (i<(nm_size_t)num_nodes) && valid; i++) {
                    auto preds = unwrap(m_preds);
                    auto seen = flag_list_t {};
                    if constexpr (is_resizable_v<flag_list_t>) {
                        seen.resize(num_nodes);
                    }
                    auto d = 0ul;
                    auto self_loop = false;

                    auto f = [&](auto v) {
                        if ((nm_size_t)v >= (nm_size_t)num_nodes) {
                            valid = false;
                        } else if ((nm_size_t)v == (nm_size_t)i) {
                            self_loop = true;
                        } else if (!seen[v]) {
                            seen[v] = true;
                            d += 1;
                        }
                    };
                    for (const auto& v : at(adj,i)) {
                        f(v);
                    }
                    for (const auto& v : at(preds,i)) {
                        f(v);
                    }
                    result[i] = d + (self_loop ? 2 : 0);
                }

                using return_t = nmtools_maybe<result_t>;
                return valid ? return_t{result} : return_t{meta::Nothing};
            } else {
                auto result = result_t {};
                return result;
            }
        }
    } // degree
} // namespace nmtools::network

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct DEGREE_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct DEGREE_INVALID : detail::fail_t {};
    }

    template <typename adjacency_list_t>
    struct resolve_optype<
        void, tag::degree_t, adjacency_list_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>) {
                using type = error::DEGREE_UNSUPPORTED<adjacency_list_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_adjacency_list_v<adjacency_list_t>) {
                constexpr auto adjacency_list = to_value_v<adjacency_list_t>;
                constexpr auto m_result = network::degree(adjacency_list);
                if constexpr (has_value(m_result)) {
                    constexpr auto result = unwrap(m_result);
                    using nmtools::at, nmtools::len;
                    return template_reduce<len(result)>([&](auto init, auto index){
                        using init_t = type_t<decltype(init)>;
                        constexpr auto I = decltype(index)::value;
                        using type = append_type_t<init_t,ct<at(result,I)>>;
                        return as_value_v<type>;
                    }, as_value_v<nmtools_tuple<>>);
                } else {
                    // NOTE: follows the TO_UNDIRECTED_INVALID decision, an invalid
                    // constant graph is a compile time error instead of a value
                    using type = error::DEGREE_INVALID<adjacency_list_t>;
                    return as_value_v<type>;
                }
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
    }; // tag::degree_t
} // namespace nmtools::meta

#endif // NMTOOLS_NETWORK_DEGREE_HPP
