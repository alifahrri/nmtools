#ifndef NMTOOLS_META_BITS_TRAITS_IS_BASE_OF_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_BASE_OF_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/expr.hpp"
#include "nmtools/meta/bits/traits/is_class.hpp"

namespace nmtools::meta::internal
{
    namespace expr
    {
        template <typename Base, typename Derived>
        using ptr_convertible = decltype(static_cast<const volatile Base*>((Derived*){0}));
    } // namespace expr
    
    template <typename Base, typename Derived>
    struct is_base_of
    {
        static constexpr auto value = [](){
            auto ptr_convertible = expression_check_v<expr::ptr_convertible,Base,Derived>;
            return (ptr_convertible && is_class_v<Base> && is_class_v<Derived>);
        }();
    };
    
    template <typename Base, typename Derived>
    constexpr inline auto is_base_of_v = is_base_of<Base,Derived>::value;
} // namespace nmtools::meta::internal

#endif // NMTOOLS_META_BITS_TRAITS_IS_BASE_OF_HPP