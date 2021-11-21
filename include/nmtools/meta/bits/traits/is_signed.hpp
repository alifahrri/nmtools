#ifndef NMTOOLS_META_BITS_TRAITS_IS_SIGNED_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_SIGNED_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_signed : false_type {};

// TODO: do not use true_type / false_type, define value instead
#define NMTOOLS_META_REGISTER_IS_SIGNED(type, signed) \
    template <> \
    struct is_signed<type> : signed##_type {}; \

    NMTOOLS_META_REGISTER_IS_SIGNED(int32_t,true);
    NMTOOLS_META_REGISTER_IS_SIGNED(int64_t,true);
    NMTOOLS_META_REGISTER_IS_SIGNED(int16_t,true);
    NMTOOLS_META_REGISTER_IS_SIGNED(int8_t, true);

    NMTOOLS_META_REGISTER_IS_SIGNED(uint32_t,false);
    NMTOOLS_META_REGISTER_IS_SIGNED(uint64_t,false);
    NMTOOLS_META_REGISTER_IS_SIGNED(uint16_t,false);
    NMTOOLS_META_REGISTER_IS_SIGNED(uint8_t, false);

#undef NMTOOLS_META_REGISTER_IS_SIGNED

    template <typename T, T v>
    struct is_signed<integral_constant<T,v>> : is_signed<T> {};

    template <typename T>
    inline constexpr auto is_signed_v = is_signed<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_SIGNED_HPP