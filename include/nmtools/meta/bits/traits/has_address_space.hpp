#ifndef NMTOOLS_META_BITS_TRAITS_HAS_ADDRESS_SPACE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_ADDRESS_SPACE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct has_address_space : false_type {};

    template <typename T>
    nmtools_meta_variable_attribute
    inline constexpr bool has_address_space_v = has_address_space<T>::value;

    #ifdef __OPENCL_VERSION__
    template <typename T>
    struct has_address_space<global T> : true_type {};

    template <typename T>
    struct has_address_space<local T> : true_type {};

    template <typename T>
    struct has_address_space<private T> : true_type {};

    template <typename T>
    struct has_address_space<constant T> : true_type {};

    template <typename T>
    struct has_address_space<generic T> : true_type {};
    #endif // __OPENCL_VERSION__
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_HAS_ADDRESS_SPACE_HPP