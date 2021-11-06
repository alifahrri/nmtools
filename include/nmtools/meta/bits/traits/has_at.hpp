#ifndef NMTOOLS_META_BITS_TRAITS_HAS_AT_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_AT_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/expr.hpp"
#include <type_traits>

namespace nmtools::meta
{
    /**
     * @brief check if type T has operator at with size_type as single argument.
     * 
     * @tparam T type to check.
     * @tparam size_type argument type.
     * @tparam typename=void 
     */
    template <typename T, typename size_type, typename=void>
    struct has_at : false_type {};

    // TODO: cleanup metafunctions
    /**
     * @brief specialization of has_at for true case.
     * Enabled if T has operator at with size_type as single argument,
     * e.g. declval<T>().at(i), with i of size_type, is well-formed.
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     */
    template <typename T, typename size_type>
    struct has_at<T,size_type,
        std::void_t<decltype(std::declval<T>().at(std::declval<size_type>()))>
    > : true_type {};

    /**
     * @brief helper variable template for has_at
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     */
    template <typename T, typename size_type>
    inline constexpr bool has_at_v = has_at<T,size_type>::value;

    /**
     * @brief check if T has member function `at` that takes `size_types...` as arguments.
     * 
     * @tparam T type to check
     * @tparam size_types arguments to `at`
     * @see nmtools::meta::expr::has_atnd
     * @see nmtools::meta::detail::expression_check
     */
    template <typename T, typename...size_types>
    struct has_atnd : detail::expression_check<void,expr::atnd,T,size_types...> {};

    /**
     * @brief helper variable template to check if T has member function `at` that takes `size_types...` as arguments.
     * 
     * @tparam T type to check
     * @tparam size_types arguments to `at`
     * @see nmtools::meta::has_atnd
     */
    template <typename T, typename...size_types>
    inline constexpr bool has_atnd_v = has_atnd<T,size_types...>::value;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRAITS_HAS_AT_HPP