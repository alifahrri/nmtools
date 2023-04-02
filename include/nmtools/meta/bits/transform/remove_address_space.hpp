#ifndef NMTOOLS_META_BITS_TRANSFORM_REMOVE_ADDRESS_SPACE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_REMOVE_ADDRESS_SPACE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct remove_address_space
    {
        using type = T;
    };

    template <typename T>
    using remove_address_space_t = type_t<remove_address_space<T>>;

    #ifdef __OPENCL_VERSION__
    template <typename T>
    struct remove_address_space<global T>
    {
        using type = T;
    };

    template <typename T>
    struct remove_address_space<local T>
    {
        using type = T;
    };

    template <typename T>
    struct remove_address_space<private T>
    {
        using type = T;
    };

    template <typename T>
    struct remove_address_space<constant T>
    {
        using type = T;
    };

    template <typename T>
    struct remove_address_space<generic T>
    {
        using type = T;
    };

    #if 0
    template <typename T>
    struct remove_address_space<__global T>
    {
        using type = T;
    };

    template <typename T>
    struct remove_address_space<__local T>
    {
        using type = T;
    };

    template <typename T>
    struct remove_address_space<__private T>
    {
        using type = T;
    };

    template <typename T>
    struct remove_address_space<__constant T>
    {
        using type = T;
    };

    template <typename T>
    struct remove_address_space<__generic T>
    {
        using type = T;
    };
    #endif
    #endif // __OPENCL_VERSION__
} // namespace nmtools::meta
#endif // NMTOOLS_META_BITS_TRANSFORM_REMOVE_ADDRESS_SPACE_HPP