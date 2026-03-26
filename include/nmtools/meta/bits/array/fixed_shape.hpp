#ifndef NMTOOLS_META_BITS_ARRAY_FIXED_SHAPE_HPP
#define NMTOOLS_META_BITS_ARRAY_FIXED_SHAPE_HPP

#include "nmtools/meta/common.hpp"
// NOTE: to include error::FIXED_SHAPE_UNSUPPORTED
// TODO: remove
#include "nmtools/meta/bits/array/fixed_ndarray_shape.hpp"
#include "nmtools/meta/bits/traits/is_num.hpp"
#include "nmtools/meta/bits/traits/is_bounded_array.hpp"
#include "nmtools/meta/bits/transform/len.hpp"

#include "nmtools/meta/bits/traits/has_address_space.hpp"
#include "nmtools/meta/bits/transform/remove_address_space.hpp"

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

    #ifdef __OPENCL_VERSION__
    template <typename T>
    struct fixed_shape<T,enable_if_t<has_address_space_v<T>>> : fixed_shape<remove_address_space_t<T>> {};
    #endif // __OPENCL_VERSION__
} // namespace nmtools::meta

namespace nmtools
{
    using meta::fixed_shape_v;
}

#endif // NMTOOLS_META_BITS_ARRAY_FIXED_SHAPE_HPP