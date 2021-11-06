#ifndef NMTOOLS_META_BITS_TRAITS_IS_NOTHING_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_NOTHING_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief Check if type T is Nothing type (std::nullopt,..)
     * 
     * The name Nothing is from haskell maybe type
     * 
     * @tparam T 
     */
    template <typename T>
    struct is_nothing : false_type {};

    template <typename T>
    constexpr inline auto is_nothing_v = is_nothing<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_NOTHING_HPP