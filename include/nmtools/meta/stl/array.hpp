#ifndef NMTOOLS_META_STL_ARRAY_HPP
#define NMTOOLS_META_STL_ARRAY_HPP

#include "nmtools/meta/array.hpp"

namespace nmtools::meta
{
    /**
     * @brief specialization of nested_array_size for type that has tuple_size and value_type.
     * 
     * @tparam T type tot check
     */
    template <typename T>
    struct nested_array_size<T
        , enable_if_t<has_tuple_size_v<T> && has_value_type_v<T>>
    > {
        static constexpr auto value = std::tuple_size_v<T>;
    }; // nested_array_size

    /**
     * @brief specialization of nested_array_dim
     *
     * Sepcialized when T square bracket expression with size_t is well-formed,
     * checked using has_square_bracket. Recursively instantiate nested_array_dim
     * with decreasing dimension.
     * 
     * @tparam T type to check
     * @see expr::square_bracket
     * @see has_square_bracket
     */
    template <typename T>
    struct nested_array_dim<T,enable_if_t<has_square_bracket_v<T,size_t>>>
    {
        using value_type = std::remove_reference_t<expr::square_bracket<T,size_t>>;
        static constexpr auto value = 1 + nested_array_dim<value_type>::value;
    }; // nested_array_dim

} // namespace nmtools::meta

#endif 