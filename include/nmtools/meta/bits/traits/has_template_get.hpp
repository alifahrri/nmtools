#ifndef NMTOOLS_META_BITS_TRAITS_HAS_TEMPLATE_GET_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_TEMPLATE_GET_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/expr.hpp"
#include "nmtools/meta/bits/traits/is_fail.hpp"

namespace nmtools::meta
{
    template <typename T, auto I>
    struct has_template_get
    {
        static constexpr auto value = [](){
            using get_type = decltype(declval<nmtools::get_t<I,T>>()(declval<T>()));
            return !is_fail_v<get_type>;
        }();
    }; // has_template_get

    template <typename T, auto I>
    inline constexpr bool has_template_get_v = has_template_get<T,I>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_HAS_TEMPLATE_GET_HPP