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
    constexpr auto map_ids(const input_t& input
        , [[maybe_unused]] const node_ids_t& node_ids)
    {
        if constexpr (meta::is_nothing_v<input_t>) {
            return input;
        } else if constexpr (meta::is_maybe_v<input_t>
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

            if constexpr (!is_none_v<result_t>
                && !meta::is_fail_v<result_t>
                && !meta::is_constant_index_v<result_t>
                && meta::is_index_v<result_t>)
            {
                using return_t = nmtools_maybe<result_t>;
                if ((nm_size_t)input >= (nm_size_t)len(node_ids)) {
                    return return_t{meta::Nothing};
                } else {
                    result = at(node_ids,input);
                    return return_t{result};
                }
            } else if constexpr (!is_none_v<result_t>
                && !meta::is_fail_v<result_t>
                && !meta::is_constant_index_array_v<result_t>
                && !meta::is_constant_adjacency_list_v<result_t>
                && !meta::is_constant_index_v<result_t>
            ) {
                auto n = len(input);
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(n);
                }

                // TODO: handle invalid input
                for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                    const auto& src = at(input,i);
                    auto& dst = at(result,i);
                    using dst_t = meta::remove_cvref_t<decltype(dst)>;
                    auto map_id = [&](auto src){
                        if constexpr (!is_none_v<node_ids_t>) {
                            return at(node_ids,src);
                        } else {
                            return src;
                        }
                    };
                    if constexpr (meta::is_index_array_v<dst_t>) {
                        auto m = len(src);
                        if constexpr (meta::is_resizable_v<dst_t>) {
                            dst.resize(m);
                        }
                        for (nm_size_t j=0; j<(nm_size_t)m; j++) {
                            at(dst,j) = map_id(at(src,j));
                        }
                    } else {
                        dst = map_id(src);
                    }
                }
                return result;
            } else {
                return result;
            }
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
            if constexpr (!(is_adjacency_list_v<input_t> || is_index_array_v<input_t> || is_index_v<input_t> || is_none_v<input_t>)
                || !(is_index_array_v<node_ids_t> || is_none_v<node_ids_t>)
            ) {
                using type = error::MAP_IDS_UNSUPPORTED<input_t,node_ids_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_v<input_t>
                && is_constant_index_array_v<node_ids_t>
            ) {
                constexpr auto input    = to_value_v<input_t>;
                constexpr auto node_ids = to_value_v<node_ids_t>;
                constexpr auto m_result = network::map_ids(input,node_ids);
                constexpr auto result   = unwrap(m_result);
                using type = ct<(nm_size_t)result>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<node_ids_t>
                && (is_constant_adjacency_list_v<input_t> || is_constant_index_array_v<input_t>)
            ) {
                constexpr auto input    = to_value_v<input_t>;
                constexpr auto node_ids = to_value_v<node_ids_t>;
                constexpr auto m_result = network::map_ids(input,node_ids);
                constexpr auto result   = unwrap(m_result);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    constexpr auto value = at(result,I);
                    if constexpr (is_index_array_v<decltype(value)>) {
                        auto inner_vtype = template_reduce<len(value)>([&](auto init, auto index){
                            using init_t = type_t<decltype(init)>;
                            constexpr auto J = decltype(index)::value;
                            using type = append_type_t<init_t,ct<at(value,J)>>;
                            return as_value_v<type>;
                        }, as_value_v<nmtools_tuple<>>);
                        using inner_t = type_t<decltype(inner_vtype)>;
                        using type = append_type_t<init_t,inner_t>;
                        return as_value_v<type>;
                    } else {
                        using type = append_type_t<init_t,ct<value>>;
                        return as_value_v<type>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else {
                // TODO: handle constant adjacency list/index array with constant node ids
                return as_value_v<input_t>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}
#endif // NMTOOLS_NETWORK_MAP_IDS_HPP