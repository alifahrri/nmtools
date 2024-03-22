#ifndef NMTOOLS_UTILS_TO_STRING_FUNCTOR_HPP
#define NMTOOLS_UTILS_TO_STRING_FUNCTOR_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/utils/to_string/common_types.hpp"
#include "nmtools/array/functional/functor.hpp"

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename F, nm_size_t Arity>
    struct to_string_t<
        functional::fmap_t<F,Arity>, none_t
    > {
        using fmap_type = functional::fmap_t<F,Arity>;
    
        auto operator()(const fmap_type& fmap) const noexcept
        {
            auto fmap_str = to_string(fmap.fn);

            if (fmap_str.empty()) {
                fmap_str += NMTOOLS_TYPENAME_TO_STRING(F);
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

    template <typename F, typename operands_t, typename attributes_t>
    struct to_string_t<functional::functor_t<F,operands_t,attributes_t>,none_t,void>
    {
        using functor_type = functional::functor_t<F,operands_t,attributes_t>;

        auto operator()(const functor_type& functor) const noexcept
        {
            auto fmap_str = to_string(functor.fmap);

            auto attr_str = nmtools_string("");
            attr_str += "[{";
            constexpr auto N = meta::len_v<attributes_t>;
            meta::template_for<N>([&](auto index){
                attr_str += to_string(nmtools::at(functor.attributes,index));
                if (index < (N-1)) {
                    attr_str += ",";
                }
            });
            attr_str += "}]";

            return fmap_str + attr_str;
        }
    };

    template <template<typename...>typename tuple, typename...functors_t, typename operands_t>
    struct to_string_t<
        functional::functor_composition_t<tuple<functors_t...>,operands_t>, none_t, void
    > {
        using composition_type = functional::functor_composition_t<tuple<functors_t...>,operands_t>;

        auto operator()(const composition_type& composition) const noexcept
        {
            auto composition_str = nmtools_string("");
            constexpr auto N = sizeof...(functors_t);
            meta::template_for<N>([&](auto index){
                composition_str += to_string(at(composition.functors,index));
                if (index < (N-1)) {
                    composition_str += " * ";
                }
            });
            return composition_str;
        }
    };

    template <typename functor_t, typename operands_t>
    struct to_string_t<
        functional::node_t<functor_t,operands_t>, none_t, void
    > {
        using node_type = functional::node_t<functor_t,operands_t>;

        auto operator()(const node_type& node) const noexcept
        {
            auto node_str = nmtools_string("");
            node_str += to_string(node.functor);
            return node_str;
        }
    };

    template <typename nodes_t, typename edges_t, typename node_data_t>
    struct to_string_t<
        // functional::compute_graph_t<nodes_t,edges_t,node_data_t>, none_t, void
        utility::ct_digraph<nodes_t,edges_t,node_data_t>, graphviz_t, void
    > {
        // using graph_type = functional::compute_graph_t<nodes_t,edges_t,node_data_t>;
        using graph_type = utility::ct_digraph<nodes_t,edges_t,node_data_t>;

        auto operator()(const graph_type& graph) const noexcept
        {
            auto graphviz = nmtools_string("digraph G");
            graphviz += "{";

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

                    auto node_id_str = to_string(node_id);
                    graphviz += node_id_str;
                    graphviz += "[";
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