#ifndef NMTOOLS_META_BITS_TRAITS_HAS_ERROR_TYPE_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_ERROR_TYPE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    namespace expr
    {
        template <typename T>
        using error_type = typename T::error_type;
    } // namespace expr

    template <typename T>
    struct has_error_type : detail::expression_check<void,expr::error_type,T> {};

    template <typename T>
    constexpr inline auto has_error_type_v = has_error_type<T>::value;
}

namespace nmtools
{
    using meta::has_error_type_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_HAS_ERROR_TYPE_HPP