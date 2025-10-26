#ifndef NMTOOLS_META_BITS_TRAITS_IS_ASSIGNABLE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_ASSIGNABLE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/expr.hpp"

namespace nmtools::meta
{
    namespace expr
    {
        template <typename T, typename U>
        using assign = decltype(meta::declval<T>() = meta::declval<U>());
    } // namespace expr

    template <typename T, typename U>
    struct is_assignable
    {
        static constexpr auto value = [](){
            using expression = detail::expression_check<void,expr::assign,T,U>;
            return expression::value;
        }();
    }; // is_assignable

    template <typename T, typename U>
    inline constexpr auto is_assignable_v = is_assignable<T,U>::value;
} // namespace nmtools::meta

namespace nmtools
{
    using meta::is_assignable_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_ASSIGNABLE_HPP