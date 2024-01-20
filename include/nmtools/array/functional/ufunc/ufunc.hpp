#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNC_UFUNC_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNC_UFUNC_HPP

#include "nmtools/array/view/ufunc/ufunc.hpp"
#include "nmtools/array/functional/functor.hpp"

namespace nmtools::functional
{
    // NOTE: special case for ufunc, must bypast get_graph for broadcast_to
    // TODO: revisit and maybe refactor (using base class for example)
    template <typename...args_t>
    struct get_graph_t<
        view::decorator_t<
            view::ufunc_t, args_t...
        >
    >
    {
        using view_type = view::decorator_t<view::ufunc_t,args_t...>;
        view_type view;

        constexpr auto operator()() const noexcept
        {
            auto operands = get_operands(view);

            constexpr auto N = meta::len_v<decltype(operands)>;

            using empty_graph_t [[maybe_unused]] = graph_t<nmtools_tuple<>,nmtools_tuple<>>;

            auto append_alias = [](const auto& sub_graph_pack){
                auto node = nmtools_tuple{alias};
                auto edge = nmtools_tuple<nmtools_tuple<>>{nmtools_tuple<>{}};
                auto sub_graph = graph_t{node,edge};
                return utility::tuple_append(sub_graph_pack,sub_graph);
            };

            auto sub_graph_pack = meta::template_reduce<N>([&](auto sub_graph_pack, auto index){
                auto operand = at(operands,index);
                using operand_t = meta::remove_cvref_pointer_t<decltype(operand)>;
                static_assert( !meta::is_fail_v<operand_t> );

                if constexpr (meta::is_same_view_v<view::alias_t,operand_t>) {

                } else if constexpr (
                    meta::is_view_v<operand_t>
                    && !meta::is_same_view_v<view::broadcast_to_t,operand_t>
                ) {
                    auto sub_graph = get_graph(operand);
                    return utility::tuple_append(sub_graph_pack,sub_graph);
                } else if constexpr (
                    meta::is_same_view_v<view::broadcast_to_t,operand_t>
                ) {
                    // broadccast_to has exactly 1 operand
                    auto sub_operand = at(get_operands(operand),meta::ct_v<0>);
                    if constexpr (meta::is_view_v<decltype(sub_operand)>) {
                        auto sub_graph = get_graph(sub_operand);
                        return utility::tuple_append(sub_graph_pack,sub_graph);
                    } else {
                        return append_alias(sub_graph_pack);
                    }
                } else if constexpr (
                    meta::is_ndarray_v<operand_t>
                    && !meta::is_view_v<operand_t>
                ) {
                    return append_alias(sub_graph_pack);
                }
            }, nmtools_tuple<>{});

            auto node = get_function(view);

            using sub_graph_pack_t = decltype(sub_graph_pack);
            auto edge = meta::template_reduce<N>([](auto init, auto index){
                constexpr auto r_index = N - (index+1);
                if constexpr ((r_index+1) == N) {
                    return utility::tuple_cat(nmtools_tuple{meta::ct_v<(int)-1>},init);
                } else {
                    using sub_graph_t = meta::at_t<sub_graph_pack_t,r_index+1>;
                    using sub_nodes_t = typename sub_graph_t::nodes_type;
                    constexpr auto distance = nmtools::at(init,meta::ct_v<0>) - (int)meta::len_v<sub_nodes_t>;
                    return utility::tuple_cat(nmtools_tuple{meta::ct_v<(int)distance>},init);
                }
            }, nmtools_tuple<>{});

            // merge sub_graphs
            auto merged_nodes = meta::template_reduce<N>([&](auto init, auto index){
                const auto& sub_graph = at(sub_graph_pack,index);
                return utility::tuple_cat(init,sub_graph.nodes);
            }, nmtools_tuple<>{});

            auto merged_edges = meta::template_reduce<N>([&](auto init, auto index){
                const auto& sub_graph = at(sub_graph_pack,index);
                return utility::tuple_cat(init,sub_graph.edges);
            }, nmtools_tuple<>{});

            auto new_nodes = utility::tuple_append(merged_nodes,node);
            auto new_edges = utility::tuple_append(merged_edges,edge);

            return graph_t{
                /*nodes*/new_nodes,
                /*edges*/new_edges
            };
        }
    };
}

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNC_UFUNC_HPP