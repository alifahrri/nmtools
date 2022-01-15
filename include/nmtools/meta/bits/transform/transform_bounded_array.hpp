#ifndef NMTOOLS_META_BITS_TRANSFORM_TRANSFORM_BOUNDED_ARRAY_HPP
#define NMTOOLS_META_BITS_TRANSFORM_TRANSFORM_BOUNDED_ARRAY_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/transform/remove_cvref.hpp"

namespace nmtools::meta
{
    /**
     * @brief transform (bounded) raw array to array
     * should have member type `type` with type of array
     * 
     * @tparam T 
     */
    template <typename T, typename=void>
    struct transform_bounded_array 
    {
        using type = T;
    };

    /**
     * @brief helper alias template to transform (bounded) raw array to array
     * 
     * @tparam T (bounded) array
     */
    template <typename T>
    using transform_bounded_array_t = typename transform_bounded_array<T>::type;

    /**
     * @brief overloaded version of transform_bounded_array for T[N]
     * 
     * @tparam T element type
     * @tparam N number of elements
     */
    template <typename T, size_t N>
    struct transform_bounded_array<T[N]>
    {
        using value_type = typename transform_bounded_array<remove_cvref_t<T>>::type;
        using type = typename make_array_type<remove_cvref_t<value_type>,N>::type;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_TRANSFORM_BOUNDED_ARRAY_HPP