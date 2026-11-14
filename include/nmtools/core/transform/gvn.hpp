#ifndef NMTOOLS_CORE_TRANSFORM_GVN_HPP
#define NMTOOLS_CORE_TRANSFORM_GVN_HPP

#include "nmtools/meta.hpp"
#include "nmtools/core/node.hpp"
#include "nmtools/network/digraph.hpp"
#include "nmtools/network/predecessors.hpp"
#include "nmtools/network/topological_sort.hpp"

#include "nmtools/utl/constant_map.hpp"
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
        , [[maybe_unused]] bool partial=false
    ) {
        // when partial, nodes that cannot be identified at compile time
        // (unknown shape in the value form without a compile-time alias id)
        // are left as NONE slots: the compile-time resolve harvests them as
        // runtime slots. Otherwise every node must get a hash, either
        // computed here or by the caller's runtime loop.
        using result_t = resolve_optype_t<gvn_t,adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t,hash_shape_t,hash_address_t>;
        auto m_digraph = digraph;

        const auto all_preds = unwrap(network::predecessors(m_digraph));
        auto pred_hashes_vtype = [](){
            constexpr auto MAX_LEN = max_len_v<node_ids_t>;
            if constexpr (MAX_LEN > 0) {
                using type = nmtools_static_vector<nm_size_t,MAX_LEN>;
                return as_value_v<type>;
            } else {
                // TODO: use small vector
                using type = nmtools_list<nm_size_t>;
                return as_value_v<type>;
            }
        }();
        using pred_hashes_t [[maybe_unused]] = type_t<decltype(pred_hashes_vtype)>;

        auto result = result_t{};

        auto m_sorted_ids = network::topological_sort(m_digraph);

        nmtools_panic( has_value(m_sorted_ids)
            , "invalid graph for gvn, can't be sorted"
        );

        const auto sorted_ids = unwrap(m_sorted_ids);

        auto loop = [&](auto i){
            const auto id = at(sorted_ids,i);

            auto& slot = result[id];
            using value_t = remove_cvref_t<decltype(slot)>;
            if constexpr (!is_constant_index_v<value_t>) {
                auto& node = m_digraph.nodes(id);
                using node_t = remove_cvref_t<decltype(node)>;
                if constexpr (is_value_node_v<node_t>) {
                    // A value-form node whose shape carries unknown entries
                    // (marked as -1, e.g. captured from runtime-shaped operands
                    // where the output shape is only known at runtime) cannot
                    // be identified at compile time, unless it carries a
                    // compile-time alias id (its identity is then the alias):
                    // leave its slot as NONE so that the resolve keeps it as
                    // a runtime slot.
                    // NOTE: tree nodes (buffer/compute node) don't need this
                    // check: they are only visited for runtime slots, whose
                    // hash() overload already takes the runtime branch.
                    // NOTE: the skip is gated by the partial flag instead of
                    // deducing from the slot value type: a value-form public
                    // call (e.g. gvn on to_value of a graph) resolves to the
                    // same runtime static_map with nullable values, but its
                    // result is final -- leaving NONE there breaks consumers
                    // reading at().
                    // auto partial = is_nullable_num_v<value_t>;
                    if (partial) {
                        const auto& attrs = node.attributes_;
                        const bool aliased = attrs.count("alias");
                        bool unknown_shape = false;
                        if (attrs.count("shape")) {
                            const auto& node_shape = attrs.at("shape").index_array;
                            for (nm_size_t k=0; k<(nm_size_t)node_shape.size(); k++) {
                                if (at(node_shape,k) < 0) {
                                    unknown_shape = true;
                                    break;
                                }
                            }
                        }
                        if (!aliased && unknown_shape) {
                            return;
                        }
                    }
                }

                // NOTE: all_preds is indexed by node position, while id is a node id;
                // convert id to its position via index_of before indexing the table.
                auto preds = at(all_preds, unwrap(index::index_of(m_digraph.node_ids,id)));

                // NOTE: combine preds hashes in sorted order so the result
                // does not depend on node ordering in the graph
                auto pred_hashes = pred_hashes_t{};
                bool preds_known = true;
                constexpr auto NUM_PREDS = len_v<decltype(preds)>;
                if constexpr (NUM_PREDS > 0) {
                    template_for<NUM_PREDS>([&](auto J){
                        const auto pred_id = at(preds,J);
                        if (result.count(pred_id)) {
                            const auto pred_hash = result.at(pred_id);
                            if (has_value(pred_hash)) {
                                pred_hashes.push_back(unwrap(pred_hash));
                            } else {
                                // predecessor is not compile-time computable,
                                // so this node is not either
                                preds_known = false;
                            }
                        }
                    });
                } else if constexpr (NUM_PREDS < 0) {
                    for (nm_size_t j=0; j<(nm_size_t)len(preds); j++) {
                        const auto pred_id = at(preds,j);
                        if (result.count(pred_id)) {
                            const auto pred_hash = result.at(pred_id);
                            if (has_value(pred_hash)) {
                                pred_hashes.push_back(unwrap(pred_hash));
                            } else {
                                preds_known = false;
                            }
                        }
                    }
                }
                if (!preds_known) {
                    return;
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

                slot = hash;
            }
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
        , typename edge_attributes_t
        , typename hash_shape_t
        , typename hash_address_t>
    struct resolve_optype<
        void, functional::gvn_t, adjacency_list_t, node_ids_t, node_attributes_t, edge_attributes_t, hash_shape_t, hash_address_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_adjacency_list_v<adjacency_list_t>
                || !is_index_array_v<node_ids_t>
            ) {
                using type = error::GVN_UNSUPPORTED<adjacency_list_t,node_ids_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<node_ids_t>
                && is_constant_adjacency_list_v<adjacency_list_t>
                && is_tuple_v<node_attributes_t>
                && is_constant_index_v<hash_shape_t>
                && is_constant_index_v<hash_address_t>
            ) {
                constexpr auto LEN = len_v<node_ids_t>;
                #if 0
                // TODO: compute at compile-time with to value
                using type = utl::constant_map<node_ids_t,nmtools_array<nm_size_t,LEN>>;
                return as_value_v<type>;
                #else
                using graph_t = network::digraph_t<adjacency_list_t,node_ids_t,node_attributes_t,edge_attributes_t>;
                constexpr auto g = to_value_v<graph_t>;
                // NOTE: partial: nodes that cannot be identified at compile
                // time are left as NONE slots, harvested below as runtime
                // slots; the runtime loop of this gvn call fills them.
                constexpr auto result = functional::gvn(g,hash_shape_t{},hash_address_t{},true);
                constexpr auto values_vtype = template_reduce<LEN>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    using node_id_t = at_t<node_ids_t,I>;
                    constexpr auto node_id = node_id_t::value;
                    constexpr auto hash = result.at(node_id);
                    using init_t = type_t<decltype(init)>;
                    if constexpr (has_value(hash)) {
                        using type = append_type_t<init_t,ct<unwrap(hash)>>;
                        return as_value_v<type>;
                    } else {
                        using type = append_type_t<init_t,nm_size_t>;
                        return as_value_v<type>;
                    }
                }, as_value_v<nmtools_tuple<>>);
                using values_t = type_t<decltype(values_vtype)>;
                using type = utl::constant_map<node_ids_t,values_t>;
                return as_value_v<type>;
                #endif
            } else {
                constexpr auto MAX_LEN = max_len_v<node_ids_t>;
                using node_id_t = get_index_element_type_t<node_ids_t>;
                using value_t   = nullable_num<nm_size_t>;
                if constexpr (MAX_LEN > 0) {
                    using type = utl::static_map<node_id_t,value_t,MAX_LEN>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_default_map<node_id_t,value_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_CORE_TRANSFORM_GVN_HPP