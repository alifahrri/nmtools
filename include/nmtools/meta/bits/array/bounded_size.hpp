#ifndef NMTOOLS_META_BITS_ARRAY_BOUNDED_SIZE_HPP
#define NMTOOLS_META_BITS_ARRAY_BOUNDED_SIZE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/array/fixed_size.hpp"
#include "nmtools/meta/bits/traits/is_num.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template<typename...>
        struct BOUNDED_SIZE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    template <typename T, typename=void>
    struct bounded_size
    {
        static constexpr auto value = [](){
            auto fixed_size = fixed_size_v<T>;
            if constexpr (is_num_v<decltype(fixed_size)>) {
                return fixed_size;
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED<T>{};
            }
        }();
        using value_type = decltype(value);
    };

    template <typename T>
    struct bounded_size<const T> : bounded_size<T> {};

    template <typename T>
    struct bounded_size<T&> : bounded_size<T> {};
    
    template <typename T>
    constexpr inline auto bounded_size_v = bounded_size<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_BOUNDED_SIZE_HPP