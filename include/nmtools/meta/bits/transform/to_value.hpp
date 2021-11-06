#ifndef NMTOOLS_META_BITS_TRANSFORM_TO_VALUE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_TO_VALUE_HPP

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
        static inline constexpr auto value = error::TO_VALUE_UNSUPPORTED<>{};
    }; // to_value

    template <typename T>
    constexpr inline auto to_value_v = to_value<T>::value;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRANSFORM_TO_VALUE_HPP