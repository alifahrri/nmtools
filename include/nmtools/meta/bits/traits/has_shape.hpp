#ifndef NMTOOLS_META_BITS_TRAITS_HAS_SHAPE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_SHAPE_HPP

#include "nmtools/meta/expr.hpp"
#include "nmtools/meta/bits/traits/has_address_space.hpp"
#include "nmtools/meta/bits/transform/remove_address_space.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if type `T` has member function `shape`.
     * 
     * @tparam T type to check
     */
    template <typename T, typename=void>
    struct has_shape : detail::expression_check<void,expr::shape,T> {};

    template <typename T>
    struct has_shape<const T> : has_shape<T> {};

    template <typename T>
    struct has_shape<T&> : has_shape<T> {};

    template <typename T>
    struct has_shape<T,enable_if_t<has_address_space_v<T>>> : has_shape<remove_address_space_t<T>> {};

    /**
     * @brief helper variable template to check if type `T` has member function `shape`.
     * 
     * @tparam T type to check 
     */
    template <typename T>
    nmtools_meta_variable_attribute
    inline constexpr bool has_shape_v = has_shape<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_HAS_SHAPE_HPP