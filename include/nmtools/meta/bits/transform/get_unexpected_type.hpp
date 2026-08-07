#ifndef NMTOOLS_META_BITS_TRANSFORM_GET_UNEXPECTED_TYPE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_GET_UNEXPECTED_TYPE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/has_unexpected_type.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct GET_UNEXPECTED_TYPE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename T>
    struct get_unexpected_type
    {
        static constexpr auto vtype = [](){
            if constexpr (has_unexpected_type_v<T>) {
                using type = typename T::unexpected_type;
                return as_value_v<type>;
            } else {
                using type = error::GET_UNEXPECTED_TYPE_UNSUPPORTED<T>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename T>
    using get_unexpected_type_t = type_t<get_unexpected_type<T>>;
}

namespace nmtools
{
    using meta::get_unexpected_type_t;
}

#endif // NMTOOLS_META_BITS_TRANSFORM_GET_UNEXPECTED_TYPE_HPP