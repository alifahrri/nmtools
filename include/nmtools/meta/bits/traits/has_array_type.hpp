#ifndef NMTOOLS_META_BITS_TRAITS_HAS_ARRAY_TYPE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_ARRAY_TYPE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    namespace expr
    {
        template <typename T>
        using array_type = typename T::array_type;
    } // namespace expr

    /**
     * @brief Check if given type T has member type "array_type"
     * 
     * @tparam T 
     */
    template <typename T>
    struct has_array_type
    {
        static constexpr auto value = [](){
            using expression = detail::expression_check<void,expr::array_type,T>;
            return expression::value;
        }();
    }; // has_array_type

    /**
     * @brief Check if given type T has member type "array_type"
     * 
     * @tparam T 
     */
    template <typename T>
    inline constexpr auto has_array_type_v = has_array_type<T>::value;
    
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRAITS_HAS_ARRAY_TYPE_HPP