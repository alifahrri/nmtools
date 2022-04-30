#ifndef NMTOOLS_META_BITS_ARRAY_BOUNDED_DIM_HPP
#define NMTOOLS_META_BITS_ARRAY_BOUNDED_DIM_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/array/fixed_dim.hpp"
#include "nmtools/meta/bits/traits/is_num.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template<typename...>
        struct BOUNDED_DIM_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    template <typename T, typename=void>
    struct bounded_dim
    {
        static constexpr auto value = [](){
            auto fixed_dim = fixed_dim_v<T>;
            using fixed_dim_t = decltype(fixed_dim);
            if constexpr (is_num_v<fixed_dim_t>) {
                return fixed_dim;
            } else {
                return error::BOUNDED_DIM_UNSUPPORTED<T>{};
            }
        }();
        using value_type = decltype(value);
    }; // bounded_dim

    template <typename T>
    struct bounded_dim<const T> : bounded_dim<T> {};

    template <typename T>
    struct bounded_dim<T&> : bounded_dim<T> {};

    template <typename T>
    constexpr inline auto bounded_dim_v = bounded_dim<T>::value;

} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_BOUNDED_DIM_HPP