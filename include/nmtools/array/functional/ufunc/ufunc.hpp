#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNC_UFUNC_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNC_UFUNC_HPP

#include "nmtools/array/view/ufunc/ufunc.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/array/functional/functor.hpp"

namespace nmtools::functional
{
    template <typename...args_t>
    struct get_function_composition_t<
        view::decorator_t<
            view::ufunc_t, args_t...
        >
    > {
        using view_type = view::decorator_t<view::ufunc_t, args_t...>;
        using view_id_type = typename view_type::id_type;
        view_type view;

        constexpr auto operator()() const noexcept 
        {
            auto function = get_function(view);
            auto operands = get_operands(view);
            static_assert( !meta::is_fail_v<decltype(operands)> );
            constexpr auto N = view_type::arity;
            auto composition = meta::template_reduce<N>([&](auto init, auto index){
                constexpr auto I = decltype(index)::value;
                constexpr auto r_index = meta::ct_v<(N-1)-I>;
                const auto& operand = at(operands,r_index);
                using operand_t = meta::remove_pointer_t<meta::remove_cvref_t<decltype(operand)>>;
                static_assert(
                    (meta::is_view_v<operand_t>)
                    || ((meta::is_num_v<operand_t> || meta::is_ndarray_v<operand_t>)
                        && !meta::is_view_v<operand_t>
                    )
                );
                if constexpr (meta::is_same_view_v<view::broadcast_to_t,operand_t>) {
                    // TODO: refactor ufuncs
                    // skip broadcasting
                    const auto& sub_operand = at(get_operands(operand),meta::ct_v<0>);
                    static_assert( !meta::is_fail_v<decltype(sub_operand)> );
                    using sub_operand_t = meta::remove_pointer_t<meta::remove_cvref_t<decltype(sub_operand)>>;
                    if constexpr (meta::is_view_v<sub_operand_t>) {
                        return init * get_function_composition(sub_operand);
                    } else if constexpr (
                        (meta::is_num_v<sub_operand_t> || meta::is_ndarray_v<sub_operand_t>)
                        && !meta::is_view_v<sub_operand_t>
                    ) {
                        return init;
                    }
                } else if constexpr (meta::is_view_v<operand_t>) {
                    return init * get_function_composition(operand);
                } else if constexpr (
                    (meta::is_num_v<operand_t> || meta::is_ndarray_v<operand_t>)
                    && !meta::is_view_v<operand_t>
                ) {
                    return init;
                }
            }, function);
            return composition;
        }
    };

