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
    struct tuple_to_array;

    template <typename T>
    using tuple_to_array_t = type_t<tuple_to_array<T>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_TUPLE_TO_ARRAY_HPP