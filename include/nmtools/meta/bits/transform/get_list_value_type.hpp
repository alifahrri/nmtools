#ifndef NMTOOLS_META_BITS_TRANSFORM_GET_LIST_VALUE_TYPE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_GET_LIST_VALUE_TYPE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct GET_LIST_VALUE_TYPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    template <typename T>
    struct get_list_value_type
    {
        using type = error::GET_LIST_VALUE_TYPE_UNSUPPORTED<T>;
    };

    template <typename T>
    using get_list_value_type_t = type_t<get_list_value_type<T>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_GET_LIST_VALUE_TYPE_HPP