    template <typename...args_t>
    struct get_compute_graph_t<
        view::decorator_t<
            view::ufunc_t, args_t...
        >
    > {
        using view_type = view::decorator_t<view::ufunc_t, args_t...>;
        using view_id_type = typename view_type::id_type;
        view_type view;

        constexpr auto operator()() const noexcept
        {
            auto operands = get_operands(view);

            constexpr auto N = meta::len_v<decltype(operands)>;
            auto sub_graph_and_ids = meta::template_reduce<N>([&](auto graph_and_ids, auto index){
                auto graph = nmtools::get<0>(graph_and_ids);
                auto operand_ids = nmtools::get<1>(graph_and_ids);

                constexpr auto I = decltype(index)::value;
                const auto& operand = nmtools::get<I>(operands);
                using operand_t = meta::remove_cvref_pointer_t<decltype(operand)>;
                static_assert(
                    meta::is_pointer_v<operand_t>
                    || meta::is_num_v<operand_t>
                    || meta::is_view_v<operand_t>
                    , "expect operand to be pointer, number or view for get_compute_graph"
                );
                if constexpr (meta::is_same_view_v<view::broadcast_to_t,operand_t>) {
                    // broadccast_to has exactly 1 operand
                    // effectively skip broadcast
                    // TODO: refactor functional ufuncs
                    auto sub_operand = at(get_operands(operand),meta::ct_v<0>);
                    using sub_operand_type = meta::remove_cvref_pointer_t<decltype(sub_operand)>;
                    if constexpr ((meta::is_ndarray_v<sub_operand_type> || meta::is_num_v<sub_operand_type>)
                        && !meta::is_view_v<sub_operand_type>
                    ) {
                        // TODO: read nodeid from view's operands_ids static member variable
                        constexpr auto N_NODES = decltype(graph.size())::value;
                        constexpr auto NODE_ID = meta::ct_v<N_NODES>;
                        return nmtools_tuple{
                            graph.add_node(NODE_ID,sub_operand)
                            , utility::tuple_append(operand_ids,NODE_ID)
                        };
                    } else if constexpr (meta::is_same_view_v<view::alias_t,sub_operand_type>) {
                        constexpr auto NODE_ID = typename sub_operand_type::id_type{};
                        return nmtools_tuple{
                            graph.add_node(NODE_ID,sub_operand.array)
                            , utility::tuple_append(operand_ids,NODE_ID)
                        };
                    } else {
                        auto sub_id = typename sub_operand_type::id_type{};
                        auto node_i = graph.nodes(sub_id);
                        constexpr auto has_node = !meta::is_fail_v<decltype(node_i)>;
                        // skip adding nodes if has already exists, but still add edge
                        if constexpr (has_node) {
                            return nmtools_tuple{
                                graph
                                , utility::tuple_append(operand_ids,sub_id)
                            };
                        } else {
                            // MERGE Graph
                            auto sub_graph = get_compute_graph(sub_operand);
                            auto sub_keys = sub_graph.digraph.keys();
                            constexpr auto N_SUB = meta::len_v<decltype(sub_keys)>;
                            auto result_graph = meta::template_reduce<N_SUB>([&](auto g, auto index){
                                auto node_id = nmtools::get<decltype(index)::value>(sub_keys);
                                auto node = sub_graph.nodes(node_id);
                                auto out_edges = sub_graph.out_edges(node_id);
                                constexpr auto N_OUT = meta::len_v<decltype(out_edges)>;
                                return meta::template_reduce<N_OUT>([&](auto g, auto out_idx){
                                    auto out_edge = nmtools::get<decltype(out_idx)::value>(out_edges);
                                    return g.add_edge(node_id,out_edge);
                                }, g.add_node(node_id,node));
                            }, graph);
                            return nmtools_tuple{
                                result_graph
                                , utility::tuple_append(operand_ids,sub_id)
                            };
                        }
                    }
                } else if constexpr (meta::is_same_view_v<view::alias_t,operand_t>) {
                    constexpr auto NODE_ID = typename operand_t::id_type{};
                    // static_assert( meta::is_pointer_v<decltype(operand)> );
                    return nmtools_tuple{
                        graph.add_node(NODE_ID,operand.array)
                        , utility::tuple_append(operand_ids,NODE_ID)
                    };
                } else if constexpr (meta::is_view_v<operand_t>) {
                    auto sub_graph = get_compute_graph(operand);
                    auto sub_keys = sub_graph.digraph.keys();
                    constexpr auto N_SUB = meta::len_v<decltype(sub_keys)>;
                    // MERGE Graph
                    auto result_graph = meta::template_reduce<N_SUB>([&](auto g, auto index){
                        auto node_id = nmtools::get<decltype(index)::value>(sub_keys);
                        auto node = sub_graph.nodes(node_id);
                        auto out_edges = sub_graph.out_edges(node_id);
                        constexpr auto N_OUT = meta::len_v<decltype(out_edges)>;
                        return meta::template_reduce<N_OUT>([&](auto g, auto out_idx){
                            auto out_edge = nmtools::get<decltype(out_idx)::value>(out_edges);
                            return g.add_edge(node_id,out_edge);
                        }, g.add_node(node_id,node));
                    }, graph);
                    auto sub_id = typename operand_t::id_type{};
                    return nmtools_tuple{
                        result_graph
                        , utility::tuple_append(operand_ids,sub_id)
                    };
                } else /* if constexpr (meta::is_ndarray_v<operand_t>) */ {
                    constexpr auto N_NODES = decltype(graph.size())::value;
                    constexpr auto NODE_ID = meta::ct_v<N_NODES>;
                    return nmtools_tuple{
                        graph.add_node(NODE_ID,operand)
                        , utility::tuple_append(operand_ids,NODE_ID)
                    };
                }
            }, nmtools_tuple{compute_graph_t<>(),nmtools_tuple<>{}});

            auto sub_graph = nmtools::get<0>(sub_graph_and_ids);
            auto operand_ids = nmtools::get<1>(sub_graph_and_ids);

            constexpr auto node_id = view_id_type{};
            auto functor = get_function(view);

            auto graph = sub_graph
                .add_node(node_id,node_t{functor,operand_ids})
            ;
            return meta::template_reduce<N>([&](auto graph, auto index){
                auto operand_id = nmtools::get<decltype(index)::value>(operand_ids);
                return graph.add_edge(operand_id,node_id);
            }, graph);
        }
    };
}

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNC_UFUNC_HPP