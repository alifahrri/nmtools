#ifndef NMTOOLS_META_BITS_TRAITS_IS_SLICE_INDEX_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_SLICE_INDEX_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_index.hpp"
#include "nmtools/meta/bits/traits/is_either.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/transform/get_either.hpp"

namespace nmtools::meta
{
    /**
     * @brief Check if type T is slicing index
     * 
     * @tparam T type to check
     */
    template <typename T, typename=void>
    struct is_slice_index
    {
        static constexpr auto value = [](){
            // NOTE: Ellipsis can also be used as ":" but must only single ellipsis is allowed
            return is_index_v<T> || is_ellipsis_v<T>;
        }();
    }; // is_slice_index

    template <template<typename...>typename tuple, typename...args_t>
    struct is_slice_index<tuple<args_t...>
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
                    result = result && (is_none_v<type_i> || is_index_v<type_i>);
                });
            }
            return result;
        }();
    };

    template <typename T>
    struct is_slice_index<const T> : is_slice_index<T> {};

    template <typename T>
    struct is_slice_index<T&> : is_slice_index<T> {};

    /**
     * @brief Helper inline variable to check if type T is slicing index.
     * 
     * @tparam T 
     */
    template <typename T>
    inline constexpr auto is_slice_index_v = is_slice_index<T>::value;

    template <template<typename...>typename either_t, typename left_t, typename right_t>
    struct is_slice_index< either_t<left_t,right_t>
        , enable_if_t<is_either_v<either_t<left_t,right_t>>>
    >
    {
        static constexpr auto value = is_slice_index_v<left_t> && is_slice_index_v<right_t>;
    };
    
} // namespace nmtools::meta

namespace nmtools
{
    using meta::is_slice_index_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_SLICE_INDEX_HPP