#ifndef NMTOOLS_META_BITS_ARRAY_FIXED_SIZE_HPP
#define NMTOOLS_META_BITS_ARRAY_FIXED_SIZE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/array/fixed_shape.hpp"
#include "nmtools/meta/bits/traits/is_index_array.hpp"
#include "nmtools/meta/bits/traits/is_constant_index_array.hpp"
#include "nmtools/meta/bits/transform/to_value.hpp"

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
            constexpr auto shape = fixed_shape_v<T>;
            using shape_t = decltype(shape);
            // by default, try to compute from fixed_shape_v
            // size is actually just product of shape
            if constexpr (is_index_array_v<shape_t>) {
                constexpr auto shape_ = [&](){
                    if constexpr (is_constant_index_array_v<shape_t>) {
                        return to_value_v<shape_t>;
                    } else {
                        return shape;
                    }
                }();
                auto product = 1ul;
                for (size_t i=0; i<shape_.size(); i++) {
                    product *= shape_[i];
                }
                return product;
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