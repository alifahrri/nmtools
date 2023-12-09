#ifndef NMTOOLS_META_BITS_TRANSFORM_GET_COMMON_TYPE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_GET_COMMON_TYPE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/transform/common_type.hpp"
#include "nmtools/meta/bits/transform/remove_address_space.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct GET_COMMON_TYPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    template <typename T, typename=void>
    struct get_common_type
    {
        using type = error::GET_COMMON_TYPE_UNSUPPORTED<T>;
    };

    template <template<typename...>typename tuple, typename...Ts>
    struct get_common_type<tuple<Ts...>>
    {
        static constexpr auto vtype = [](){
            using tuple_t = tuple<remove_address_space_t<Ts>...>;
            if constexpr (is_tuple_v<tuple_t>) {
                using type = typename common_type<remove_address_space_t<Ts>...>::type;
                return as_value_v<type>;
            } else {
                return as_value_v<error::GET_COMMON_TYPE_UNSUPPORTED<tuple_t>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename T>
    using get_common_type_t = type_t<get_common_type<T>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_GET_COMMON_TYPE_HPP