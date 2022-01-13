#ifndef NMTOOLS_META_BITS_ARRAY_NESTED_ARRAY_SIZE_HPP
#define NMTOOLS_META_BITS_ARRAY_NESTED_ARRAY_SIZE_HPP

#include "nmtools/meta/bits/traits/is_num.hpp"

namespace nmtools::meta
{
    // TODO: remove, use len
    /**
     * @brief returns the number of elements of fixed shape at its 1st axis.
     *
     * @tparam T type to check
     * @tparam typename customization point
     */
    template <typename T, typename=void>
    struct nested_array_size
    {
        static constexpr auto value = 0;
    }; // nested_array_size

    /**
     * @brief helper variable template to get the number of elements of fixed shape at its 1st axis.
     * 
     * @tparam T type to check
     * @see nested_array_size
     */
    template <typename T>
    inline constexpr auto nested_array_size_v = nested_array_size<T>::value;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_ARRAY_NESTED_ARRAY_SIZE_HPP