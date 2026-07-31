#ifndef NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_LINEARIZE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_LINEARIZE_HPP

#include "nmtools/core/transform/unary_fusion.hpp"
#include "nmtools/core/transform/binary_fusion.hpp"

namespace nmtools::functional
{
    template <typename graph_t>
    constexpr auto linearize(const graph_t& graph)
    {
        auto g1 = transform_unary_fusion(graph,ct_v<-1>);
        auto g2 = transform_binary_fusion(g1,ct_v<-1>);
        return g2;
    }

    // template <typename nodes_t, typename edges_t, typename node_data_t>
    // constexpr auto get_function(const compute_graph_t<nodes_t,edges_t,node_data_t>& graph)
    template <typename compute_graph_t, enable_if_t<!is_view_v<decltype(unwrap(declval<compute_graph_t>()))>,int> = 0>
    constexpr auto get_function(const compute_graph_t& graph)
    {
        auto nodes = graph.nodes();

        constexpr auto N = len_v<decltype(nodes)>;
        auto function_nodes = template_reduce<N>([&](auto init, auto I){
            auto index = at(nodes,I);
            auto f = graph.nodes(index);
            using fun_t = decltype(f);
            if constexpr (is_num_v<fun_t> || is_pointer_v<fun_t>) {
                return init;
            } else {
                return utility::tuple_append(init,index);
            }
        },nmtools_tuple{});

        static_assert( len_v<decltype(function_nodes)> == 1 );

        return graph.nodes(at(function_nodes,ct_v<0>));
    }

    // template <typename nodes_t, typename edges_t, typename node_data_t>
    // constexpr auto get_operands(const compute_graph_t<nodes_t,edges_t,node_data_t>& graph)
    template <typename compute_graph_t, enable_if_t<!is_view_v<remove_cvref_pointer_t<decltype(unwrap(declval<compute_graph_t>()))>>,int> = 0>
    constexpr auto get_operands(const compute_graph_t& graph)
    {
        auto nodes = graph.nodes();

        constexpr auto N = len_v<decltype(nodes)>;
        auto input_nodes = template_reduce<N>([&](auto init, auto I){
            auto index = at(nodes,I);
            auto inp = graph.nodes(index);
            using inp_t = decltype(inp);
            if constexpr (is_num_v<inp_t> || is_pointer_v<inp_t>) {
                return utility::tuple_append(init,index);
            } else {
                return init;
            }
        },nmtools_tuple{});

        return template_reduce<len_v<decltype(input_nodes)>>([&](auto init, auto I){
            auto index = at(input_nodes,I);
            return utility::tuple_append(init,graph.nodes(index));
        },nmtools_tuple{});
    }
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_TRANSFORM_LINEARIZE_HPP