#ifndef NMTOOLS_UTILITY_CT_DIGRAPH_HPP
#define NMTOOLS_UTILITY_CT_DIGRAPH_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/ct_map.hpp"
#include "nmtools/utl/static_vector.hpp"
#include "nmtools/utl/static_queue.hpp"
#include "nmtools/assert.hpp"

namespace nmtools::utility
{
    template <typename tuple_t, typename key_t>
    constexpr auto contains(const tuple_t& tuple, key_t key)
    {
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
    }

    template <typename nodes_t, typename edges_t>
    constexpr auto adjacency_matrix(ct_map<nodes_t,edges_t>)
    {
        constexpr auto N = meta::len_v<nodes_t>;
        using adj_matrix_t = nmtools_array<nmtools_array<nm_size_t,N>,N>;
        using id_mapping_t = nmtools_array<nm_size_t,N>;

        auto matrix = adj_matrix_t {};
        auto id_map = id_mapping_t {}; // node -> id

        constexpr auto nodes = meta::to_value_v<nodes_t>;

        for (nm_size_t i=0; i<N; i++) {
            id_map[i] = nodes[i];
        }

        // given id, return node
        auto reverse_id = [&](auto id)->nm_index_t{
            for (nm_size_t i=0; i<(nm_size_t)len(id_map); i++) {
                if (id_map[i] == id) {
                    return i;
                }
            }
            return -1;
        };

        meta::template_for<N>([&](auto index){
            constexpr auto I = decltype(index)::value;
            using edge_t = meta::at_t<edges_t,I>;
            constexpr auto M = meta::len_v<edge_t>;
            meta::template_for<M>([&](auto index){
                constexpr auto J = decltype(index)::value;
                constexpr auto e = meta::at_t<edge_t,J>::value;
                matrix[I][reverse_id(e)] = 1;
            });
        });

        return nmtools_tuple{matrix,id_map};
    }

    template <typename nodes_t, typename edges_t>
    constexpr auto adjacency_list(ct_map<nodes_t,edges_t>)
    {
        constexpr auto N = meta::len_v<nodes_t>;
        using adj_list_t = nmtools_array<utl::static_vector<nm_size_t,N>,N>;
        using id_mapping_t = nmtools_array<nm_size_t,N>;

        auto list = adj_list_t {};
        auto id_map = id_mapping_t {}; // node -> id

        constexpr auto nodes = meta::to_value_v<nodes_t>;

        for (nm_size_t i=0; i<N; i++) {
            id_map[i] = nodes[i];
        }

        // given id, return node
        auto reverse_id = [&](auto id)->nm_index_t{
            for (nm_size_t i=0; i<(nm_size_t)len(id_map); i++) {
                if (id_map[i] == id) {
                    return i;
                }
            }
            return -1;
        };

        meta::template_for<N>([&](auto index){
            constexpr auto I = decltype(index)::value;
            using edge_t = meta::at_t<edges_t,I>;
            constexpr auto M = meta::len_v<edge_t>;
            meta::template_for<M>([&](auto index){
                constexpr auto J = decltype(index)::value;
                constexpr auto e = meta::at_t<edge_t,J>::value;
                list[I].push_back(reverse_id(e));
            });
        });

        return nmtools_tuple{list,id_map};
    } // adjacency_list

    template <typename adjacency_list_t>
    constexpr auto in_degree(const adjacency_list_t& list)
    {
        // assume static_vector or array
        // TODO: check for another type
        constexpr auto N = meta::bounded_size_v<typename adjacency_list_t::value_type>;

        using result_t = utl::static_vector<nm_size_t,N>;
        auto result = result_t {};

        auto n = len(list);
        result.resize(n);

        for (nm_size_t i=0; i<(nm_size_t)n; i++) {
            for (nm_size_t j=0; j<(nm_size_t)list[i].size(); j++) {
                result[list[i][j]]++;
            }
        }
        return result;
    }

    template <typename nodes_t=nmtools_tuple<>, typename edges_t=nmtools_tuple<>, typename node_data_t=nmtools_tuple<>>
    struct ct_digraph
    {
        // edges is out edges
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

