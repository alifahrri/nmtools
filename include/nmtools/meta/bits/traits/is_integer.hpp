#ifndef NMTOOLS_META_BITS_TRAITS_IS_INTEGER_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_INTEGER_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/has_address_space.hpp"
#include "nmtools/meta/bits/transform/remove_address_space.hpp"

namespace nmtools::meta
{
    /**
     * @brief Check if type T is integer type.
     * 
     * Note that specializing std's is_integral is undefined behaviour.
     * This traits exists to avoid UB while specializing similar concept is allowed.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_integer
    {
        // use static member var IILE to avoid specialization,
        // which must be exclusive.
        // somehow on some platform (arm 32-bit none, gcc 9.2 & 10.2),
        // must specialize on int and int32_t, which trigger error on linux platform
        // see:
        // doesn't work on embedded, works on linux: https://godbolt.org/z/186Ex9Eeq
        // doesn't work on linux, works on embedded: https://godbolt.org/z/hfr7e6fbM
        static constexpr auto value = [](){
            // NOTE: following std, integral_constant is not considered as integral/integer trait
            return is_same_v<T,bool>
                || is_same_v<T,char>
                || is_same_v<T,int>
                || is_same_v<T,long>
                || is_same_v<T,long long>
                || is_same_v<T,unsigned char>
                || is_same_v<T,unsigned int>
                || is_same_v<T,unsigned long>
                || is_same_v<T,unsigned long long>
                || is_same_v<T,::nmtools::int8_t>
                || is_same_v<T,::nmtools::int16_t>
                || is_same_v<T,::nmtools::int32_t>
                || is_same_v<T,::nmtools::int64_t>
                || is_same_v<T,::nmtools::uint8_t>
                || is_same_v<T,::nmtools::uint16_t>
                || is_same_v<T,::nmtools::uint32_t>
                || is_same_v<T,::nmtools::uint64_t>;
        }();
    };

    template <typename T>
    constexpr inline auto is_integer_v = is_integer<T>::value;

    template <typename T, auto Min, auto Max>
    struct is_integer<clipped_integer_t<T,Min,Max>,enable_if_t<is_integer_v<T>>> : true_type {};

    template <typename T>
    struct is_integer<const T> : is_integer<T> {};

    template <typename T>
    struct is_integer<T&> : is_integer<T> {};

    template <typename T, typename=void>
    struct is_integral : is_integer<T> {};

    #ifdef __OPENCL_VERSION__
    template <typename T>
    struct is_integer<T,enable_if_t<has_address_space_v<T>>> : is_integer<remove_address_space_t<T>> {};
    #endif // __OPENCL_VERSION__

    template <typename T>
    constexpr inline auto is_integral_v = is_integral<T>::value;

/* see primary templates for notes */

/*
#define NMTOOLS_IS_INTEGER_TRAIT(type) \
    template <> \
    struct is_integer<type> : true_type {};

    // following stl, boolean is also integer
    NMTOOLS_IS_INTEGER_TRAIT(bool)

    NMTOOLS_IS_INTEGER_TRAIT(char)

    NMTOOLS_IS_INTEGER_TRAIT(::nmtools::int8_t)
    NMTOOLS_IS_INTEGER_TRAIT(::nmtools::int16_t)
    NMTOOLS_IS_INTEGER_TRAIT(::nmtools::int32_t)
    NMTOOLS_IS_INTEGER_TRAIT(::nmtools::int64_t)
    NMTOOLS_IS_INTEGER_TRAIT(::nmtools::uint8_t)
    NMTOOLS_IS_INTEGER_TRAIT(::nmtools::uint16_t)
    NMTOOLS_IS_INTEGER_TRAIT(::nmtools::uint32_t)
    NMTOOLS_IS_INTEGER_TRAIT(::nmtools::uint64_t)

    // size_t length may be different type on different platform
    // as well as int type
    NMTOOLS_IS_INTEGER_TRAIT(::nmtools::size_t)
    NMTOOLS_IS_INTEGER_TRAIT(int)

    // NMTOOLS_IS_INTEGER_TRAIT(long long)
    // NMTOOLS_IS_INTEGER_TRAIT(unsigned long long)

#undef NMTOOLS_IS_INTEGER_TRAIT
*/

} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_INTEGER_HPP