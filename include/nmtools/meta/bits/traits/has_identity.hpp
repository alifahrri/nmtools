#ifndef NMTOOLS_META_BITS_TRAITS_HAS_IDENTITY_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_IDENTITY_HPP

#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    namespace expr
    {
        /**
         * @brief helper alias template to deduce the return value of member function `identity` of type `T`
         * 
         * @tparam T type to check
         */
         template <typename T>
         using identity = decltype(declval<T>().identity());
    }

    /**
     * @brief check if type `T` has member function `identity`.
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_identity : detail::expression_check<void,expr::identity,T> {};

    /**
     * @brief helper variable template to check if type `T` has member function `identity`.
     * 
     * @tparam T type to check 
     */
    template <typename T>
    nmtools_meta_variable_attribute
    inline constexpr bool has_identity_v = has_identity<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_HAS_IDENTITY_HPP