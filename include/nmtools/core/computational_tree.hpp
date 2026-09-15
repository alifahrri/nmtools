#ifndef NMTOOLS_CORE_COMPUTATIONAL_TREE_HPP
#define NMTOOLS_CORE_COMPUTATIONAL_TREE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/error.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/core/node.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/index/alias.hpp"
#include "nmtools/array/ref.hpp"

namespace nmtools::functional
{
    template <typename view_t>
    struct get_computational_tree_t;

    template <typename view_t, typename node_id_t=none_t>
    constexpr auto get_computational_tree(const view_t& view, [[maybe_unused]] node_id_t node_id=node_id_t{})
    {
        static_assert( is_none_v<node_id_t> || is_constant_index_v<node_id_t> );
        if constexpr (is_maybe_v<view_t>) {
            using result_t = decltype(get_computational_tree(unwrap(view),node_id));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(view)
                ? return_t{get_computational_tree(unwrap(view),node_id)}
                : return_t{Nothing}
            );
        } else if constexpr (is_either_v<view_t>) {
            using left_t   = decltype(get_computational_tree(*get_left(&view),node_id));
            using right_t  = decltype(get_computational_tree(*get_right(&view),node_id));
            using return_t = conditional_t<is_same_v<left_t,right_t>,left_t,nmtools_either<left_t,right_t>>;
            if (auto l_ptr = get_left(&view)) {
                return return_t{get_computational_tree(*l_ptr,node_id)};
            } else {
                auto r_ptr = get_right(&view);
                return return_t{get_computational_tree(*r_ptr,node_id)};
            }
        } else if constexpr (is_view_v<view_t>) {
            using view_type = view_t;
            auto getter = get_computational_tree_t<view_type>();
            return getter(view,node_id);
        }
    } // get_computational_tree

    template <template<typename...> typename view_t, typename...args_t>
    struct get_computational_tree_t<view::decorator_t<view_t,args_t...>>
    {
        using view_type = view::decorator_t<view_t,args_t...>;
        using view_id_type = typename view_type::id_type;

        template <typename node_id_t>
        constexpr auto operator()(const view_type& view, node_id_t) const
        {
            auto compute_node = node(view);
            auto node_id = [](){
                if constexpr (!is_none_v<node_id_t>) {
                    return node_id_t{};
                } else {
                    return ct_v<0>;
                    // return view_id_type{};
                }
            }();

            // if (node_id == 0) {
            //     nmtools_panic( node_id != 0
            //         , "invalid node id"
            //     );
            // }

            auto digraph = network::digraph(
                nmtools_tuple<nmtools_tuple<>>{}
                , nmtools_tuple{node_id}
                , nmtools_tuple{unwrap(compute_node)}
            );

            auto operands = get_operands(view);

            constexpr auto N = len_v<decltype(operands)>;
            return template_reduce<N>([&](auto G, auto I){
                const auto& operand = at(operands,I);
                const auto& operand_node = [&](){
                    using operand_t = remove_cvref_t<decltype(operand)>;
                    if constexpr (is_pointer_v<operand_t> && !is_shared_ptr_v<operand_t>) {
                        return node(*operand);
                    } else {
                        return node(operand);
                    }
                }();

                // id unique to the graph
                // auto operand_id = index::generate_alias(G.node_ids,ct_v<256>,ct_v<57885161>);

                auto operand_id = at(G.node_ids,ct_v<-1>) + ct_v<1>;
                
                if (operand_id == node_id) {
                    nmtools_panic( operand_id != node_id
                        , "invalid operand id / node id"
                    );
                }

                auto graph = G
                    .add_node(operand_id,operand_node)
                    .add_edge(operand_id,node_id)
                ;
                using operand_t = remove_cvref_t<decltype(operand)>;
                if constexpr (is_view_v<operand_t>
                    && !meta::is_same_view_v<view::alias_t,operand_t>
                ) {
                    auto subgraph = get_computational_tree(operand,operand_id);
                    auto composed = network::compose(graph,subgraph);
                    return composed;
                } else {
                    return graph;
                }
            }, digraph);
        }
    };
}

#endif // NMTOOLS_CORE_COMPUTATIONAL_TREE_HPP