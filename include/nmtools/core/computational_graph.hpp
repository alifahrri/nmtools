#ifndef NMTOOLS_CORE_COPUTATIONAL_GRAPH_HPP
#define NMTOOLS_CORE_COPUTATIONAL_GRAPH_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/core/node.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/network/multi_digraph.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"


namespace nmtools::functional
{
    template <typename view_t>
    struct get_computational_graph_t;

    template <typename view_t>
    constexpr auto get_computational_graph(const view_t& view)
    {
        if constexpr (is_maybe_v<view_t>) {
            using result_t = decltype(get_computational_graph(unwrap(view)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(view)
                ? return_t{get_computational_graph(unwrap(view))}
                : return_t{Nothing}
            );
        } else if constexpr (is_either_v<view_t>) {
            using left_t   = decltype(get_computational_graph(*get_left(&view)));
            using right_t  = decltype(get_computational_graph(*get_right(&view)));
            using return_t = conditional_t<is_same_v<left_t,right_t>,left_t,nmtools_either<left_t,right_t>>;
            if (auto l_ptr = get_left(&view)) {
                return return_t{get_computational_graph(*l_ptr)};
            } else {
                auto r_ptr = get_right(&view);
                return return_t{get_computational_graph(*r_ptr)};
            }
        } else if constexpr (is_view_v<view_t>) {
            auto tree  = get_computational_tree(view);
            auto graph = cse(tree);
            return graph;
        }
    }
} // nmtools::functional

namespace nmtools::meta
{
    // TODO: move somehere else?
    template <typename adjacency_list_t
        , typename node_ids_t
        , typename node_attributes_t
        , typename edge_attributes_t
        , typename multi_t>
    struct to_value<
        network::base_digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t,multi_t>
    > {
        using digraph_type = network::base_digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t,multi_t>;

        static constexpr auto value = [](){
            if constexpr (!is_constant_adjacency_list_v<adjacency_list_t>
                || !(is_constant_index_array_v<node_ids_t> || is_none_v<node_ids_t>)
            ) {
                using type = error::TO_VALUE_UNSUPPORTED<digraph_type>;
                return type{};
            } else {
                // TODO: support edge attributes
                static_assert( is_none_v<edge_attributes_t> );

                constexpr auto adjacency_list = to_value_v<adjacency_list_t>;
                constexpr auto node_ids = to_value_v<node_ids_t>;
                // assume node attirbutes
                constexpr auto N = len_v<node_attributes_t>;
                using dst_node_attributes_t = nmtools_array<functional::Node<>,N>;
                auto attributes = dst_node_attributes_t{};
                using nmtools::at;
                template_for<N>([&](auto index){
                    constexpr auto I = decltype(index)::value;
                    using type_i = at_t<node_attributes_t,I>;
                    auto node = to_value_v<type_i>;
                    at(attributes,I) = node;
                });
                if constexpr (multi_t::value) {
                    return network::multi_digraph(adjacency_list,node_ids,attributes);
                } else {
                    return network::digraph(adjacency_list,node_ids,attributes);
                }
            }
        }();
    };
}

#endif // NMTOOLS_CORE_COPUTATIONAL_GRAPH_HPP