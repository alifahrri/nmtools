#ifndef NMTOOLS_META_BITS_TRANSFORM_TRANSFORM_BOUNDED_ARRAY_HPP
#define NMTOOLS_META_BITS_TRANSFORM_TRANSFORM_BOUNDED_ARRAY_HPP

namespace nmtools::meta
{
    /**
     * @brief transform (bounded) raw array to std::array
     * should have member type `type` with type of std::array
     * if given T is bounded (1D or 2D) raw array, 
     * `type` has type of T otherwise
     * 
     * @tparam T 
     */
    template <typename T, typename=void>
    struct transform_bounded_array 
    {
        using type = T;
    };

    /**
     * @brief helper alias template to transform (bounded) raw array to std::array
     * 
     * @tparam T (bounded) array
     */
    template <typename T>
    using transform_bounded_array_t = typename transform_bounded_array<T>::type;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_TRANSFORM_BOUNDED_ARRAY_HPP