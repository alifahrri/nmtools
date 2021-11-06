#ifndef NMTOOLS_META_BITS_TRAITS_HAS_SQUARE_BRACKET_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_SQUARE_BRACKET_HPP

#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if type T can be indexed.
     * 
     * @tparam T type to check
     * @tparam size_type argument type to indexing subscript
     * @tparam typename customization point
     * @see expr::square_bracket
     */
    template <typename T, typename size_type, typename=void>
    struct has_square_bracket
    {
        /**
         * @brief check using expression checker
         * 
         * @return constexpr auto 
         */
        static constexpr auto value = [](){
            using expression = detail::expression_check<void,expr::square_bracket,T,size_type>;
            if constexpr (expression::value)
                return true;
            else return false;
        }();
    }; // has_square_bracket

    /**
     * @brief helper variable template for has_square_bracket
     * 
     * @tparam T type to check
     * @tparam size_type argument type to indexing subscript
     */
    template <typename T, typename size_type>
    inline constexpr bool has_square_bracket_v = has_square_bracket<T,size_type>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_HAS_SQUARE_BRACKET_HPP