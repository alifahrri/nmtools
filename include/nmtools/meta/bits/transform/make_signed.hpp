#ifndef NMTOOLS_META_BITS_TRANSFORM_MAKE_SIGNED_HPP
#define NMTOOLS_META_BITS_TRANSFORM_MAKE_SIGNED_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/def.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct make_signed
    {
        static constexpr auto vtype = [](){
            if constexpr (is_same_v<T,unsigned int>) {
                return as_value_v<int>;
            } else if constexpr (is_same_v<T,unsigned long>) {
                return as_value_v<long>;
            } else if constexpr (is_same_v<T,unsigned long long>) {
                return as_value_v<long long>;
            } else if constexpr (is_same_v<T,unsigned char>) {
                return as_value_v<char>;
            } else if constexpr (is_same_v<T,::nmtools::uint8_t>) {
                return as_value_v<::nmtools::int8_t>;
            } else if constexpr (is_same_v<T,::nmtools::uint16_t>) {
                return as_value_v<::nmtools::int16_t>;
            } else if constexpr (is_same_v<T,::nmtools::uint32_t>) {
                return as_value_v<::nmtools::int32_t>;
            } else if constexpr (is_same_v<T,::nmtools::uint64_t>) {
                return as_value_v<::nmtools::int64_t>;
            } else {
                return as_value_v<T>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename T>
    using make_signed_t = type_t<make_signed<T>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_MAKE_SIGNED_HPP