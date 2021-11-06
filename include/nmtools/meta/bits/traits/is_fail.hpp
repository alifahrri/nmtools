#ifndef NMTOOLS_META_BITS_TRAITS_IS_FAIL_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_FAIL_HPP

#include "nmtools/meta/common.hpp"
#include <type_traits>

namespace nmtools::meta
{
    /**
     * @brief Check if type T is fail type.
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct is_fail : std::is_base_of<detail::fail_t,T> {};

    template <typename T>
    constexpr inline auto is_fail_v = is_fail<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_FAIL_HPP