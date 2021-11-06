#ifndef NMTOOLS_META_BITS_TRANSFORM_GET_EITHER_HPP
#define NMTOOLS_META_BITS_TRANSFORM_GET_EITHER_HPP

namespace nmtools::meta
{
    namespace error
    {
        struct GET_EITHER_LEFT_UNSUPPORTED : detail::fail_t {};
        struct GET_EITHER_RIGHT_UNSUPPORTED : detail::fail_t {};
    }

    /**
     * @brief Get the Left type of Either
     * 
     * @tparam T 
     * @todo move to transform
     */
    template <typename T>
    struct get_either_left
    {
        using type = error::GET_EITHER_LEFT_UNSUPPORTED;
    };

    /**
     * @brief Get the Right type of Either
     * 
     * @tparam T 
     * @todo move to transform
     */
    template <typename T>
    struct get_either_right
    {
        using type = error::GET_EITHER_RIGHT_UNSUPPORTED;
    };

    template <typename T>
    using get_either_left_t = typename get_either_left<T>::type;

    template <typename T>
    using get_either_right_t = typename get_either_right<T>::type;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_GET_EITHER_HPP