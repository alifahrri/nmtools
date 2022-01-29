#ifndef NMTOOLS_META_BITS_TRANSFORM_REPLACE_VALUE_TYPE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_REPLACE_VALUE_TYPE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct REPLACE_VALUE_TYPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    /**
     * @brief Replace value_type of a list type
     * 
     * @tparam list_t   existing list type
     * @tparam value_t  desired new value type
     */
    template <typename list_t, typename value_t>
    struct replace_value_type
    {
        using type = error::REPLACE_VALUE_TYPE_UNSUPPORTED<list_t,value_t>;
    };

    /**
     * @brief helper alias for replace_value_type.
     * 
     * Replace value_type of a list type
     * 
     * @tparam list_t 
     * @tparam value_t 
     */
    template <typename list_t, typename value_t>
    using replace_value_type_t = type_t<replace_value_type<list_t,value_t>>;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRANSFORM_REPLACE_VALUE_TYPE_HPP