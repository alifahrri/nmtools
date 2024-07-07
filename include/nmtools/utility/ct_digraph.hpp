#ifndef NMTOOLS_UTILITY_CT_DIGRAPH_HPP
#define NMTOOLS_UTILITY_CT_DIGRAPH_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/at.hpp"
#include "nmtools/utility/ct_map.hpp"

namespace nmtools::utility
{
    template <typename nodes_t=nmtools_tuple<>, typename edges_t=nmtools_tuple<>, typename node_data_t=nmtools_tuple<>>
    struct ct_digraph
    {
        using digraph_type   = ct_map<nodes_t,edges_t>;
        using node_data_type = ct_map<nodes_t,node_data_t>;
        static_assert( digraph_type::SIZE == node_data_type::SIZE
            , "invalid size of nodes, edges, and data"
        );

        digraph_type   digraph;
        node_data_type node_data;

        constexpr ct_digraph() {}

        constexpr ct_digraph(const ct_map<nodes_t,edges_t>& digraph, const ct_map<nodes_t,node_data_t>& node_data)
            : digraph(digraph)
            , node_data(node_data)
        {}

        static constexpr auto SIZE = node_data_type::SIZE;

        constexpr auto size() const noexcept
        {
            return meta::ct_v<SIZE>;
        }

        template <typename node_t, typename data_t>
        constexpr auto add_node(node_t node, const data_t& data) const noexcept
        {
            auto new_digraph = digraph.insert(node,/*edges*/nmtools_tuple{});
            auto new_node_data = node_data.insert(node,data);
            using new_digraph_type = decltype(new_digraph);
            using new_node_data_type = decltype(new_node_data);
            using new_ct_digraph_type = ct_digraph<
                meta::remove_cvref_t<typename new_digraph_type::keys_type>
                , meta::remove_cvref_t<typename new_digraph_type::values_type>
                , meta::remove_cvref_t<typename new_node_data_type::values_type>
            >;
            return new_ct_digraph_type(
                new_digraph
                , new_node_data  
            );
        }

        template <typename from_t, typename to_t>
        constexpr auto add_edge(from_t from, to_t to) const noexcept
        {
            auto edges = digraph.at(from);
            // avoid duplication
            auto contains = [](auto tuple, auto key){
                constexpr auto N = meta::len_v<decltype(tuple)>;
                constexpr auto KEY = meta::to_value_v<decltype(key)>;
                return meta::template_reduce<N>([&](auto init, auto index){
                    auto element = nmtools::at(tuple,index);
                    constexpr auto ELEMENT = meta::to_value_v<decltype(element)>;
                    if constexpr (ELEMENT == KEY) {
                        return meta::true_type{};
                    } else {
                        return init;
                    }
                }, meta::false_type{});
            };
            auto has_key = contains(edges,to);
            constexpr auto HAS_KEY = meta::to_value_v<decltype(has_key)>;
            if constexpr (HAS_KEY) {
                return *this;
            } else {
                auto new_edges = tuple_append(edges,to);
                auto new_digraph = digraph.update(from,/*edges*/new_edges);
                using new_digraph_type = decltype(new_digraph);
                using new_node_data_type = decltype(node_data);
                using new_ct_digraph_type = ct_digraph<
                    meta::remove_cvref_t<typename new_digraph_type::keys_type>
                    , meta::remove_cvref_t<typename new_digraph_type::values_type>
                    , meta::remove_cvref_t<typename new_node_data_type::values_type>
                >;
                return new_ct_digraph_type(
                    new_digraph
                    , node_data
                );
            }
        }

        constexpr auto nodes() const noexcept
        {
            return node_data.keys();
        }

        constexpr auto out_edges() const noexcept
        {
            auto keys = digraph.keys();
            return meta::template_reduce<SIZE>([&](auto init, auto index){
                constexpr auto I = decltype(index)::value;
                auto src_edge = nmtools::get<I>(keys);
                auto out_edges = digraph.at(src_edge);
                constexpr auto N = meta::len_v<decltype(out_edges)>;
                using src_edge_t = meta::remove_cvref_t<decltype(src_edge)>;
                return meta::template_reduce<N>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    auto dst_edge = nmtools::get<I>(out_edges);
                    using dst_edge_t = meta::remove_cvref_t<decltype(dst_edge)>;
                    return tuple_append(init,nmtools_tuple<src_edge_t,dst_edge_t>{src_edge,dst_edge});
                }, init);
            }, nmtools_tuple{});
        }

        template <typename key_t>
        constexpr auto nodes(key_t key) const noexcept
        {
            return node_data.at(key);
        }

        template <typename key_t>
        constexpr auto out_edges(key_t key) const noexcept
        {
            return digraph.at(key);
        }
    }; // ct_digraph

    template <typename nodes_t, typename edges_t, typename node_data_t>
    ct_digraph(const ct_map<nodes_t,edges_t>&, const ct_map<nodes_t,node_data_t>&) -> ct_digraph<nodes_t,edges_t,node_data_t>;
}

#endif // NMTOOLS_UTILITY_CT_DIGRAPH_HPP