#ifndef NMTOOLS_CORE_EXPRESSION_TREE_HPP
#define NMTOOLS_CORE_EXPRESSION_TREE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/network/digraph.hpp"

#include <iostream>

namespace nmtools::functional
{
    template <typename input_t, typename shape_t, typename element_t=none_t>
    struct buffer_node_t
    {
        // TODO: input must be buffered array or num
        using input_type = meta::conditional_t<meta::is_num_v<input_t>,input_t,const input_t*>;
        using shape_type = const shape_t;
        using element_type = element_t;

        input_type input;
        shape_type shape;

        #if NMTOOLS_HAS_STRING
        auto to_string() const noexcept
        {
            auto str = nmtools_string();

            str += utils::to_string(input,utils::Compact);
            if constexpr (!is_none_v<shape_t>) {
                str += " | ";
                str += utils::to_string(shape,utils::Compact);
            }
            return str;
        }
        #endif
    };

    template <typename input_t>
    constexpr auto buffer_node(const input_t& input)
    {
        if constexpr (meta::is_maybe_v<input_t>) {
            using result_t = decltype(buffer_node(unwrap(input)));
            using return_t = nmtools_maybe<result_t>;
            // TODO: make sure unwrap return reference
            return (has_value(input)
                ? return_t{buffer_node(unwrap(input))}
                : return_t{meta::Nothing}
            );
        } else {
            auto shape = nmtools::shape<true>(input);
            using element_t = meta::get_element_type_t<input_t>;
            using shape_t   = meta::remove_cvref_t<decltype(shape)>;
            using node_t    = buffer_node_t<input_t,shape_t,element_t>;
            if constexpr (meta::is_num_v<input_t>) {
                return node_t{input,shape};
            } else {
                return node_t{&input,shape};
            }
        }
    }

    template <typename functor_t, typename operands_t, typename output_shape_t=nmtools_tuple<>, typename output_element_t=none_t>
    struct compute_node_t
    {
        // TODO: assert functor_t is functor or functor composition
        // TODO: assert operands_t is tuple of integral constant

        using functor_type  = functor_t;
        using operands_type = operands_t;
        using output_shape_type   = output_shape_t;
        using output_element_type = output_element_t;

        functor_type        functor;
        operands_type       operands;
        output_shape_type   output_shape   = {};
        output_element_type output_element = {};

        #if NMTOOLS_HAS_STRING
        auto to_string() const noexcept
        {
            auto str = nmtools_string("");

            {
                using attributes_t = meta::remove_cvref_t<decltype(functor.attributes)>;
                auto fmap_str = utils::to_string(functor.fmap,utils::Compact);

                auto attr_str = nmtools_string("");
                constexpr auto N = meta::len_v<attributes_t>;
                meta::template_for<N>([&](auto index){
                    attr_str += utils::to_string(nmtools::at(functor.attributes,index),utils::Compact);
                    if (index < (N-1)) {
                        attr_str += ",";
                    }
                });

                str += fmap_str;
                str += " ";
                str += attr_str;
            }

            {
                auto operands_str = nmtools_string("operands: ");
                constexpr auto N = meta::len_v<operands_type>;
                meta::template_for<N>([&](auto I){
                    operands_str += utils::to_string(at(operands,I),utils::Compact);
                    if (I < (N-1)) {
                        operands_str += ", ";
                    }
                });
                str += " | ";
                str += operands_str;
            }

            if constexpr (!is_none_v<output_shape_type> && !meta::is_same_v<output_shape_type,nmtools_tuple<>>) {
                str += " | ";
                str += utils::to_string(output_shape,utils::Compact);
            }

            return str;
        }
        #endif
    };

    template <typename functor_t, typename operands_t, typename output_shape_t=nmtools_tuple<>, typename output_element_t=none_t>
    constexpr auto compute_node(const functor_t& functor
        , const operands_t& operands
        , const output_shape_t& output_shape=output_shape_t{}
        , const output_element_t& output_element=output_element_t{})
    {
        using node_t = compute_node_t<functor_t,operands_t,output_shape_t,output_element_t>;
        return node_t{functor,operands,output_shape,output_element};
    }

    template <typename view_t>
    constexpr auto compute_node(const view_t& view)
    {
        if constexpr (meta::is_maybe_v<view_t>) {
            using result_t = decltype(compute_node(unwrap(view)));
            using return_t = nmtools_maybe<result_t>;
            return (has_value(view)
                ? return_t{compute_node(unwrap(view))}
                : return_t{meta::Nothing}
            );
        } else {
            auto functor   = get_function(view);
            auto operands  = view.operands_ids;
            auto shape     = nmtools::shape<true>(view);
            using output_t = meta::get_element_type_t<view_t>;
            auto node = compute_node(functor,operands,shape,meta::as_value_v<output_t>);
            return node;
        }
    }

    template <typename input_t>
    constexpr auto node(const input_t& input)
    {
        if constexpr (meta::is_maybe_v<input_t>) {
            using result_t = decltype(node(unwrap(input)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(input)
                ? return_t{node(unwrap(input))}
                : return_t{meta::Nothing}
            );
        } else if constexpr (meta::is_same_view_v<view::alias_t,input_t>) {
            if constexpr (meta::is_pointer_v<decltype(input.array)>) {
                return buffer_node(*(input.array));
            } else {
                return buffer_node(input.array);
            }
        } else if constexpr (meta::is_view_v<input_t>) {
            return compute_node(input);
        } else {
            return buffer_node(input);
        }
    }

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
}

#endif // NMTOOLS_CORE_EXPRESSION_TREE_HPP