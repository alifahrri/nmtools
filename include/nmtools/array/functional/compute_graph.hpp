#ifndef NMTOOLS_ARRAY_FUNCTIONAL_COMPUTE_GRAPH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_COMPUTE_GRAPH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufunc/ufunc.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::functional
{
    template <typename view_t>
    struct get_compute_graph_t;

    template <typename view_t>
    constexpr auto get_compute_graph(const view_t& view)
    {
        if constexpr (meta::is_maybe_v<view_t>) {
            using view_type = meta::get_maybe_type_t<view_t>;
            using result_type = decltype(get_compute_graph(meta::declval<view_type>()));
            using return_type = nmtools_maybe<result_type>;
            if (static_cast<bool>(view)) {
                return return_type{get_compute_graph(*view)};
            } else {
                return return_type{meta::Nothing};
            }
        } else {
            using view_type = view_t;
            auto get_graph = get_compute_graph_t<view_type>{view};
            return get_graph();
        }
    } // get_compute_graph

    template <typename functor_t, typename operands_t, typename output_shape_t=nmtools_tuple<>, typename output_element_t=none_t>
    struct node_t
    {
        // TODO: assert functor_t is functor or functor composition
        // TODO: assert operands_t is tuple of integral constant

        using functor_type  = functor_t;
        using operands_type = operands_t;
        using output_shape_type   = output_shape_t;
        using output_element_type = output_element_t;

        functor_type functor;
        operands_type operands;
        output_shape_type output_shape     = {};
        output_element_type output_element = {};
    };

    template <typename functor_t, typename operands_t>
    node_t(const functor_t&, const operands_t&) -> node_t<functor_t,operands_t>;

    template <typename functor_t, typename operands_t, typename output_shape_t>
    node_t(const functor_t&, const operands_t&, const output_shape_t&) -> node_t<functor_t,operands_t,output_shape_t>;

    template <typename functor_t, typename operands_t, typename output_shape_t, typename output_element_t>
    node_t(const functor_t&, const operands_t&, const output_shape_t&, output_element_t) -> node_t<functor_t,operands_t,output_shape_t,output_element_t>;

    template <typename nodes_t=nmtools_tuple<>, typename edges_t=nmtools_tuple<>, typename node_data_t=nmtools_tuple<>>
    struct compute_graph_t : utility::ct_digraph<nodes_t,edges_t,node_data_t>
    {
        // TODO: validate that node_data_t is tuple of node_t
        using base_type = utility::ct_digraph<nodes_t,edges_t,node_data_t>;
    };

    template <template <typename...> typename view_t, typename...args_t>
    struct get_compute_graph_t<view::decorator_t<view_t,args_t...>>
    {
        using view_type = view::decorator_t<view_t,args_t...>;
        view_type view;

        constexpr auto operator()() const noexcept
        {
            auto operands = get_operands(view);
            constexpr auto operand_ids = view_type::operands_ids;

            constexpr auto N = meta::len_v<decltype(operands)>;
            auto sub_graph = meta::template_reduce<N>([&](auto graph, auto index){

                constexpr auto I = decltype(index)::value;
                const auto& operand = nmtools::get<I>(operands);
                using operand_t = meta::remove_cvref_pointer_t<decltype(operand)>;
                static_assert(
                    meta::is_pointer_v<operand_t>
                    || meta::is_num_v<operand_t>
                    || meta::is_view_v<operand_t>
                    , "expect operand to be pointer, number or view for get_compute_graph"
                );
                if constexpr (meta::is_same_view_v<view::alias_t,operand_t>) {
                    constexpr auto NODE_ID = typename operand_t::id_type{};
                    // static_assert( meta::is_pointer_v<decltype(operand)> );
                    return graph.add_node(NODE_ID,operand.array);
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
                    return result_graph;
                } else /* if constexpr (meta::is_ndarray_v<operand_t>) */ {
                    constexpr auto N_NODES = decltype(graph.size())::value;
                    constexpr auto NODE_ID = meta::ct_v<N_NODES>;
                    return graph.add_node(NODE_ID,operand);
                }
            }, compute_graph_t<>());

            // TODO: support aliasing
            constexpr auto node_id = typename view_type::id_type{};
            auto functor = get_function(view);

            auto output_shape = nmtools::shape<true>(view);
            using element_t    = meta::get_element_type_t<decltype(view)>;
            auto element_vtype = meta::as_value_v<element_t>;

            auto graph = sub_graph
                .add_node(node_id,node_t{functor,operand_ids,output_shape,element_vtype})
            ;
            return meta::template_reduce<N>([&](auto graph, auto index){
                auto operand_id = nmtools::get<decltype(index)::value>(operand_ids);
                return graph.add_edge(operand_id,node_id);
            }, graph);
        }
    }; // get_compute_graph_t

    // specialization of get_compute_graph_t for ufuncs
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
                #if 1
                if constexpr (is_broadcast_view_v<operand_t>) {
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
                } else
                #endif
                if constexpr (meta::is_same_view_v<view::alias_t,operand_t>) {
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

            auto output_shape  = nmtools::shape<true>(view);
            using element_t    = meta::get_element_type_t<decltype(view)>;
            auto element_vtype = meta::as_value_v<element_t>;

            auto graph = sub_graph
                .add_node(node_id,node_t{functor,operand_ids,output_shape,element_vtype})
            ;
            return meta::template_reduce<N>([&](auto graph, auto index){
                auto operand_id = nmtools::get<decltype(index)::value>(operand_ids);
                return graph.add_edge(operand_id,node_id);
            }, graph);
        }
    }; // get_compute_graph_t
} // namespace nmtools::functional

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/utility/to_string/common_types.hpp"

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename F, nm_size_t Arity
        , typename formatter_t
    >
    struct to_string_t<
        functional::fmap_t<F,Arity>
        , formatter_t
    > {
        using fmap_type = functional::fmap_t<F,Arity>;
        using formatter_type = formatter_t;
    
        auto operator()(const fmap_type& fmap) const noexcept
        {
            auto fmap_str = nmtools_string("");
            fmap_str = NMTOOLS_TYPENAME_TO_STRING(F);

            using mapper_type = to_string_t<meta::remove_cvref_t<decltype(fmap.fn)>,formatter_type>;
            if constexpr (meta::has_result_type_v<mapper_type>) {
                if constexpr (!meta::is_fail_v<typename mapper_type::result_type>) {
                    fmap_str = to_string(fmap.fn);
                }
            }

            auto str = nmtools_string("");

            str += "fmap(";
            str += fmap_str;
            str += ",";
            str += to_string(Arity);
            str += "_ct)";

            return str;
        }
    };

    template <typename F, typename operands_t, typename attributes_t
        , typename formatter_t
    >
    struct to_string_t<functional::functor_t<F,operands_t,attributes_t>
        , formatter_t
    > {
        using functor_type = functional::functor_t<F,operands_t,attributes_t>;
        using formatter_type = formatter_t;

        auto operator()(const functor_type& functor) const noexcept
        {
            auto fmap_str = to_string(functor.fmap,formatter_type{});

            auto attr_str = nmtools_string("");
            attr_str += "[{";
            constexpr auto N = meta::len_v<attributes_t>;
            meta::template_for<N>([&](auto index){
                attr_str += to_string(nmtools::at(functor.attributes,index),formatter_type{});
                if (index < (N-1)) {
                    attr_str += ",";
                }
            });
            attr_str += "}]";

            return fmap_str + attr_str;
        }
    };

    template <template<typename...>typename tuple, typename...functors_t, typename operands_t, auto...fmt_args>
    struct to_string_t<
        functional::functor_composition_t<tuple<functors_t...>,operands_t>, fmt_string_t<fmt_args...>, void
    > {
        using composition_type = functional::functor_composition_t<tuple<functors_t...>,operands_t>;
        using formatter_type = fmt_string_t<fmt_args...>;
        using result_type = nmtools_string;

        auto operator()(const composition_type& composition) const noexcept
        {
            auto composition_str = nmtools_string("");
            constexpr auto N = sizeof...(functors_t);
            meta::template_for<N>([&](auto index){
                composition_str += to_string(at(composition.functors,index),formatter_type{});
                if (index < (N-1)) {
                    composition_str += " * ";
                }
            });
            return composition_str;
        }
    };

    template <typename functor_t, typename operands_t, typename output_shape_t, typename output_element_t, auto...fmt_args>
    struct to_string_t<
        functional::node_t<functor_t,operands_t,output_shape_t,output_element_t>, fmt_string_t<fmt_args...>, void
    > {
        using node_type = functional::node_t<functor_t,operands_t,output_shape_t,output_element_t>;
        using formatter_type = fmt_string_t<fmt_args...>;
        using result_type = nmtools_string;

        auto operator()(const node_type& node) const noexcept
        {
            auto node_str = nmtools_string("");
            node_str += to_string(node.functor,formatter_type{});
            if constexpr (!is_none_v<output_element_t>) {
                using element_t = meta::type_t<output_element_t>;
                node_str += " | ";
                node_str += NMTOOLS_TYPENAME_TO_STRING(element_t);
            }
            if constexpr (!meta::is_same_v<output_shape_t,nmtools_tuple<>>) {
                node_str += " | ";
                node_str += to_string(node.output_shape,formatter_type{});
            }
            return node_str;
        }
    };

    // graphviz stuff
    /**********************************************************************************************************************/

    template <typename F, typename operands_t, typename attributes_t>
    struct to_string_t<functional::functor_t<F,operands_t,attributes_t>, graphviz_t>
    {
        using functor_type   = functional::functor_t<F,operands_t,attributes_t>;
        using formatter_type = graphviz_t;
        using result_type    = nmtools_string;

        auto operator()(const functor_type& functor) const noexcept
        {
            auto fmap_str = to_string(functor.fmap,utils::Compact);

            auto attr_str = nmtools_string("");
            constexpr auto N = meta::len_v<attributes_t>;
            meta::template_for<N>([&](auto index){
                attr_str += to_string(nmtools::at(functor.attributes,index),utils::Compact);
                if (index < (N-1)) {
                    attr_str += ",";
                }
            });
            auto str = nmtools_string("");
            str += "[graphviz_record_layout_open]";
            str += fmap_str;
            str += " | ";
            str += attr_str;
            str += "[graphviz_record_layout_close]";

            return str;
        }
    };

    template <typename functor_t, typename operands_t, typename output_shape_t, typename output_element_t>
    struct to_string_t<
        functional::node_t<functor_t,operands_t,output_shape_t,output_element_t>, graphviz_t, void
    > {
        using node_type = functional::node_t<functor_t,operands_t,output_shape_t,output_element_t>;
        using formatter_type = graphviz_t;
        using result_type = nmtools_string;

        auto operator()(const node_type& node) const noexcept
        {
            auto node_str = nmtools_string("");
            node_str += to_string(node.functor,utils::Graphviz);
            if constexpr (!is_none_v<output_element_t>) {
                using element_t = meta::type_t<output_element_t>;
                node_str += " | ";
                node_str += NMTOOLS_TYPENAME_TO_STRING(element_t);
            }
            if constexpr (!meta::is_same_v<output_shape_t,nmtools_tuple<>>) {
                node_str += " | ";
                node_str += to_string(node.output_shape,utils::Compact);
            }
            return node_str;
        }
    };

    template <typename nodes_t, typename edges_t, typename node_data_t>
    struct to_string_t<
        utility::ct_digraph<nodes_t,edges_t,node_data_t>, graphviz_t, void
    > {
        // using graph_type = functional::compute_graph_t<nodes_t,edges_t,node_data_t>;
        using graph_type = utility::ct_digraph<nodes_t,edges_t,node_data_t>;

        auto operator()(const graph_type& graph) const noexcept
        {
            auto graphviz = nmtools_string("digraph G");
            graphviz += "{\n";

            {
                auto out_edges = graph.out_edges();
                constexpr auto N = meta::len_v<decltype(out_edges)>;
                meta::template_for<N>([&](auto index){
                    auto out_edge = nmtools::at(out_edges,index);
                    auto src_edge = nmtools::get<0>(out_edge);
                    auto dst_edge = nmtools::get<1>(out_edge);

                    graphviz += to_string(src_edge,utils::Compact);
                    graphviz += " -> ";
                    graphviz += to_string(dst_edge,utils::Compact);
                    graphviz += "\n";
                });
            }

            {
                auto nodes = graph.nodes();
                constexpr auto N = meta::len_v<decltype(nodes)>;
                meta::template_for<N>([&](auto index){
                    auto node_id  = nmtools::at(nodes,index);
                    auto node = graph.nodes(node_id);
                    using node_t = meta::remove_cvref_pointer_t<decltype(node)>;
                    constexpr auto is_buffered =
                        (meta::is_ndarray_v<node_t> || meta::is_num_v<node_t>)
                        && !meta::is_view_v<node_t>
                    ;

                    auto node_id_str = to_string(node_id,utils::Compact);
                    graphviz += node_id_str;
                    graphviz += "[";
                    graphviz += "shape=\"record\" ";
                    if (is_buffered) {
                        graphviz += "style=\"rounded,filled\" ";
                        graphviz += "color=\"black\" ";
                        graphviz += "fillcolor=\"gray93\" ";
                    }
                    graphviz += "label=";
                    graphviz += "\"";
                    graphviz += "id: ";
                    graphviz += node_id_str;
                    graphviz += " | ";

                    auto node_string = nmtools_string("");
                    if constexpr (meta::is_ndarray_v<node_t> || meta::is_num_v<node_t> || meta::is_maybe_v<node_t>) {
                        node_string = to_string(node,utils::Compact);
                    } else {
                        node_string = to_string(node,utils::Graphviz);
                    }
                    replace_string(node_string,nmtools_string("{"),nmtools_string("[open_curl_bracket]"));
                    replace_string(node_string,nmtools_string("}"),nmtools_string("[close_curl_bracket]"));
                    replace_string(node_string,nmtools_string("<"),nmtools_string("[open_angle_bracket]"));
                    replace_string(node_string,nmtools_string(">"),nmtools_string("[close_angle_bracket]"));

                    replace_string(node_string,nmtools_string("[open_curl_bracket]"),nmtools_string("\\{"));
                    replace_string(node_string,nmtools_string("[close_curl_bracket]"),nmtools_string("\\}"));
                    replace_string(node_string,nmtools_string("[open_angle_bracket]"),nmtools_string("\\<"));
                    replace_string(node_string,nmtools_string("[close_angle_bracket]"),nmtools_string("\\>"));

                    replace_string(node_string,nmtools_string("[graphviz_record_layout_open]"),nmtools_string("{"));
                    replace_string(node_string,nmtools_string("[graphviz_record_layout_close]"),nmtools_string("}"));

                    graphviz += node_string;

                    graphviz += "\"";
                    graphviz += "]\n";
                });
            }

            graphviz += "}";

            remove_string(graphviz, nmtools_string("nmtools::"));
            remove_string(graphviz, nmtools_string("array::"));
            remove_string(graphviz, nmtools_string("std::"));
            remove_string(graphviz, nmtools_string("resolve_stride_type_t,"));
            remove_string(graphviz, nmtools_string("row_major_offset_t,"));
            remove_string(graphviz, nmtools_string("column_major_offset_t,"));

            return graphviz;
        }
    };

    template <typename nodes_t, typename edges_t, typename node_data_t>
    struct to_string_t<
        functional::compute_graph_t<nodes_t,edges_t,node_data_t>, graphviz_t, void
    > : to_string_t<utility::ct_digraph<nodes_t,edges_t,node_data_t>, graphviz_t, void>
    {};
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_FUNCTIONAL_COMPUTE_GRAPH_HPP