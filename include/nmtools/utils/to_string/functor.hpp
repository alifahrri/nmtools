#ifndef NMTOOLS_UTILS_TO_STRING_FUNCTOR_HPP
#define NMTOOLS_UTILS_TO_STRING_FUNCTOR_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/utils/to_string/common_types.hpp"
#include "nmtools/array/functional/functor.hpp"

// TODO: move to functor.hpp

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

            using mapper_type = to_string_t<decltype(fmap.fn),formatter_type>;
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

    template <typename functor_t, typename operands_t, auto...fmt_args>
    struct to_string_t<
        functional::node_t<functor_t,operands_t>, fmt_string_t<fmt_args...>, void
    > {
        using node_type = functional::node_t<functor_t,operands_t>;
        using formatter_type = fmt_string_t<fmt_args...>;
        using result_type = nmtools_string;

        auto operator()(const node_type& node) const noexcept
        {
            auto node_str = nmtools_string("");
            node_str += to_string(node.functor,formatter_type{});
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

                    graphviz += to_string(src_edge);
                    graphviz += " -> ";
                    graphviz += to_string(dst_edge);
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

                    auto node_id_str = to_string(node_id);
                    graphviz += node_id_str;
                    graphviz += "[";
                    graphviz += "shape=\"box\" ";
                    if (is_buffered) {
                        graphviz += "style=\"rounded,filled\" ";
                        graphviz += "color=\"black\" ";
                        graphviz += "fillcolor=\"gray93\" ";
                    }
                    graphviz += "label=";
                    graphviz += "\"";
                    graphviz += "{id: ";
                    graphviz += node_id_str;
                    graphviz += "}\n";
                    graphviz += to_string(node);
                    graphviz += "\"";
                    graphviz += "]\n";
                });
            }

            graphviz += "}";

            remove_string(graphviz, nmtools_string("nmtools::"));
            remove_string(graphviz, nmtools_string("array::"));
            remove_string(graphviz, nmtools_string("std::"));

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

#endif // NMTOOLS_UTILS_TO_STRING_FUNCTOR_HPP