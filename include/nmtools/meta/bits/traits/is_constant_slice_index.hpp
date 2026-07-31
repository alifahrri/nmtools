#ifndef NMTOOLS_META_BITS_TRAITS_IS_CONSTANT_SLICE_INDEX_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_CONSTANT_SLICE_INDEX_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_constant_index.hpp"
#include "nmtools/meta/bits/traits/is_either.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/transform/get_either.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_constant_slice_index
    {
        static constexpr auto value = is_constant_index_v<T> || is_ellipsis_v<T>;
    };

    template <template<typename...>typename tuple, typename...args_t>
    struct is_constant_slice_index<tuple<args_t...>
        , enable_if_t<is_tuple_v<tuple<args_t...>>>
    > {
        using tuple_type = tuple<args_t...>;

        static constexpr auto value = [](){
            constexpr auto num_args = sizeof...(args_t);
            auto result = (num_args == 2) || (num_args == 3);
            if (result) {
                template_for<num_args>([&](auto index){
                    constexpr auto I = decltype(index)::value;
                    using type_i = at_t<tuple_type,I>;
                    result = result && (is_none_v<type_i> || is_constant_index_v<type_i>);
                });
            }
            return result;
        }();
    };

    template <typename T>
    struct is_constant_slice_index<const T> : is_constant_slice_index<T> {};

    template <typename T>
    struct is_constant_slice_index<T&> : is_constant_slice_index<T> {};

    template <typename T>
    constexpr inline auto is_constant_slice_index_v = is_constant_slice_index<T>::value;
}

namespace nmtools
{
    using meta::is_constant_slice_index_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_CONSTANT_SLICE_INDEX_HPP