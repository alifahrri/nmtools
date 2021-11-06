#ifndef NMTOOLS_META_BITS_ARRAY_NESTED_ARRAY_DIM_HPP
#define NMTOOLS_META_BITS_ARRAY_NESTED_ARRAY_DIM_HPP

namespace nmtools::meta
{
    /**
     * @brief get the number of dimension of (possibly) nested array.
     *
     * By default, check using expr::square_bracket.
     * 
     * @tparam T type to check
     * @tparam typename
     */
    template <typename T, typename=void>
    struct nested_array_dim
    {
        static constexpr auto value = 0;
    }; // nested_array_dim

    /**
     * @brief helper variable template for nested_array_dim.
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr auto nested_array_dim_v = nested_array_dim<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_NESTED_ARRAY_DIM_HPP