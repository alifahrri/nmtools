#ifndef NMTOOLS_META_BITS_TRAITS_HAS_DATA_HPP
#define NMTOOLS_META_BITS_TRAITS_HAS_DATA_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    namespace expr
    {
        template <typename T>
        using data = decltype(declval<T>().data());
    }

    template <typename T>
    struct has_data : detail::expression_check<void,expr::data,T> {};

    template <typename T>
    inline constexpr auto has_data_v = has_data<T>::value;
}

#endif // NMTOOLS_META_BITS_TRAITS_HAS_DATA_HPP