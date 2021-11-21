#ifndef NMTOOLS_META_BITS_TRANSFORM_TO_VALUE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_TO_VALUE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct TO_VALUE_UNSUPPORTED : detail::fail_t {};
    }

    /**
     * @brief Convert constant index to value
     * 
     * If T is tuple, it is expected to transform to array
     * for easy handling as value.
     * 
     * @tparam T 
     */
    template <typename T>
    struct to_value
    {
        static inline constexpr auto value = error::TO_VALUE_UNSUPPORTED<T>{};
    }; // to_value

    template <typename T, T v>
    struct to_value<integral_constant<T,v>>
    {
        static constexpr auto value = v;
    };

    // nmtools' true_type & false_type is not an alias to integral_constant
    template <> struct to_value<true_type>
    { static constexpr auto value = true; };

    template <> struct to_value<false_type>
    { static constexpr auto value = false; };
    

    template <typename T>
    constexpr inline auto to_value_v = to_value<T>::value;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRANSFORM_TO_VALUE_HPP