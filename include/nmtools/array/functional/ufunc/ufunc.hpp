#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNC_UFUNC_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNC_UFUNC_HPP

#include "nmtools/array/view/ufunc/ufunc.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/utils/to_string/common_types.hpp"

#include "nmtools/utils/isequal.hpp"

namespace nmtools::functional::fun
{
    template <typename op_t=none_t>
    struct broadcast_binary_ufunc
    {
        template <typename...args_t>
        constexpr auto operator()(const args_t&...args) const
        {
            if constexpr (is_none_v<op_t>) {
                return view::broadcast_binary_ufunc(args...);
            } else {
                return view::broadcast_binary_ufunc(op_t{},args...);
            }
        }
    };

    template <typename op_t=none_t>
    struct binary_ufunc
    {
        template <typename...args_t>
        constexpr auto operator()(const args_t&...args) const
        {
            if constexpr (is_none_v<op_t>) {
                return view::binary_ufunc(args...);
            } else {
                return view::binary_ufunc(op_t{},args...);
            }
        }
    };

    template <typename op_t=none_t>
    struct unary_ufunc
    {
        using op_type = op_t;

        template <typename...args_t>
        constexpr auto operator()(const args_t&...args) const
        {
            if constexpr (is_none_v<op_type>) {
                return view::unary_ufunc(args...);
            } else {
                return view::unary_ufunc(op_type{},args...);
            }
        }
    };
} // namespace nmtools::functional::fun

namespace nmtools::utils
{
    using functional::fun::unary_ufunc;
    using functional::unary_fmap_t;
    using functional::functor_t;

    template <
        typename F, typename lhs_operands_t, typename lhs_attributes_t
        , typename G, typename rhs_operands_t, typename rhs_attributes_t>
    constexpr auto isequal(
        [[maybe_unused]] const functor_t<unary_fmap_t<unary_ufunc<F>>,lhs_operands_t,lhs_attributes_t>& lhs
        , [[maybe_unused]] const functor_t<unary_fmap_t<unary_ufunc<G>>,rhs_operands_t,rhs_attributes_t>& rhs
    )
        -> meta::enable_if_t<(is_none_v<F> || is_none_v<G>) && !meta::is_same_v<F,G>,bool>
    {
        // unfortunately the easiest way to compare is getting the view and extract the function composition
        using dummy_i_array_t = nmtools_array<int,1>;
        using dummy_f_array_t = nmtools_array<float,1>;
        constexpr auto can_call_float = meta::expression_check_v<meta::expr::callable,decltype(lhs),dummy_f_array_t>;
        using dummy_type = meta::conditional_t<
            can_call_float, dummy_f_array_t, dummy_i_array_t
        >;
        auto dummy_array = dummy_type{1};

        // the following should have same op, regardless how many attributes configuration
        auto lhs_view = lhs (dummy_array);
        auto rhs_view = rhs (dummy_array);

        // return isequal(lhs_view.attributes(),rhs_view.attributes());
        return lhs_view.attributes() == rhs_view.attributes();
    }
} // namespace nmtools::utils

namespace nmtools::functional
{
    constexpr inline auto unary_ufunc  = functor_t(unary_fmap_t<fun::unary_ufunc<>>{});
    constexpr inline auto binary_ufunc = functor_t(binary_fmap_t<fun::binary_ufunc<>>{});
    constexpr inline auto broadcast_binary_ufunc = functor_t(binary_fmap_t<fun::broadcast_binary_ufunc<>>{});

    template <typename op_t, typename lhs_t, typename rhs_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, op_t, lhs_t, rhs_t
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, op_t, lhs_t, rhs_t
        >;

        view_type view;
        constexpr auto operator()() const noexcept
        {
            return broadcast_binary_ufunc[view.attributes()];
        }
    };

    template <typename op_t, typename array_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, op_t, array_t
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, op_t, array_t
        >;

        view_type view;
        constexpr auto operator()() const noexcept
        {
            return unary_ufunc[view.attributes()];
        }
    };
} // namespace nmtools::functional

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

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename op_t>
    struct to_string_t<
        functional::fun::unary_ufunc<op_t>, none_t
    > {
        using ufunc_type = functional::fun::unary_ufunc<op_t>;

        auto operator()(const ufunc_type&) const noexcept
        {
            auto op_str = nmtools_string("");
            
            if constexpr (!is_none_v<op_t>) {
                op_str = to_string(op_t{});

                if (op_str.empty()) {
                    op_str += NMTOOLS_TYPENAME_TO_STRING(op_t);
                }
            }

            auto str = nmtools_string("");

            str += "ufunc(";
            str += op_str;
            str += ")";

            return str;
        }
    };

    template <typename op_t>
    struct to_string_t<
        functional::fun::binary_ufunc<op_t>, none_t
    > {
        using ufunc_type = functional::fun::binary_ufunc<op_t>;

        auto operator()(const ufunc_type&) const noexcept
        {
            auto op_str = nmtools_string("");
            
            if constexpr (!is_none_v<op_t>) {
                op_str = to_string(op_t{});

                if (op_str.empty()) {
                    op_str += NMTOOLS_TYPENAME_TO_STRING(op_t);
                }
            }

            auto str = nmtools_string("");

            str += "ufunc(";
            str += op_str;
            str += ")";

            return str;
        }
    };

    template <typename op_t>
    struct to_string_t<
        functional::fun::broadcast_binary_ufunc<op_t>, none_t
    > {
        using ufunc_type = functional::fun::broadcast_binary_ufunc<op_t>;

        auto operator()(const ufunc_type&) const noexcept
        {
            auto op_str = nmtools_string("");
            
            if constexpr (!is_none_v<op_t>) {
                op_str = to_string(op_t{});

                if (op_str.empty()) {
                    op_str += NMTOOLS_TYPENAME_TO_STRING(op_t);
                }
            }

            auto str = nmtools_string("");

            str += "broadcast_ufunc(";
            str += op_str;
            str += ")";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif /// NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNC_UFUNC_HPP