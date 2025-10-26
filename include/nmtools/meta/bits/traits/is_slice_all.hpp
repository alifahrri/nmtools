#ifndef NMTOOLS_META_BITS_TRAITS_IS_SLICE_ALL_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_SLICE_ALL_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_slice_all : false_type {};

    template <template<typename...>typename tuple, typename...args_t>
    struct is_slice_all<tuple<args_t...>
        , enable_if_t<is_tuple_v<tuple<args_t...>>>
    >
    {
        using tuple_t = tuple<args_t...>;

        static constexpr auto value = [](){
            constexpr auto num_args = sizeof...(args_t);
            auto result = (num_args == 2) || (num_args == 3);
            if (result) {
                meta::template_for<num_args>([&](auto index){
                    constexpr auto I = decltype(index)::value;
                    using type_i = at_t<tuple_t,I>;
                    result = result && is_none_v<type_i>;
                });
            }
            return result;
        }();
    };

    template <typename T>
    struct is_slice_all<const T> : is_slice_all<T> {};

    template <typename T>
    struct is_slice_all<T&> : is_slice_all<T> {};

    template <typename T>
    constexpr inline auto is_slice_all_v = is_slice_all<T>::value;
}

namespace nmtools
{
    using meta::is_slice_all_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_SLICE_ALL_HPP