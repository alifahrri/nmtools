#ifndef NMTOOLS_META_BITS_TRANSFORM_REMOVE_CONST_HPP
#define NMTOOLS_META_BITS_TRANSFORM_REMOVE_CONST_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct remove_const
    {
        using type = T;
    }; // remove_const

    template <typename T>
    using remove_const_t = type_t<remove_const<T>>;

    template <typename T>
    struct remove_const<const T>
    {
        using type = T;
    }; // remove_const

    template <typename T>
    struct remove_const<T&>
    {
        using type = remove_const_t<T>&;
    };
    
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRANSFORM_REMOVE_CONST_HPP