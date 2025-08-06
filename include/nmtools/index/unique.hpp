#ifndef NMTOOLS_INDEX_UNIQUE_HPP
#define NMTOOLS_INDEX_UNIQUE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/index_of.hpp"

namespace nmtools::index
{
    struct unique_t {};

    template <typename index_array_t>
    constexpr auto unique(const index_array_t& array)
    {
        if constexpr (meta::is_maybe_v<index_array_t>) {
            using result_t = decltype(unique(unwrap(array)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(array)
                ? return_t{unique(unwrap(array))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<unique_t,index_array_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_index_array_v<result_t>
            ) {
                // assume has push_back
                auto n = len(array);
                for (nm_size_t i=0; i<(nm_size_t)n; i++) {
                    auto v = at(array,i);
                    auto idx = index_of(result,v);
                    if (!has_value(idx)) {
                        result.push_back(v);
                    }
                }
            }

            return result;
        }
    } // unique
}

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct UNIQUE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename index_array_t>
    struct resolve_optype<
        void, index::unique_t, index_array_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<index_array_t>) {
                using type = error::UNIQUE_UNSUPPORTED<index_array_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<index_array_t>) {
                constexpr auto list   = to_value_v<index_array_t>;
                constexpr auto result = index::unique(list);
                using ::nmtools::at, ::nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                using index_t = get_index_element_type_t<index_array_t>;
                constexpr auto B_SIZE = max_len_v<index_array_t>;
                if constexpr (B_SIZE >= 0) {
                    using type = nmtools_static_vector<index_t,B_SIZE>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_INDEX_UNIQUE_HPP