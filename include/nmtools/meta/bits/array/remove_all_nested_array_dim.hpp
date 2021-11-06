#ifndef NMTOOLS_META_BITS_ARRAY_REMOVE_ALL_NESTED_ARRAY_DIM_HPP
#define NMTOOLS_META_BITS_ARRAY_REMOVE_ALL_NESTED_ARRAY_DIM_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/expr.hpp"
#include "nmtools/meta/bits/traits/has_square_bracket.hpp"

namespace nmtools::meta
{
    /**
     * @brief Get element type of nested array.
     * 
     * If T is some type that has expression t[i][j]...,
     * provide member typedef with type of that element type with maximum indexing,
     * otherwise provide typedef with T.
     * 
     * 
     * @tparam T type to check
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct remove_all_nested_array_dim
    {
        using type = T;
    }; // remove_all_nested_array_dim

    /**
     * @brief Specialization of remove_all_nested_array_dim.
     *
     * Enabled when given type T can be 'sliced' with size_t.
     * 
     * @tparam T type to check
     * @see meta::has_square_bracket
     */
    template <typename T>
    struct remove_all_nested_array_dim<T,enable_if_t<has_square_bracket_v<T,size_t>>>
    {
        // recursively call itself until it reach default case
        using value_type = remove_cvref_t<expr::square_bracket<T,size_t>>;
        using type = typename remove_all_nested_array_dim<value_type>::type;
    }; // remove_all_nested_array_dim

    /**
     * @brief helper alias template for remove_all_nested_array_dim.
     * 
     * @tparam T type to check
     */
    template <typename T>
    using remove_all_nested_array_dim_t = typename remove_all_nested_array_dim<T>::type;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_REMOVE_ALL_NESTED_ARRAY_DIM_HPP