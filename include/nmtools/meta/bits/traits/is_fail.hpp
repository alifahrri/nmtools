#ifndef NMTOOLS_META_BITS_TRAITS_IS_FAIL_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_FAIL_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_base_of.hpp"

#include "nmtools/meta/bits/traits/has_address_space.hpp"
#include "nmtools/meta/bits/transform/remove_address_space.hpp"

namespace nmtools::meta
{
    /**
     * @brief Check if type T is fail type.
     * 
     * @tparam T type to check
     */
    template <typename T, typename=void>
    struct is_fail : internal::is_base_of<detail::fail_t,T> {};

    template <typename T>
    struct is_fail<const T, enable_if_t<!has_address_space_v<T>>> : is_fail<T> {};

    template <typename T>
    struct is_fail<T&> : is_fail<T> {};

    template <typename T>
    constexpr inline auto is_fail_v = is_fail<T>::value;

    #ifdef __OPENCL_VERSION__
    template <typename T>
    struct is_fail<T,enable_if_t<has_address_space_v<T>>> : is_fail<remove_address_space_t<T>> {};
    #endif // __OPENCL_VERSION__
} // namespace nmtools::meta

namespace nmtools
{
    using meta::is_fail_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_FAIL_HPP