#ifndef NMTOOLS_META_BITS_TRAITS_IS_BASE_OF_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_BASE_OF_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta::expr
{
    template <typename T>
    using has_member_pointer = decltype(T::*);
} // namespace nmtools::meta::expr

namespace nmtools::meta
{
    template <typename T>
    struct is_class
    {
        /* data */
    };
    
    template <typename T, typename U>
    struct is_base_of
    {
        
    };
    
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_BASE_OF_HPP