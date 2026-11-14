#ifndef NMTOOLS_INDEX_INVERT_MAP_HPP
#define NMTOOLS_INDEX_INVERT_MAP_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/has_value.hpp"
#include "nmtools/utl/constant_map.hpp"

namespace nmtools::index
{
    struct invert_map_t {};

    template <typename map_t>
    constexpr auto invert_map(const map_t& map)
    {
        using result_t = resolve_optype_t<invert_map_t,map_t>;

        auto result = result_t {};

        if constexpr (!is_fail_v<result_t>
            && !is_constant_map_v<result_t>
        ) {
            for (const auto& [key,value] : map) {
                if (has_value(value)) {
                    result[value] = key;
                }
                // TODO: handle null value
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
        struct INVERT_MAP_UNSUPPORTED : detail::fail_t {};
    }

    template <typename map_t>
    struct resolve_optype<
        void, index::invert_map_t, map_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_map_v<map_t>) {
                using type = error::INVERT_MAP_UNSUPPORTED<map_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_map_v<map_t>) {
                constexpr auto map = to_value_v<map_t>;
                constexpr auto result = index::invert_map(map);
                // convert back to constant map
                constexpr auto N = result.size();
                using nmtools::at;
                constexpr auto keys_vtype = template_reduce<N>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    using init_t = type_t<decltype(init)>;
                    constexpr auto key = at(result.keys(),I);
                    if constexpr (has_value(key)) {
                        // TODO: proper cast to underlying key type
                        using type = append_type_t<init_t,ct<(nm_size_t)key>>;
                        return as_value_v<type>;
                    } else {
                        using type = init_t;
                        return as_value_v<type>;
                    }
                }, as_value_v<nmtools_tuple<>>);
                constexpr auto values_vtype = template_reduce<N>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    using init_t = type_t<decltype(init)>;
                    // assume value is index
                    // TODO: handle non-index value
                    constexpr auto key = at(result.keys(),I);
                    constexpr auto value = result[key];
                    // skip rt value for now
                    // TODO: handle null value
                    if constexpr (has_value(value)) {
                        using type = append_type_t<init_t,ct<value>>;
                        return as_value_v<type>;
                    } else {
                        using type = init_t;
                        return as_value_v<type>;
                    }
                }, as_value_v<nmtools_tuple<>>);
                using keys_t   = type_t<decltype(keys_vtype)>;
                using values_t = type_t<decltype(values_vtype)>;
                // already inverted
                using type = utl::constant_map<keys_t,values_t>;
                return as_value_v<type>;
            } else {
                // TODO: specialize on constant map
                using key_t   = typename map_t::key_type;
                using value_t = typename map_t::mapped_type;
                constexpr auto MAX_LEN = max_len_v<map_t>;
                if constexpr (MAX_LEN > 0) {
                    using type = utl::static_map<value_t,key_t,MAX_LEN>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_default_map<value_t,key_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_INDEX_INVERT_MAP_HPP