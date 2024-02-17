#ifndef NMTOOLS_META_BITS_TRANSFORM_REMOVE_POINTER_HPP
#define NMTOOLS_META_BITS_TRANSFORM_REMOVE_POINTER_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct remove_pointer
    {
        using type = T;
    };

    template <typename T>
    using remove_pointer_t = type_t<remove_pointer<T>>;

    template <typename T>
    struct remove_pointer<T*>
        : remove_pointer<T> {};

    template <typename T>
    struct remove_pointer<const T*>
        : remove_pointer<T> {};

    template <typename T>
    struct remove_pointer<T* volatile>
        : remove_pointer<T> {};

    template <typename T>
    struct remove_pointer<T* const volatile>
        : remove_pointer<T> {};
}

#endif // NMTOOLS_META_BITS_TRANSFORM_REMOVE_POINTER_HPP