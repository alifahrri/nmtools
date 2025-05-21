#ifndef NMTOOLS_META_BITS_TRANSFORM_TUPLE_SIZE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_TUPLE_SIZE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct TUPLE_SIZE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename T, typename=void>
    struct tuple_size
    {
        static constexpr auto value = [](){
            if constexpr (is_tuple_v<T>) {

            } else {
                return error::TUPLE_SIZE_UNSUPPORTED {};
            }
        }();
    };

    template <typename T>
    constexpr inline auto tuple_size_v = tuple_size<T>::value;

    template <typename T>
    struct tuple_size<const T> : tuple_size<T> {};

    template <typename T>
    struct tuple_size<T&> : tuple_size<T> {};
}

#endif // NMTOOLS_META_BITS_TRANSFORM_TUPLE_SIZE_HPP