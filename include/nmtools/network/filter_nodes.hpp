#ifndef NMTOOLS_NETWORK_FILTER_NODES_HPP
#define NMTOOLS_NETWORK_FILTER_NODES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/index_of.hpp"

namespace nmtools::tag
{
    struct filter_nodes_t {};
}

namespace nmtools::network
{
    template <typename node_attributes_t, typename src_node_ids_t, typename dst_node_ids_t>
    constexpr auto filter_nodes(const node_attributes_t& node_attributes
        , const src_node_ids_t& src_node_ids
        , const dst_node_ids_t& dst_node_ids
    ) {
        if constexpr (is_none_v<node_attributes_t>) {
            return None;
        } else if constexpr (meta::is_maybe_v<node_attributes_t>
            || meta::is_maybe_v<src_node_ids_t>
            || meta::is_maybe_v<dst_node_ids_t>
        ) {
            using result_t = decltype(filter_nodes(
                unwrap(node_attributes)
                , unwrap(src_node_ids)
                , unwrap(dst_node_ids)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(node_attributes) && has_value(src_node_ids) && has_value(dst_node_ids)
                ? return_t{filter_nodes(
                    unwrap(node_attributes)
                    , unwrap(src_node_ids)
                    , unwrap(dst_node_ids))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::filter_nodes_t,node_attributes_t,src_node_ids_t,dst_node_ids_t>;

            if constexpr (!meta::is_tuple_v<result_t>
                && !meta::is_constant_index_array_v<result_t>
            ) {
                auto result = result_t {};

                using return_t = nmtools_maybe<result_t>;

                auto num_nodes = len(dst_node_ids);
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(num_nodes);
                }

                auto success = true;
                for (nm_size_t i=0; i<(nm_size_t)num_nodes; i++) {
                    auto node_id = at(dst_node_ids,i);
                    auto m_idx   = index::index_of(src_node_ids,node_id);
                    if (!has_value(m_idx)) {
                        success = false;
                        break;
                    }
                    auto idx = unwrap(m_idx);
                    at(result,i) = at(node_attributes,idx);
                }

                if (success) {
                    return return_t{result};
                } else {
                    return return_t{meta::Nothing};
                }
            } else if constexpr (meta::is_tuple_v<result_t>) {
                constexpr auto src_node_ids = meta::to_value_v<src_node_ids_t>;
                constexpr auto dst_node_ids = meta::to_value_v<dst_node_ids_t>;
                return meta::template_reduce<len(dst_node_ids)>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    constexpr auto m_idx = index::index_of(src_node_ids,at(dst_node_ids,I));
                    return utility::tuple_append(init,at(node_attributes,meta::ct_v<unwrap(m_idx)>));
                },nmtools_tuple<>{});
            } else {
                auto result = result_t {};

                return result;
            }
        }
    }
}

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct FILTER_NODES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename node_attributes_t, typename src_node_ids_t, typename dst_node_ids_t>
    struct resolve_optype<
        void, tag::filter_nodes_t, node_attributes_t, src_node_ids_t, dst_node_ids_t
    > {
        static constexpr auto vtype = [](){
            // TODO: check node_attributes_t
            if constexpr (
                !is_index_array_v<src_node_ids_t>
                || !is_index_array_v<dst_node_ids_t>
                || !(is_index_array_v<node_attributes_t> || has_value_type_v<node_attributes_t> || is_tuple_v<node_attributes_t>)
            ) {
                using type = error::FILTER_NODES_UNSUPPORTED<node_attributes_t,src_node_ids_t,dst_node_ids_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<node_attributes_t>
                && is_constant_index_array_v<src_node_ids_t>
                && is_constant_index_array_v<dst_node_ids_t>
            ) {
                constexpr auto node_attributes = to_value_v<node_attributes_t>;
                constexpr auto src_node_ids = to_value_v<src_node_ids_t>;
                constexpr auto dst_node_ids = to_value_v<dst_node_ids_t>;
                constexpr auto m_result = network::filter_nodes(node_attributes,src_node_ids,dst_node_ids);
                constexpr auto result   = unwrap(m_result);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                },as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_tuple_v<node_attributes_t>
                && is_constant_index_array_v<src_node_ids_t>
                && is_constant_index_array_v<dst_node_ids_t>
            ) {
                constexpr auto src_node_ids = to_value_v<src_node_ids_t>;
                constexpr auto dst_node_ids = to_value_v<dst_node_ids_t>;
                using nmtools::at, nmtools::len;
                return template_reduce<len(dst_node_ids)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    constexpr auto m_idx = index::index_of(src_node_ids,at(dst_node_ids,I));
                    using type = append_type_t<init_t,at_t<node_attributes_t,unwrap(m_idx)>>;
                    return as_value_v<type>;
                },as_value_v<nmtools_tuple<>>);
            } else {
                using value_type = get_value_type_t<node_attributes_t>;
                using value_t = conditional_t<!is_fail_v<value_type>,value_type,get_element_type_t<node_attributes_t>>;
                constexpr auto NUM_DST_NODES = len_v<dst_node_ids_t>;
                [[maybe_unused]] constexpr auto B_NUM_DST_NODES = max_len_v<dst_node_ids_t>;
                if constexpr (NUM_DST_NODES >= 0) {
                    using type = nmtools_array<value_t,NUM_DST_NODES>;
                    return as_value_v<type>;
                } else if constexpr (B_NUM_DST_NODES >= 0) {
                    using type = nmtools_static_vector<value_t,B_NUM_DST_NODES>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<value_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_NETWORK_FILTER_NODES_HPP