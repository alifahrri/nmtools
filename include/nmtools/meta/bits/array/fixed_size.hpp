#ifndef NMTOOLS_META_BITS_ARRAY_FIXED_SIZE_HPP
#define NMTOOLS_META_BITS_ARRAY_FIXED_SIZE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/array/fixed_shape.hpp"
#include "nmtools/meta/bits/traits/is_constant_index_array.hpp"
#include "nmtools/meta/bits/traits/is_num.hpp"
#include "nmtools/meta/bits/transform/to_value.hpp"
#include "nmtools/meta/bits/transform/get_value_type.hpp"
#include "nmtools/meta/bits/transform/len.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template<typename...>
        struct FIXED_SIZE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    template <typename T, typename=void>
    struct fixed_size
    {
        static constexpr auto value = [](){
            using value_t [[maybe_unused]] = get_value_type_t<T>;
            [[maybe_unused]]
            constexpr auto SIZE  = len_v<T>;
            constexpr auto SHAPE = fixed_shape_v<T>;
            using shape_t = decltype(SHAPE);
            // by default, try to compute from fixed_shape_v
            // size is actually just product of shape
            if constexpr (!is_fail_v<shape_t>) {
                auto product = 1ul;
                for (nm_size_t i=0; i<SHAPE.size(); i++) {
                    product *= SHAPE[i];
                }
                return product;
            } else if constexpr (is_num_v<value_t> && (SIZE > 0)) {
                return SIZE;
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<T>{};
            }
        }();
        using value_type = decltype(value);
    };

    template <typename T>
    struct fixed_size<const T> : fixed_size<T> {};

    template <typename T>
    struct fixed_size<T&> : fixed_size<T> {};
    
    template <template<typename...>typename Tuple, typename...Ts>
    struct fixed_size<
        Tuple<Ts...>, enable_if_t<is_tuple_v<Tuple<Ts...>>>
    >
    {
        static constexpr auto value = sizeof...(Ts);
        using value_type = decltype(value);
    }; // fixed_size
    
    template <typename T>
    constexpr inline auto fixed_size_v = fixed_size<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_FIXED_SIZE_HPP