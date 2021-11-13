#ifndef NMTOOLS_META_BITS_TRANSFORM_ADD_REFERENCE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_ADD_REFERENCE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_void.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct add_lvalue_reference
    {
        static constexpr auto vtype = [](){
            if constexpr (is_void_v<T>) {
                return as_value_v<T>;
            } else {
                return as_value_v<T&>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // add_lvalue_reference

    template <typename T>
    using add_lvalue_reference_t = type_t<add_lvalue_reference<T>>;

    template <typename T>
    struct add_rvalue_reference
    {
        static constexpr auto vtype = [](){
            if constexpr (is_void_v<T>) {
                return as_value_v<T>;
            } else {
                return as_value_v<T&&>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // add_rvalue_reference

    template <typename T>
    using add_rvalue_reference_t = type_t<add_rvalue_reference<T>>;

    template <typename T>
    add_rvalue_reference_t<T> declval() noexcept;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_ADD_REFERENCE_HPP