        template <typename from_t, typename tos_t>
        constexpr auto add_edges(from_t from, tos_t tos) const noexcept
        {
            auto new_digraph = digraph.update(from,tos);
            using new_digraph_type = decltype(new_digraph);
            using new_node_data_type = decltype(node_data);
            using result_t = ct_digraph<
                meta::remove_cvref_t<typename new_digraph_type::keys_type>
                , meta::remove_cvref_t<typename new_digraph_type::values_type>
                , meta::remove_cvref_t<typename new_node_data_type::values_type>
            >;
            return result_t(
                new_digraph
                , node_data
            );
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

    template <auto N, typename index_t, typename edge_t, typename new_id_t>
    constexpr auto contracted_edge(const nmtools_array<utl::static_vector<index_t,N>,N>& adj_list, const nmtools_array<index_t,N>& id_map, edge_t edge, new_id_t new_id)
    {
        // given id, return node
        auto reverse_id = [&](auto id){
            auto index = -1;
            for (nm_size_t i=0; i<(nm_size_t)len(id_map); i++) {
                if (id_map[i] == id) {
                    index = i;
                    break;
                }
            }
            return index;
        };

        auto src_node = at(edge,meta::ct_v<0>);
        auto dst_node = at(edge,meta::ct_v<1>);

        using graph_ids_t = utl::static_vector<nm_size_t,N+1>;
        using adj_list_t  = utl::static_vector<utl::static_vector<nm_size_t,N+1>,N+1>;

        auto graph_ids = graph_ids_t{};
        graph_ids.resize(N+1);

        for (nm_size_t i=0; i<N; i++) {
            at(graph_ids,i) = at(id_map,i);
        }
        at(graph_ids,N) = new_id;

        // create adjacency list with graph_id as columns
        auto adj_list_1 = adj_list_t{};
        adj_list_1.resize(N+1);
        for (nm_size_t i=0; i<N; i++) {
            for (nm_size_t j=0; j<adj_list[i].size(); j++) {
                auto g_id = graph_ids[adj_list[i][j]];
                if (((nm_index_t)g_id == (nm_index_t)src_node)
                    || ((nm_index_t)g_id == (nm_index_t)dst_node)
                ) {
                    g_id = new_id;
                }
                at(adj_list_1,i).push_back(g_id);
            }
        }
        // dst_node outgoing edges
        auto dst_ = adj_list[reverse_id(dst_node)];
        for (nm_size_t i=0; i<dst_.size(); i++) {
            // assume there are no loopback to src_node, as it should be for dag
            adj_list_1[N].push_back(graph_ids[dst_[i]]);
        }
        // erase
        auto res_id_map = graph_ids_t {};
        auto res_adj_list = adj_list_t {};
        for (nm_size_t i=0; i<(nm_size_t)adj_list_1.size(); i++) {
            if (i == (nm_size_t)reverse_id(src_node)
                || i == (nm_size_t)reverse_id(dst_node)
            ) {
                continue;
            }
            res_adj_list.push_back(adj_list_1[i]);
        }
        for (nm_size_t i=0; i<(nm_size_t)graph_ids.size(); i++) {
            if (i == (nm_size_t)reverse_id(src_node)
                || i == (nm_size_t)reverse_id(dst_node)
            ) {
                continue;
            }
            res_id_map.push_back(graph_ids[i]);
        }
        auto index = [](const auto& vector, auto value) {
            auto index = -1;
            for (nm_size_t i=0; i<(nm_size_t)vector.size(); i++) {
                if ((nm_index_t)vector[i] == (nm_index_t)value) {
                    index = i;
                    break;
                }
            }
            return index;
        };
        // convert adj_list edges to node index instead of graph id
        for (nm_size_t i=0; i<(nm_size_t)res_adj_list.size(); i++) {
            // const auto& node = at(res_adj_list,i);
            for (nm_size_t j=0; j<(nm_size_t)res_adj_list[i].size(); j++) {
                auto idx = index(res_id_map,res_adj_list[i][j]);
                nmtools_assert( idx >= 0
                    , "invalid index when contracting edge");
                res_adj_list[i][j] = idx;
            }
        }
        return nmtools_tuple{res_adj_list,res_id_map};
    } // contracted_edge

    template <typename nodes_t, typename edges_t, typename node_data_t, typename from_t, typename to_t, template<typename...>typename tuple_t, typename new_id_t, typename new_data_t>
    constexpr auto contracted_edge(const ct_digraph<nodes_t,edges_t,node_data_t>& graph, tuple_t<from_t,to_t>, new_id_t, new_data_t new_data)
    {
        constexpr auto adjacency_result  = adjacency_list(decltype(graph.digraph){});
        constexpr auto adjacency_list    = nmtools::get<0>(adjacency_result);
        constexpr auto src_id_map        = nmtools::get<1>(adjacency_result);
        constexpr auto contracted_result = contracted_edge(adjacency_list,src_id_map,tuple_t<from_t,to_t>{},new_id_t{});
        constexpr auto contracted_list   = nmtools::get<0>(contracted_result);
        constexpr auto dst_id_map = nmtools::get<1>(contracted_result);

        auto res_data = graph.node_data
            .erase(from_t{})
            .erase(to_t{})
            .insert(new_id_t{},new_data)
        ;

        auto result = meta::template_reduce<contracted_list.size()>([&](auto G, auto index){
            constexpr auto I = decltype(index)::value;
            constexpr auto node_ct = meta::ct_v<at(dst_id_map,I)>;
            constexpr auto edges = at(contracted_list,I);
            constexpr auto edges_ct = meta::template_reduce<len(edges)>([&](auto E, auto index){
                return utility::tuple_append(E,meta::ct_v<dst_id_map[at(edges,index)]>);
            },nmtools_tuple{});
            return G
                .add_node(node_ct,res_data.at(node_ct))
                .add_edges(node_ct,edges_ct)
            ;
        }, utility::ct_digraph());

        return result;
    }

    template <typename adjacency_list_t>
    constexpr auto topological_sort(const adjacency_list_t& adjacency_list)
    {
        // assume static_vector or array
        // TODO: check for another type
        constexpr auto N = meta::bounded_size_v<typename adjacency_list_t::value_type>;

        auto in_degree = utility::in_degree(adjacency_list);

        auto queue  = utl::static_queue<nm_size_t,N>();
        auto result = utl::static_vector<nm_size_t,N>();

        // initialize queue with input (in_degree 0)
        for (nm_size_t i=0; i<adjacency_list.size(); i++) {
            if (in_degree[i] == 0) {
                queue.push(i);
            }
        }
        for (; !queue.empty();) {
            auto node = queue.pop();
            result.push_back(node);
            for (nm_size_t j=0; j<(nm_size_t)adjacency_list[node].size(); j++) {
                auto neighbor = adjacency_list[node][j];
                in_degree[neighbor] -= 1;
                if (in_degree[neighbor] == 0) {
                    queue.push(neighbor);
                }
            }
        }

        return result;
    } // topological_sort

    template <typename nodes_t, typename edges_t, typename node_data_t>
    constexpr auto topological_sort(const ct_digraph<nodes_t,edges_t,node_data_t>& graph)
    {
        constexpr auto adjacency_result  = adjacency_list(decltype(graph.digraph){});
        constexpr auto adjacency_list    = nmtools::get<0>(adjacency_result);
        constexpr auto src_id_map        = nmtools::get<1>(adjacency_result);

        constexpr auto sorted = topological_sort(adjacency_list);
        constexpr auto N = sorted.size();

        return meta::template_reduce<N>([&](auto init, auto index){
            auto node_id = meta::ct_v<at(src_id_map,at(sorted,index))>;
            return tuple_append(init,node_id);
        },nmtools_tuple{});
    }
} // nmtools::utility

#endif // NMTOOLS_UTILITY_CT_DIGRAPH_HPP