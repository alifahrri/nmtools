#ifndef NMTOOLS_NETWORK_INTERVAL_GRAPH_HPP
#define NMTOOLS_NETWORK_INTERVAL_GRAPH_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"

namespace nmtools::tag
{
    struct interval_graph_t {};
}

namespace nmtools::network
{
    // Live interval graph of the half-open intervals [at(start,i), at(end,i)).
    template <typename start_t, typename end_t>
    constexpr auto interval_graph([[maybe_unused]] const start_t& start, [[maybe_unused]] const end_t& end)
    {
        using result_t = resolve_optype_t<tag::interval_graph_t,start_t,end_t>;

        if constexpr (is_fail_v<result_t>
            || is_constant_adjacency_list_v<result_t>
        ) {
            // constant input: the folded values live in the type, see the
            // resolve specialization below
            return result_t {};
        } else {
            using return_t = nmtools_maybe<result_t>;

            auto num_nodes = len(start);

            auto result = result_t {};

            if ((nm_size_t)num_nodes != (nm_size_t)len(end)) {
                return return_t{meta::Nothing};
            }

            for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                if ((nm_size_t)at(start,i) > (nm_size_t)at(end,i)) {
                    return return_t {meta::Nothing};
                }
            }

            if constexpr (is_resizable_v<result_t>) {
                result.resize(num_nodes);
            }

            for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                for (nm_size_t j=i+1; j<(nm_size_t)num_nodes; j++) {
                    auto lo = (nm_size_t)at(start,i) > (nm_size_t)at(start,j) ? at(start,i) : at(start,j);
                    auto hi = (nm_size_t)at(end,i) < (nm_size_t)at(end,j) ? at(end,i) : at(end,j);
                    if ((nm_size_t)lo < (nm_size_t)hi) {
                        result[i].push_back(j);
                        result[j].push_back(i);
                    }
                }
            }

            return return_t {result};
        }
    } // interval_graph
} // namespace nmtools::network

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct INTERVAL_GRAPH_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct INTERVAL_GRAPH_INVALID : detail::fail_t {};
    }

    template <typename start_t, typename end_t>
    struct resolve_optype<
        void, tag::interval_graph_t, start_t, end_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<start_t> || !is_index_array_v<end_t>) {
                using type = error::INTERVAL_GRAPH_UNSUPPORTED<start_t,end_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<start_t>
                && is_constant_index_array_v<end_t>
            ) {
                if constexpr ((len_v<start_t> == 0) && (len_v<end_t> == 0)) {
                    // no intervals: nothing to validate, empty adjacency list
                    using type = nmtools_tuple<>;
                    return as_value_v<type>;
                } else if constexpr (len_v<start_t> != len_v<end_t>) {
                    using type = error::INTERVAL_GRAPH_INVALID<start_t,end_t>;
                    return as_value_v<type>;
                } else {
                    constexpr auto start_values = to_value_v<start_t>;
                    constexpr auto end_values   = to_value_v<end_t>;

                    constexpr auto is_valid = [](auto start_values, auto end_values){
                        using nmtools::at, nmtools::len;
                        bool valid = true;
                        for (nm_size_t i=0; i<(nm_size_t)len(start_values); i++) {
                            valid = valid && ((nm_index_t)at(start_values,i) <= (nm_index_t)at(end_values,i));
                        }
                        return valid;
                    }(start_values, end_values);

                    if constexpr (!is_valid) {
                        using type = error::INTERVAL_GRAPH_INVALID<start_t,end_t>;
                        return as_value_v<type>;
                    } else {
                        constexpr auto m_result = network::interval_graph(start_values, end_values);
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
                            using type = error::INTERVAL_GRAPH_INVALID<start_t,end_t>;
                            return as_value_v<type>;
                        }
                    }
                }
            } else {
                // node i has at most num_nodes-1 neighbours, so a row never
                // grows past num_nodes
                constexpr auto NUM_NODES = len_v<start_t>;
                [[maybe_unused]]
                constexpr auto B_NUM_NODES = max_len_v<start_t>;

                // TODO: deduce index type from start_t
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
    }; // tag::interval_graph_t
} // namespace nmtools::meta

#endif // NMTOOLS_NETWORK_INTERVAL_GRAPH_HPP
