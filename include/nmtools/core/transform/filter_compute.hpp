#ifndef NMTOOLS_CORE_TRANSFORM_FILTER_COMPUTE_HPP
#define NMTOOLS_CORE_TRANSFORM_FILTER_COMPUTE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/core/node.hpp"

namespace nmtools::functional
{
    template <typename adjacency_list_t
        , typename node_ids_t
        , typename node_attributes_t
        , typename edge_attributes_t
        , typename n_repeats_t=ct<1>>
    constexpr auto filter_compute(
        const network::digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t>& digraph
        , [[maybe_unused]] n_repeats_t n_repeats = n_repeats_t{})
    {
        using digraph_t = network::digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t>;
        using result_t  = typename digraph_t::node_ids_type;

        // assume node is functional::node
        auto nodes = digraph.nodes();

        auto result = result_t{};

        for (nm_size_t i=0; i<(nm_size_t)len(nodes); i++) {
            auto node_id = nodes.at(i);
            auto node = digraph.nodes(node_id);
            if (node.is_compute()) {
                // assume has push back
                result.push_back(node_id);
            }
        }

        return result;
    }
} // filter_compute

#endif // NMTOOLS_CORE_TRANSFORM_FILTER_COMPUTE_HPP