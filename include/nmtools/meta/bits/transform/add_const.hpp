#ifndef NMTOOLS_META_BITS_TRANSFORM_ADD_CONST_HPP
#define NMTOOLS_META_BITS_TRANSFORM_ADD_CONST_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct add_const
    {
        using type = const T;
    };

    template <typename T>
    using add_const_t = type_t<add_const<T>>;
}

#endif // NMTOOLS_META_BITS_TRANSFORM_ADD_CONST_HPP