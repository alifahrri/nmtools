#ifndef NMTOOLS_META_BITS_TRAITS_HAS_TEMPLATE_GET_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_TEMPLATE_GET_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    template <typename T, auto I>
    struct has_template_get
    {
        static constexpr auto value = [](){
            using get_type = type_t<nmtools::get_t<I,T>>;
            return !is_same_v<get_type,error::TEMPLATE_GET_UNSUPPORTED<T>>;
        }();
    }; // has_template_get

    template <typename T, auto...Is>
    inline constexpr bool has_template_get_v = has_template_get<T,Is...>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_HAS_TEMPLATE_GET_HPP