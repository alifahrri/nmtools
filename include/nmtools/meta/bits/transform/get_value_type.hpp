#ifndef NMTOOLS_META_BITS_TRANSFORM_GET_VALUE_TYPE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_GET_VALUE_TYPE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/has_value_type.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct GET_VALUE_TYPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    template <typename T>
    struct get_value_type
    {
        static constexpr auto vtype = [](){
            if constexpr (has_value_type_v<T>) {
                using type = typename T::value_type;
                return as_value_v<type>;
            } else {
                using type = error::GET_VALUE_TYPE_UNSUPPORTED<T>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename T>
    using get_value_type_t = type_t<get_value_type<T>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_GET_VALUE_TYPE_HPP