#ifndef NMTOOLS_META_BIT_TRANSFORM_GET_ELEMENT_OR_COMMON_TYPE_HPP
#define NMTOOLS_META_BIT_TRANSFORM_GET_ELEMENT_OR_COMMON_TYPE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/transform/get_common_type.hpp"
#include "nmtools/meta/bits/transform/get_element_type.hpp"
#include "nmtools/meta/bits/traits/is_fail.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename T>
        struct GET_ELEMENT_OR_COMMON_TYPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    template <typename T, typename=void>
    struct get_element_or_common_type
    {
        static constexpr auto vtype = [](){
            using element_t = get_element_type_t<T>;
            if constexpr (is_void_v<element_t> || is_fail_v<element_t>) {
                using common_t = get_common_type_t<T>;
                if constexpr (is_void_v<common_t> || is_fail_v<common_t>) {
                    using type = error::GET_ELEMENT_OR_COMMON_TYPE_UNSUPPORTED<T>;
                    return as_value_v<type>;
                } else {
                    using type = common_t;
                    return as_value_v<type>;
                }
            } else {
                using type = element_t;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename T>
    using get_element_or_common_type_t = type_t<get_element_or_common_type<T>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BIT_TRANSFORM_GET_ELEMENT_OR_COMMON_TYPE_HPP
