#ifndef NMTOOLS_META_BITS_ARRAY_FIXED_SHAPE_HPP
#define NMTOOLS_META_BITS_ARRAY_FIXED_SHAPE_HPP

#include "nmtools/meta/common.hpp"
// NOTE: to include error::FIXED_SHAPE_UNSUPPORTED
// TODO: remove
#include "nmtools/meta/bits/array/fixed_ndarray_shape.hpp"

namespace nmtools::meta
{

    template <typename T, typename=void>
    struct fixed_shape
    {
        static constexpr auto value = error::FIXED_SHAPE_UNSUPPORTED<T>{};
        using value_type = decltype(value);
    };

    template <typename T>
    struct fixed_shape<const T> : fixed_shape<T> {};

    template <typename T>
    struct fixed_shape<T&> : fixed_shape<T> {};

    template <typename T>
    constexpr inline auto fixed_shape_v = fixed_shape<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_FIXED_SHAPE_HPP