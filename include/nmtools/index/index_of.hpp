#ifndef NMTOOLS_INDEX_INDEX_OF_HPP
#define NMTOOLS_INDEX_INDEX_OF_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"

namespace nmtools::index
{
    struct index_of_t {};

    template <typename list_t, typename value_t>
    constexpr auto index_of(const list_t& list, value_t value)
    {
        if constexpr (meta::is_maybe_v<list_t>
            || meta::is_maybe_v<value_t>
        ) {
            using result_t = decltype(index_of(unwrap(list),unwrap(value)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(list) && has_value(value)
                ? return_t{index_of(unwrap(list),unwrap(value))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<index_of_t,list_t,value_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_index_v<result_t>
                && meta::is_index_v<result_t>
            ) {
                using return_t = nmtools_maybe<result_t>;

                auto size  = len(list);
                auto found = false;
                for (nm_size_t i=0; i<(nm_size_t)size; i++) {
                    if ((value_t)at(list,i) == value) {
                        found = true;
                        result = i;
                        break;
                    }
                }

                if (found) {
                    return return_t{result};
                } else {
                    return return_t{meta::Nothing};
                }
            } else if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_index_v<result_t>
                && meta::is_index_array_v<result_t>
            ) {
                using return_t = nmtools_maybe<result_t>;

                auto size = len(value);
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(size);
                }
                auto all_found = true;
                for (nm_size_t i=0; (i<(nm_size_t)size) && all_found; i++) {
                    auto v = at(value,i);
                    auto idx = index_of(list,v);
                    all_found &= has_value(idx);
                    if (has_value(idx)) {
                        at(result,i) = unwrap(idx);
                    }
                }
                if (all_found) {
                    return return_t{result};
                } else {
                    return return_t{meta::Nothing};
                }
            } else {
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
        struct INDEX_OF_UNSUPPORTED : detail::fail_t {};
    }

    template <typename list_t, typename value_t>
    struct resolve_optype<
        void, index::index_of_t, list_t, value_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<list_t>
                || !(is_index_v<value_t> || is_index_array_v<value_t>)
            ) {
                using type = error::INDEX_OF_UNSUPPORTED<list_t,value_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<value_t>
                && is_constant_index_array_v<list_t>
            ) {
                constexpr auto list     = to_value_v<list_t>;
                constexpr auto value    = to_value_v<value_t>;
                constexpr auto m_result = index::index_of(list,value);
                constexpr auto result   = unwrap(m_result);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    using type = append_type_t<init_t,ct<(nm_size_t)at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_constant_index_v<value_t>
                && is_constant_index_array_v<list_t>
            ) {
                constexpr auto list     = to_value_v<list_t>;
                constexpr auto value    = to_value_v<value_t>;
                constexpr auto m_result = index::index_of(list,value);
                constexpr auto result   = unwrap(m_result);
                using type = ct<result>;
                return as_value_v<type>;
            } else if constexpr (is_index_array_v<value_t>) {
                [[maybe_unused]]
                constexpr auto B_DIM = max_len_v<value_t>;
                constexpr auto DIM = len_v<value_t>;
                if constexpr (DIM >= 0) {
                    using type = nmtools_array<nm_size_t,DIM>;
                    return as_value_v<type>;
                } else if constexpr (B_DIM >= 0) {
                    using type = nmtools_static_vector<nm_size_t,B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            } else {
                using type = nm_size_t;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_INDEX_INDEX_OF_HPP