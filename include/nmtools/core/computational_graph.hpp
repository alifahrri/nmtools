#ifndef NMTOOLS_CORE_EXPRESSION_TREE_HPP
#define NMTOOLS_CORE_EXPRESSION_TREE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/core/node.hpp"
#include "nmtools/network/digraph.hpp"

#if 0
#include <iostream>
#endif

namespace nmtools::functional
{
    template <typename view_t>
    struct get_computational_graph_t;

    template <typename view_t>
    constexpr auto get_computational_graph(const view_t& view)
    {
        if constexpr (meta::is_maybe_v<view_t>) {
            using result_t = decltype(get_computational_graph(unwrap(view)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(view)
                ? return_t{get_computational_graph(unwrap(view))}
                : return_t{meta::Nothing}
            );
        } else if constexpr (meta::is_view_v<view_t>) {
            using view_type = view_t;
            auto getter = get_computational_graph_t<view_type>();
            return getter(view);
        }
    }

    template <template<typename...> typename view_t, typename...args_t>
    struct get_computational_graph_t<view::decorator_t<view_t,args_t...>>
    {
        using view_type = view::decorator_t<view_t,args_t...>;
        using view_id_type = typename view_type::id_type;

        constexpr auto operator()(const view_type& view) const noexcept
        {
            auto compute_node = node(view);
            auto node_id = view_id_type{};
            auto digraph = network::digraph(
                nmtools_tuple<nmtools_tuple<>>{}
                , nmtools_tuple{node_id}
                , nmtools_tuple{unwrap(compute_node)}
            );

            #if 0
            [[maybe_unused]]
            auto digraph_viz = utils::to_string(digraph,utils::Graphviz);
            std::cout << "-------------------------" << std::endl;
            std::cout << digraph_viz << std::endl;
            #endif

            auto operands = get_operands(view);
            constexpr auto operands_ids = view_type::operands_ids;

            constexpr auto N = meta::len_v<decltype(operands)>;
            auto m_digraph = meta::template_reduce<N>([&](auto init, auto I){
                const auto& operand = at(operands,I);
                const auto& operand_node = [&](){
                    if constexpr (meta::is_pointer_v<meta::remove_cvref_t<decltype(operand)>>) {
                        return node(*operand);
                    } else {
                        return node(operand);
                    }
                }();
                auto operand_id = at(operands_ids,I);
                return init
                    .add_node(operand_id,operand_node)
                    .add_edge(operand_id,node_id)
                ;
            }, digraph);

            #if 0
            [[maybe_unused]]
            auto m_digraph_viz = utils::to_string(m_digraph,utils::Graphviz);
            std::cout << "=========================" << std::endl;
            std::cout << m_digraph_viz << std::endl;
            #endif

            auto merged_graph = meta::template_reduce<N>([&](auto init, auto I){
                const auto& operand = at(operands,I);
                using operand_t = meta::remove_cvref_t<decltype(operand)>;
                if constexpr (meta::is_view_v<operand_t>
                    && !meta::is_same_view_v<view::alias_t,operand_t>
                ) {
                    auto subgraph = get_computational_graph(operand);
                    auto composed = network::compose(init,subgraph);

                    #if 0
                    auto init_viz = utils::to_string(init,utils::Graphviz);
                    std::cout << "init+++++++++++++++++++++" << std::endl;
                    std::cout << init_viz << std::endl;

                    auto subgraph_viz = utils::to_string(subgraph,utils::Graphviz);
                    std::cout << "subgraph+++++++++++++++++" << std::endl;
                    std::cout << subgraph_viz << std::endl;

                    auto composed_viz = utils::to_string(composed,utils::Graphviz);
                    std::cout << "composed+++++++++++++++++" << std::endl;
                    std::cout << composed_viz << std::endl;
                    #endif

                    return composed;
                } else {
                    return init;
                }
            }, m_digraph);

            #if 0
            [[maybe_unused]]
            auto merged_digraph_viz = utils::to_string(merged_graph,utils::Graphviz);
            std::cout << "#########################" << std::endl;
            std::cout << merged_digraph_viz << std::endl;
            #endif

            return merged_graph;
        }
    };
} // nmtools::functional

namespace nmtools::meta
{
    template <typename adjacency_list_t
        , typename node_ids_t
        , typename node_attributes_t
        , typename edge_attributes_t>
    struct to_value<
        network::digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t>
    > {
        using digraph_type = network::digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t>;

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
                return network::digraph(adjacency_list,node_ids,attributes);
            }
        }();
    };
}

#endif // NMTOOLS_CORE_EXPRESSION_TREE_HPP