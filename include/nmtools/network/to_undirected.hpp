#ifndef NMTOOLS_NETWORK_TO_UNDIRECTED_HPP
#define NMTOOLS_NETWORK_TO_UNDIRECTED_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/compute_offset.hpp"
#include "nmtools/index/compute_strides.hpp"

namespace nmtools::tag
{
    struct to_undirected_t {};
}

namespace nmtools::network
{
    template <typename adjacency_list_t>
    constexpr auto to_undirected(const adjacency_list_t& adj_list)
    {
        if constexpr (is_maybe_v<adjacency_list_t>) {
            using result_t = decltype(to_undirected(unwrap(adj_list)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(adj_list)
                ? return_t{to_undirected(unwrap(adj_list))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = resolve_optype_t<tag::to_undirected_t,adjacency_list_t>;

            if constexpr (!is_fail_v<result_t>
                && !is_constant_adjacency_list_v<result_t>
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

                auto matrix_vtype = [](){
                    using bool_t = nm_bool_t;
                    [[maybe_unused]]
                    constexpr auto MAX_NODES = max_len_v<adjacency_list_t>;
                    constexpr auto NUM_NODES = len_v<adjacency_list_t>;
                    if constexpr (NUM_NODES > 0) {
                        using type = nmtools_array<bool_t,NUM_NODES*NUM_NODES>;
                        return as_value_v<type>;
                    } else if constexpr (MAX_NODES >= 0) {
                        using type = nmtools_static_vector<bool_t,MAX_NODES*MAX_NODES>;
                        return as_value_v<type>;
                    } else {
                        // TODO: use small vector
                        using type = nmtools_list<bool_t>;
                        return as_value_v<type>;
                    }
                }();
                using matrix_t = type_t<decltype(matrix_vtype)>;

                auto connected = matrix_t {};
                if constexpr (is_resizable_v<matrix_t>) {
                    connected.resize(num_nodes*num_nodes);
                }
                auto m_shape  = nmtools_array{num_nodes,num_nodes};
                auto m_stride = index::compute_strides(m_shape);
                auto offset   = [&](auto i, auto j){
                    return index::compute_offset(nmtools_array{i,j},m_shape,m_stride);
                };

                for (nm_size_t i=0; i<(nm_size_t)len(connected); i++) {
                    connected[i] = false;
                }

                auto valid = true;
                for (nm_size_t i=0; (i<(nm_size_t)num_nodes) && valid; i++) {
                    const auto& neighbors = at(adj,i);
                    for (nm_size_t j=0; (j<(nm_size_t)len(neighbors)) && valid; j++) {
                        auto v = (nm_size_t)at(neighbors,j);
                        if (v >= (nm_size_t)num_nodes) {
                            valid = false;
                        } else {
                            at(connected,offset(i,v)) = true;
                            at(connected,offset(v,i)) = true;
                        }
                    }
                }

                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    auto& row = at(result,i);
                    for (nm_size_t j=0; j<(nm_size_t)num_nodes; j++) {
                        if (at(connected,offset(i,j))) {
                            row.push_back(j);
                        }
                    }
                }

                using return_t = nmtools_maybe<result_t>;
                return valid ? return_t{result} : return_t{meta::Nothing};
            } else {
                auto result = result_t {};
                return result;
            }
        }
    } // to_undirected
} // namespace nmtools::network

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct TO_UNDIRECTED_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct TO_UNDIRECTED_INVALID : detail::fail_t {};
    }

    template <typename adjacency_list_t>
    struct resolve_optype<
        void, tag::to_undirected_t, adjacency_list_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>) {
                using type = error::TO_UNDIRECTED_UNSUPPORTED<adjacency_list_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_adjacency_list_v<adjacency_list_t>) {
                constexpr auto adjacency_list = to_value_v<adjacency_list_t>;
                constexpr auto m_result = network::to_undirected(adjacency_list);
                if constexpr (has_value(m_result)) {
                    constexpr auto result = unwrap(m_result);
                    using nmtools::at, nmtools::len;
                    return template_reduce<len(result)>([&](auto init, auto index){
                        using init_t = type_t<decltype(init)>;
                        constexpr auto I = decltype(index)::value;
                        auto inner_vtype = template_reduce<len(at(result,I))>([&](auto init, auto index){
                            using init_t = type_t<decltype(init)>;
                            constexpr auto J = decltype(index)::value;
                            using type = append_type_t<init_t,ct<at(at(result,I),J)>>;
                            return as_value_v<type>;
                        }, as_value_v<nmtools_tuple<>>);
                        using inner_t = type_t<decltype(inner_vtype)>;
                        using type = append_type_t<init_t,inner_t>;
                        return as_value_v<type>;
                    }, as_value_v<nmtools_tuple<>>);
                } else {
                    using type = error::TO_UNDIRECTED_INVALID<adjacency_list_t>;
                    return as_value_v<type>;
                }
            } else {
                constexpr auto NUM_NODES = len_v<adjacency_list_t>;
                constexpr auto B_NUM_NODES = max_len_v<adjacency_list_t>;

                // TODO: deduce index type from adjacency_list_t
                using index_t = nm_index_t;

                if constexpr (NUM_NODES >= 0) {
                    using inner_type = nmtools_static_vector<index_t,NUM_NODES>;
                    using outer_type = nmtools_array<inner_type,NUM_NODES>;
                    using type = outer_type;
                    return as_value_v<type>;
                } else if constexpr (B_NUM_NODES >= 0) {
                    using inner_type = nmtools_static_vector<index_t,B_NUM_NODES>;
                    using outer_type = nmtools_static_vector<inner_type,B_NUM_NODES>;
                    using type = outer_type;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using inner_type = nmtools_list<index_t>;
                    using outer_type = nmtools_list<inner_type>;
                    using type = outer_type;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // tag::to_undirected_t
} // namespace nmtools::meta

#endif // NMTOOLS_NETWORK_TO_UNDIRECTED_HPP
