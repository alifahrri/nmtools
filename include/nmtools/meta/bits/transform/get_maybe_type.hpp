#ifndef NMTOOLS_META_BITS_TRANSFORM_GET_MAYBE_TYPE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_GET_MAYBE_TYPE_HPP

namespace nmtools::meta
{
    /**
     * @brief Get the value type of maybe type
     * 
     * @tparam T type to check 
     * @tparam typename 
     * @todo move to transform
     */
    template <typename T, typename=void>
    struct get_maybe_type
    {
        using type = void;
    };

    template <typename T>
    using get_maybe_type_t = typename get_maybe_type<T>::type;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_GET_MAYBE_TYPE_HPP