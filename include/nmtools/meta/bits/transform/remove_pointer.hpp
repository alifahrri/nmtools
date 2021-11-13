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
    {
        using type = T;
    };

    template <typename T>
    struct remove_pointer<T* const>
    {
        using type = T;
    };

    template <typename T>
    struct remove_pointer<T* volatile>
    {
        using type = T;
    };

    template <typename T>
    struct remove_pointer<T* const volatile>
    {
        using type = T;
    };
}

#endif // NMTOOLS_META_BITS_TRANSFORM_REMOVE_POINTER_HPP