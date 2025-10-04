#ifndef NMTOOLS_META_BITS_TRANSFORM_GET_MAYBE_TYPE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_GET_MAYBE_TYPE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/has_address_space.hpp"
#include "nmtools/meta/bits/transform/remove_address_space.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct GET_MAYBE_TYPE_UNSUPPORTED : detail::fail_t {};
    }
    /**
     * @brief Get the value type of maybe type
     * 
     * @tparam T type to check 
     * @tparam typename 
     * @todo move to transform
     */
    template <typename T, typename=void>
    struct get_maybe_type
    {
        using type = error::GET_MAYBE_TYPE_UNSUPPORTED<T>;
    };

    template <typename T>
    struct get_maybe_type<const T,enable_if_t<!has_address_space_v<T>>> : get_maybe_type<T> {};

    template <typename T>
    struct get_maybe_type<T&,enable_if_t<!has_address_space_v<T>>> : get_maybe_type<T> {};

    template <typename T>
    struct get_maybe_type<T,enable_if_t<has_address_space_v<T>>>
        : get_maybe_type<remove_address_space_t<T>> {};

    template <typename T>
    struct get_maybe_type<nullable_num<T>>
    {
        using type = T;
    };

    template <typename T>
    using get_maybe_type_t = typename get_maybe_type<T>::type;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_GET_MAYBE_TYPE_HPP