#ifndef NMTOOLS_META_BITS_TRAITS_HAS_TEMPLATE_GET_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_TEMPLATE_GET_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    template <typename T, auto...Is>
    struct has_template_get : detail::expression_check<void,expr::template_get,T,std::index_sequence<Is...>> {};

    template <typename T, auto...Is>
    inline constexpr bool has_template_get_v = has_template_get<T,Is...>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_HAS_TEMPLATE_GET_HPP