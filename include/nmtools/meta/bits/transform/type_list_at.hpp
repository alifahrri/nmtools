#ifndef NMTOOLS_META_BITS_TRANSFORM_TYPE_LIST_AT_HPP
#define NMTOOLS_META_BITS_TRANSFORM_TYPE_LIST_AT_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/transform/at.hpp"

namespace nmtools::meta
{
    /**
     * @brief "value-less" type list.
     * 
     * @tparam Ts 
     */
    template <typename...Ts>
    struct type_list {};

    template <size_t I, typename type_list_t, typename=void>
    struct type_list_at
    {
        using type = void;
    }; // type_list_at

    template <size_t I, typename T, typename...Ts>
    struct type_list_at<I,type_list<T,Ts...>>
    {
        static constexpr auto vtype = [](){
            if constexpr (I==0)
                return as_value_v<T>;
            else {
                using new_type_list = type_list<Ts...>;
                using type = type_t<type_list_at<I-1,new_type_list>>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // type_list_at

    template <size_t I, typename T>
    using type_list_at_t = type_t<type_list_at<I,T>>;

    // NOTE: gcc (9.3) complains that the following specialization (of type_at)
    // is not more specialized than the primary template when using auto specifier for I
    // while clang (10) accepts happily. So use size_t instead.

    template <typename...Ts, size_t I>
    struct type_at<type_list<Ts...>,I> : type_list_at<I,type_list<Ts...>> {};
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRANSFORM_TYPE_LIST_AT_HPP