#ifndef NMTOOLS_META_BITS_TRANSFORM_CONCAT_TYPE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_CONCAT_TYPE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct CONCAT_TYPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    /**
     * @brief Concatenate two type list to single type list.
     * Given List<Ts...> and List<Us...> return List<Ts...,Us...>;
     * 
     * @tparam T type list
     * @tparam U type list
     */
    template <typename T, typename U>
    struct concat_type
    {
        using type = error::CONCAT_TYPE_UNSUPPORTED<T,U>;
    }; // concat_type

    template <template<typename...>typename left_tuple, typename...Ts, template<typename...>typename right_tuple, typename...Us>
    struct concat_type<left_tuple<Ts...>,right_tuple<Us...>>
    {
        static constexpr auto vtype = [](){
            using lhs_type = left_tuple<Ts...>;
            using rhs_type = right_tuple<Us...>;
            if constexpr (is_tuple_v<lhs_type> && is_tuple_v<rhs_type>) {
                using type = left_tuple<Ts...,Us...>;
                return as_value_v<type>;
            } else {
                return as_value_v<error::CONCAT_TYPE_UNSUPPORTED<lhs_type,rhs_type>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // concat_type

    /**
     * @brief Helper type alias for concat_type
     * 
     * @tparam T type list
     * @tparam U type list
     */
    template <typename T, typename U>
    using concat_type_t = type_t<concat_type<T,U>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_CONCAT_TYPE_HPP