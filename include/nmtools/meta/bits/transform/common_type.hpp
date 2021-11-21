#ifndef NMTOOLS_META_BITS_TRANSFORM_COMMON_TYPE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_COMMON_TYPE_HPP

#include "nmtools/meta/bits/traits/is_integer.hpp"
#include "nmtools/meta/bits/traits/is_integral_constant.hpp"
#include "nmtools/meta/bits/traits/is_num.hpp"
#include "nmtools/meta/loop.hpp"
#include "nmtools/meta/bits/transform/at.hpp"
#include "nmtools/meta/bits/transform/type_list_at.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct COMMON_TYPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    /**
     * @brief Check if we can static_cast from type T to type U.
     * 
     * @tparam T 
     * @tparam U 
     * @tparam typename 
     */
    template <typename T, typename U, typename=void>
    struct can_cast : false_type {};

    template <typename T, typename U>
    struct can_cast<T,U,void_t<decltype(static_cast<U>(declval<T>()))>> : true_type {};

    template <typename T, typename U>
    constexpr inline auto can_cast_v = can_cast<T,U>::value;

    /**
     * @brief Deduce common type of numeric type lhs_t with the rest rest_t...
     * 
     * @tparam lhs_t 
     * @tparam rest_t 
     */
    template <typename lhs_t, typename...rest_t>
    struct common_type
    {
        template <typename left_t, typename right_t>
        static constexpr auto cast(as_value<left_t>, as_value<right_t>)
        {
            [[maybe_unused]] constexpr auto l_size = sizeof(left_t);
            [[maybe_unused]] constexpr auto r_size = sizeof(right_t);
            if constexpr (is_integer_v<left_t> && is_floating_point_v<right_t>) {
                return as_value_v<right_t>;
            } else if constexpr (is_floating_point_v<left_t> && is_integer_v<right_t>) {
                return as_value_v<left_t>;
            } else if constexpr (is_integral_constant_v<left_t> && is_num_v<right_t>) {
                // also check if we can cast right to left's value_type
                using value_type = typename left_t::value_type;
                if constexpr (can_cast_v<right_t,value_type>) {
                    return as_value_v<right_t>;
                } else {
                    return as_value_v<value_type>;
                }
            } else if constexpr (is_num_v<left_t> && is_integral_constant_v<right_t>) {
                using value_type = typename right_t::value_type;
                if constexpr (can_cast_v<left_t,value_type>) {
                    return as_value_v<left_t>;
                } else {
                    return as_value_v<value_type>;
                }
            } else if constexpr (is_num_v<left_t> && is_num_v<right_t>) {
                // other than size check, also check if can actually cast
                // such case may happen for view type
                constexpr auto l2r_cast = can_cast_v<left_t,right_t>;
                constexpr auto r2l_cast = can_cast_v<right_t,left_t>;
                if constexpr (l2r_cast && r2l_cast) {
                    if constexpr (l_size > r_size) {
                        return as_value_v<left_t>;
                    } else {
                        return as_value_v<right_t>;
                    }
                } else if constexpr (l2r_cast) {
                    return as_value_v<right_t>;
                } else /* if constexpr (r2l_cast) */ {
                    return as_value_v<left_t>;
                }
            } else {
                return as_value_v<error::COMMON_TYPE_UNSUPPORTED<left_t,right_t>>;
            }
        }

        static constexpr auto vtype = [](){
            using types  = type_list<rest_t...>;
            return template_reduce<sizeof...(rest_t)>([](auto init, auto index){
                constexpr auto i = decltype(index)::value;
                using type_i = at_t<types,i>;
                return cast(init,as_value_v<type_i>);
            }, as_value_v<lhs_t>);
        }();
        
        using type = type_t<decltype(vtype)>;
    }; // common_type

    template <typename lhs_t, typename...rest_t>
    using common_type_t = type_t<common_type<lhs_t,rest_t...>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_COMMON_TYPE_HPP