#ifndef NMTOOLS_META_BITS_TRANSFORM_BIT_REFERENCE_TO_BOOL_HPP
#define NMTOOLS_META_BITS_TRANSFORM_BIT_REFERENCE_TO_BOOL_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_bit_reference.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct bit_reference_to_bool
    {
        static constexpr auto vtype = [](){
            if constexpr (is_bit_reference_v<T>) {
                return as_value_v<bool>;
            } else {
                return as_value_v<T>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // bit_reference_to_bool

    template <typename T>
    using bit_reference_to_bool_t = type_t<bit_reference_to_bool<T>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_BIT_REFERENCE_TO_BOOL_HPP