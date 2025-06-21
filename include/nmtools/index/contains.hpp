#ifndef NMTOOLS_ARRAY_INDEX_CONTAINS_HPP
#define NMTOOLS_ARRAY_INDEX_CONTAINS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/isequal.hpp"

namespace nmtools::index
{
    struct contains_t {};

    template <typename array_t, typename value_t>
    constexpr auto contains(const array_t& array, const value_t& value)
    {
        if constexpr (meta::is_maybe_v<array_t>
            || meta::is_maybe_v<value_t>
        ) {
            using result_t = decltype(contains(unwrap(array),unwrap(value)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(array) && has_value(value)
                ? return_t{contains(unwrap(array),unwrap(value))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<contains_t,array_t,value_t>;

            if constexpr (!meta::is_constant_index_v<result_t> && !meta::is_fail_v<result_t>) {
                for (nm_size_t i=0; i<(nm_size_t)len(array); i++) {
                    if (utils::isequal(at(array,i),value)) {
                        return true;
                    }
                }
                return false;
            } else {
                return result_t {};
            }
        }
    } // contains
} // nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct CONTAINS_UNSUPPORTED : detail::fail_t {};
    }

    template <typename array_t, typename value_t>
    struct resolve_optype<
        void, index::contains_t, array_t, value_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_v<value_t>
                || !is_index_array_v<array_t>
            ) {
                using type = error::CONTAINS_UNSUPPORTED<array_t,value_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_v<value_t>
                && is_constant_index_array_v<array_t>
            ) {
                constexpr auto array = to_value_v<array_t>;
                constexpr auto value = to_value_v<value_t>;
                constexpr auto result = index::contains(array,value);
                using type = meta::ct<unwrap(result)>;
                return as_value_v<type>;
            } else {
                using type = bool;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_ARRAY_INDEX_CONTAINS_HPP