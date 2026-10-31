#ifndef NMTOOLS_CORE_TRANSFORM_GVN_HPP
#define NMTOOLS_CORE_TRANSFORM_GVN_HPP

#include "nmtools/meta.hpp"
#include "nmtools/core/node.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/network/predecessors.hpp"
#include "nmtools/network/topological_sort.hpp"

#include "nmtools/utl/static_map.hpp"
#include "nmtools/utl/static_vector.hpp"

namespace nmtools::functional
{
    struct gvn_t {};

    template <typename adjacency_list_t
        , typename node_ids_t
        , typename node_attributes_t
        , typename edge_attributes_t
        , typename hash_shape_t=true_type
        , typename hash_address_t=true_type>
    constexpr auto gvn(
        const network::digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t>& digraph
        , hash_shape_t hash_shape=hash_shape_t{}
        , hash_address_t hash_address=hash_address_t{}
    ) {
        // TODO: deduce type
        using result_t = resolve_optype_t<gvn_t,adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t>;
        auto m_digraph = digraph;

        auto result = result_t{};

        auto m_sorted_ids = network::topological_sort(m_digraph);

        nmtools_panic( has_value(m_sorted_ids)
            , "invalid graph for gvn, can't be sorted"
        );

        const auto sorted_ids = unwrap(m_sorted_ids);

        auto loop = [&](auto i){
            const auto id = at(sorted_ids,i);

            auto& node = m_digraph.nodes(id);

            const auto preds = unwrap(network::predecessors(m_digraph,id));
            using preds_t = decltype(preds);

            auto pred_hashes_vtype = [](){
                if constexpr (!is_index_array_v<preds_t>) {
                    using type = meta::detail::fail_t;
                    return as_value_v<type>;
                } else {
                    constexpr auto MAX_LEN = max_len_v<preds_t>;
                    if constexpr (MAX_LEN > 0) {
                        using type = nmtools_static_vector<nm_size_t,MAX_LEN>;
                        return as_value_v<type>;
                    } else {
                        // TODO: use small vector
                        using type = nmtools_list<nm_size_t>;
                        return as_value_v<type>;
                    }
                }
            }();
            using pred_hashes_t = type_t<decltype(pred_hashes_vtype)>;

            // NOTE: combine preds hashes in sorted order so the result
            // does not depend on node ordering in the graph
            auto pred_hashes = pred_hashes_t{};
            constexpr auto NUM_PREDS = meta::len_v<preds_t>;
            if constexpr (NUM_PREDS > 0) {
                template_for<NUM_PREDS>([&](auto J){
                    const nm_size_t pred_id = at(preds,J);
                    if (result.count(pred_id)) {
                        pred_hashes.push_back(result.at(pred_id));
                    }
                });
            } else if constexpr (NUM_PREDS < 0) {
                for (nm_size_t j=0; j<(nm_size_t)len(preds); j++) {
                    const nm_size_t pred_id = at(preds,j);
                    if (result.count(pred_id)) {
                        pred_hashes.push_back(result.at(pred_id));
                    }
                }
            }
            // insertion sort (preds are few)
            for (nm_size_t j=1; j<pred_hashes.size(); j++) {
                auto key = pred_hashes.at(j);
                nm_size_t k = j;
                while (k > 0 && pred_hashes.at(k-1) > key) {
                    pred_hashes.at(k) = pred_hashes.at(k-1);
                    k--;
                }
                pred_hashes.at(k) = key;
            }

            // NOTE: hash may be a constant index (e.g. aliased buffers);
            // normalize it so pred_hashes & result keep plain nm_size_t
            nm_size_t hash = functional::hash(node,hash_shape,hash_address);
            for (nm_size_t j=0; j<pred_hashes.size(); j++) {
                auto to_hash = nmtools_array{pred_hashes.at(j),hash};
                hash = index::hash(to_hash);
            }

            result[static_cast<nm_size_t>(id)] = hash;
        };

        constexpr auto NUM_IDS = len_v<decltype(sorted_ids)>;
        if constexpr (NUM_IDS > 0) {
            template_for<NUM_IDS>(
                loop
            );
        } else {
            for (nm_size_t i=0; i<(nm_size_t)len(sorted_ids); i++) {
                loop(i);
            }
        }

        return result;
    }
}

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct GVN_UNSUPPORTED : detail::fail_t {};
    }

    // TODO: pass base_digraph_t directly? instead of the components;
    template <typename adjacency_list_t
        , typename node_ids_t
        , typename node_attributes_t
        , typename edge_attributes_t>
    struct resolve_optype<
        void, functional::gvn_t, adjacency_list_t, node_ids_t, node_attributes_t, edge_attributes_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>
                || !is_index_array_v<node_ids_t>
            ) {
                using type = error::GVN_UNSUPPORTED<adjacency_list_t,node_ids_t>;
                return as_value_v<type>;
            } else {
                constexpr auto MAX_LEN = max_len_v<node_ids_t>;
                if constexpr (MAX_LEN > 0) {
                    using type = utl::static_map<nm_size_t,nm_size_t,MAX_LEN>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_default_map<nm_size_t,nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_CORE_TRANSFORM_GVN_HPP