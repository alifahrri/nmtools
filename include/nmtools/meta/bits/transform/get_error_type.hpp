#ifndef NMTOOLS_META_BITS_TRANSFORM_GET_ERROR_TYPE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_GET_ERROR_TYPE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/has_error_type.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct GET_ERROR_TYPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    template <typename T>
    struct get_error_type
    {
        static constexpr auto vtype = [](){
            if constexpr (has_error_type_v<T>) {
                using type = typename T::error_type;
                return as_value_v<type>;
            } else {
                using type = error::GET_ERROR_TYPE_UNSUPPORTED<T>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename T>
    using get_error_type_t = type_t<get_error_type<T>>;
}

namespace nmtools
{
    using meta::get_error_type_t;
}

#endif // NMTOOLS_META_BITS_TRANSFORM_GET_ERROR_TYPE_HPP