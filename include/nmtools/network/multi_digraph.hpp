#ifndef NMTOOLS_NETWORK_MULTI_DIGRAPH_HPP
#define NMTOOLS_NETWORK_MULTI_DIGRAPH_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/contains.hpp"
#include "nmtools/index/index_of.hpp"
#include "nmtools/network/add_edge.hpp"
#include "nmtools/network/common.hpp"
#include "nmtools/network/compose.hpp"
#include "nmtools/network/contracted_edge.hpp"
#include "nmtools/network/filter_nodes.hpp"
#include "nmtools/network/filter_node_arity.hpp"
#include "nmtools/network/is_directed_acyclic_graph.hpp"
#include "nmtools/network/out_edges.hpp"
#include "nmtools/network/predecessors.hpp"
#include "nmtools/network/topological_generations.hpp"
#include "nmtools/network/topological_sort.hpp"
#include "nmtools/network/map_ids.hpp"

namespace nmtools::network
{
    template <typename adjacency_list_t
        , typename node_ids_t=none_t
        , typename node_attributes_t=none_t
        , typename edge_attributes_t=none_t>
    using multi_digraph_t = base_digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t,meta::true_type>;

    template <typename edge_attributes_t=none_t
        , typename node_attributes_t=none_t
        , typename node_ids_t=none_t
        , typename adjacency_list_t=none_t>
    constexpr auto multi_digraph([[maybe_unused]] const adjacency_list_t& adj_list=adjacency_list_t{}
        , [[maybe_unused]] const node_ids_t& node_ids=node_ids_t{}
        , [[maybe_unused]] const node_attributes_t& node_attributes=node_attributes_t{}
        , [[maybe_unused]] const edge_attributes_t& edge_attributes=edge_attributes_t{})
    {
        return base_digraph<meta::true_type>(adj_list,node_ids,node_attributes,edge_attributes);
    }
}

#endif // NMTOOLS_NETWORK_MULTI_DIGRAPH_HPP