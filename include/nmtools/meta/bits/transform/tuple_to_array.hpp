#ifndef NMTOOLS_META_BITS_TRANSFORM_TUPLE_TO_ARRAY_HPP
#define NMTOOLS_META_BITS_TRANSFORM_TUPLE_TO_ARRAY_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct tuple_to_array
    {
        using type = T;
    }; // tuple_to_array

    template <typename T>
    using tuple_to_array_t = type_t<tuple_to_array<T>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_TUPLE_TO_ARRAY_HPP