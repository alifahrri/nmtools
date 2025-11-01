#ifndef NMTOOLS_META_BITS_TRAITS_IS_SLICE_INDEX_ARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_SLICE_INDEX_ARRAY_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_slice_index.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/traits/has_value_type.hpp"

namespace nmtools::meta
{
    /**
     * @brief Check if type T is an array of slice index
     * 
     * @tparam T 
     */
    template <typename T, typename=void>
    struct is_slice_index_array
    {
        static constexpr auto value = [](){
            if constexpr (has_value_type_v<T>) {
                auto fixed_dim = fixed_dim_v<T>;
                if constexpr (!is_fail_v<decltype(fixed_dim)>) {
                    using value_type = typename T::value_type;
                    return !(fixed_dim > 1) && is_slice_index_v<value_type>;
                } else {
                    // NOTE: dynamic ndarray may fall to this
                    return false;
                }
            } else {
                return false;
            }
        }();
    }; // is_slice_index_array

    template <template<typename...>typename tuple, typename...args_t>
    struct is_slice_index_array<
        tuple<args_t...>, enable_if_t<is_tuple_v<tuple<args_t...>>>
    > {
        static constexpr auto value = [](){
            auto num_ellipsis = 0;
            constexpr auto N = sizeof...(args_t);
            using tuple_t = tuple<args_t...>;
            bool valid = true;
            template_for<N>([&](auto I){
                constexpr auto i = decltype(I)::value;
                using type_i = at_t<tuple_t,i>;
                if (is_ellipsis_v<type_i>) {
                    num_ellipsis++;
                }
                valid &= is_slice_index_v<type_i>;
            });
            return valid && ((num_ellipsis == 0) || (num_ellipsis == 1));
        }();
    };

    template <typename T>
    struct is_slice_index_array<const T> : is_slice_index_array<T> {};

    template <typename T>
    struct is_slice_index_array<T&> : is_slice_index_array<T> {};

    template <typename T>
    inline constexpr auto is_slice_index_array_v = is_slice_index_array<T>::value;
    
} // namespace nmtools::meta

namespace nmtools
{
    using meta::is_slice_index_array_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_SLICE_INDEX_ARRAY_HPP