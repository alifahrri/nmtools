#ifndef NMTOOLS_META_BITS_TRANSFORM_TUPLE_TO_ARRAY_HPP
#define NMTOOLS_META_BITS_TRANSFORM_TUPLE_TO_ARRAY_HPP

#include "nmtools/stl.hpp"
#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/transform/get_common_type.hpp"
#include "nmtools/meta/bits/traits/is_constant_index.hpp"

namespace nmtools::meta
{
    // TODO: remove
    template <typename T, typename=void>
    struct tuple_to_array
    {
        static constexpr auto vtype = [](){
            if constexpr (is_tuple_v<T>) {
                auto element_vtype = [](){
                    using element_t = get_common_type_t<T>;
                    if constexpr (is_constant_index_v<element_t>) {
                        return as_value_v<typename element_t::value_type>;
                    } else {
                        return as_value_v<element_t>;
                    }
                }();
                using element_t = type_t<decltype(element_vtype)>;
                constexpr auto N = len_v<T>;
                return as_value_v<nmtools_array<element_t,N>>;
            } else {
                return as_value_v<T>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // tuple_to_array

    template <typename T>
    using tuple_to_array_t = type_t<tuple_to_array<T>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_TUPLE_TO_ARRAY_HPP