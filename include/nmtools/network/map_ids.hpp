#ifndef NMTOOLS_NETWORK_MAP_IDS_HPP
#define NMTOOLS_NETWORK_MAP_IDS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"

namespace nmtools::tag
{
    struct map_ids_t {};
}

namespace nmtools::network
{
    template <typename input_t, typename node_ids_t>
    constexpr auto map_ids(const input_t& input, const node_ids_t& node_ids)
    {
        if constexpr (meta::is_maybe_v<input_t>
            || meta::is_maybe_v<node_ids_t>
        ) {
            using result_t = decltype(map_ids(unwrap(input),unwrap(node_ids)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(input) && has_value(node_ids)
                ? return_t{map_ids(unwrap(input),unwrap(node_ids))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<tag::map_ids_t,input_t,node_ids_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_index_array_v<result_t>
                && !meta::is_constant_adjacency_list_v<result_t>
            ) {
                auto n = len(input);
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(n);
                }

                for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                    const auto& src = at(input,i);
                    auto& dst = at(result,i);
                    using dst_t = meta::remove_cvref_t<decltype(dst)>;
                    if constexpr (meta::is_index_array_v<dst_t>) {
                        auto m = len(src);
                        if constexpr (meta::is_resizable_v<dst_t>) {
                            dst.resize(m);
                        }
                        for (nm_size_t j=0; j<(nm_size_t)m; j++) {
                            at(dst,j) = at(node_ids,at(src,j));
                        }
                    } else {
                        dst = at(node_ids,src);
                    }
                }
            }

            return result;
        }
    } // map_ids
} // nmtools::network

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct MAP_IDS_UNSUPPORTED : detail::fail_t {};
    }

    template <typename input_t, typename node_ids_t>
    struct resolve_optype<
        void, tag::map_ids_t, input_t, node_ids_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!(is_adjacency_list_v<input_t> || is_index_array_v<input_t>)
                || !is_index_array_v<node_ids_t>
            ) {
                using type = error::MAP_IDS_UNSUPPORTED<input_t,node_ids_t>;
                return as_value_v<type>;
            } else {
                // TODO: handle constant adjacency list/index array with constant node ids
                return as_value_v<input_t>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}
#endif // NMTOOLS_NETWORK_MAP_IDS_HPP