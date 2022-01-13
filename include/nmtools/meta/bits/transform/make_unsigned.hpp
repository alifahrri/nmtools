#ifndef NMTOOLS_META_BITS_TRANSFORM_MAKE_UNSIGNED_HPP
#define NMTOOLS_META_BITS_TRANSFORM_MAKE_UNSIGNED_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/def.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct make_unsigned
    {
        using type = T;
    };

    template <typename T>
    using make_unsigned_t = type_t<make_unsigned<T>>;

    template <>
    struct make_unsigned<int8_t>
    {
        using type = uint8_t;
    };

    template <>
    struct make_unsigned<int16_t>
    {
        using type = uint16_t;
    };

    template <>
    struct make_unsigned<int32_t>
    {
        using type = uint32_t;
    };

    template <>
    struct make_unsigned<int64_t>
    {
        using type = uint64_t;
    };

} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_MAKE_UNSIGNED_HPP