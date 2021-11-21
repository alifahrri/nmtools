#ifndef NMTOOLS_META_BITS_TRAITS_HAS_BRACKET_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_BRACKET_HPP

#include "nmtools/meta/expr.hpp"
#include "nmtools/meta/bits/transform/add_reference.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if type `T` has `operator()` that takes `size_types...` as arguments.
     * 
     * @tparam T type to check
     * @tparam size_types arguments to `operator()`
     */
    template <typename T, typename...size_types>
    struct has_funcnd : detail::expression_check<void,expr::funcnd,T,size_types...> {};

    /**
     * @brief helper variable template to check if type `T` has `operator()` that takes `size_types...` as arguments.
     * 
     * @tparam T type to check
     * @tparam size_types arguments to `operator()`
     */
    template <typename T, typename...size_types>
    inline constexpr bool has_funcnd_v = has_funcnd<T,size_types...>::value;

    /**
     * @brief check if T has bracket operator (()) with size_type as argument
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     * @tparam typename=void 
     */
    template <typename T, typename size_type, typename=void>
    struct has_bracket : has_funcnd<T,size_type> {};

    /**
     * @brief helper variable template for has_bracket.
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     */
    template <typename T, typename size_type>
    inline constexpr bool has_bracket_v = has_bracket<T,size_type>::value;

    /**
     * @brief check if type `T` has `operator[]` that takes `size_types...` as arguments.
     * 
     * @tparam T type to check
     * @tparam size_types arguments to `operator[]`
     */
    template <typename T, typename...size_types>
    struct has_bracketnd : detail::expression_check<void,expr::bracketnd,T,size_types...> {};

    /**
     * @brief helper variable template to check if type `T` has `operator[]` that takes `size_types...` as arguments.
     * 
     * @tparam T type to check
     * @tparam size_types arguments to `operator[]`
     */
    template <typename T, typename...size_types>
    inline constexpr bool has_bracketnd_v = has_bracketnd<T,size_types...>::value;

    /**
     * @brief check if T has square bracket operator ([]) with size_type as arguments.
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     * @tparam typename=void 
     */
    template <typename T, typename size_type, typename=void>
    struct has_square_bracket2d : false_type {};

    /**
     * @brief specialization of has_square_bracket2d for true case.
     * Enabled if T has square bracket operator with size_type as argument,
     * e.g. declval<T>()[i,i], with i of type size_type, is well-formed.
     * 
     * @tparam T 
     * @tparam size_type 
     */
    template <typename T, typename size_type>
    struct has_square_bracket2d<T,size_type,
        /* note: use .operator[](i,i) so that 
            it doesn't implicitly call [] with comma operator .operator[](operator,(i,i))*/
        void_t<decltype(declval<T>().operator[](declval<size_type>(),declval<size_type>()))>
    > : true_type {};

    /**
     * @brief helper variable template for has_square_bracket2d
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     */
    template <typename T, typename size_type>
    inline constexpr bool has_square_bracket2d_v = has_square_bracket2d<T,size_type>::value;

    /**
     * @brief check if T has bracket operator (()) with size_type as argument
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     * @tparam typename=void 
     */
    template <typename T, typename size_type, typename=void>
    struct has_bracket2d : false_type {};

    /**
     * @brief specialization of has_bracket2d for true case.
     * Enabled if T has bracket operator with size_type as argument,
     * e.g. declval<T>()(i,i), with i of type size_type, is well-formed.
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     */
    template <typename T, typename size_type>
    struct has_bracket2d<T,size_type,
        void_t<decltype(declval<T>()(declval<size_type>(),declval<size_type>()))>
    > : true_type {};

    /**
     * @brief helper variable template for has_bracket2d.
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     */
    template <typename T, typename size_type>
    inline constexpr bool has_bracket2d_v = has_bracket2d<T,size_type>::value;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRAITS_HAS_BRACKET_HPP