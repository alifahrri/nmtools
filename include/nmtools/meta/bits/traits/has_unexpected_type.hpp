#ifndef NMTOOLS_META_BITS_TRAITS_HAS_UNEXPECTED_TYPE
#define NMTOOLS_META_BITS_TRAITS_HAS_UNEXPECTED_TYPE

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    namespace expr
    {
        template <typename T>
        using unexpected_type = typename T::unexpected_type;
    } // namespace expr

    template <typename T>
    struct has_unexpected_type : detail::expression_check<void,expr::unexpected_type,T> {};

    template <typename T>
    constexpr inline auto has_unexpected_type_v = has_unexpected_type<T>::value;
}

namespace nmtools
{
    using meta::has_unexpected_type_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_HAS_UNEXPECTED_TYPE