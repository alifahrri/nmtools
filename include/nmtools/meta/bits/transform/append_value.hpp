#ifndef NMTOOLS_META_BITS_TRANSFORM_APPEND_VALUE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_APPEND_VALUE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief Append new value to the end of some value type.
     * 
     * @tparam value_type some value type to be appended
     * @tparam new_value  desired new value
     */
    template <typename value_type, auto new_value>
    struct append_value
    {
        using type = void;
    }; // append_value

    template <typename value_type, auto N>
    using append_value_t = type_t<append_value<value_type,N>>;    
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_APPEND_VALUE_HPP