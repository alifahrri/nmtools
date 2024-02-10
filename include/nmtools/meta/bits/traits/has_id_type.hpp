#ifndef NMTOOLS_META_BITS_TRAITS_HAS_ID_TYPE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_ID_TYPE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    namespace expr
    {
        template <typename T>
        using id_type = typename T::id_type;
    } // namespace expr

    /**
     * @brief Check if given type T has member type "id_type"
     * 
     * @tparam T 
     */
    template <typename T>
    struct has_id_type
    {
        static constexpr auto value = [](){
            using expression = detail::expression_check<void,expr::id_type,T>;
            return expression::value;
        }();
    }; // has_id_type

    /**
     * @brief Check if given type T has member type "id_type"
     * 
     * @tparam T 
     */
    template <typename T>
    inline constexpr auto has_id_type_v = has_id_type<T>::value;
    
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRAITS_HAS_ID_TYPE_HPP