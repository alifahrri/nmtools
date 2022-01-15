#ifndef NMTOOLS_META_BITS_ARRAY_NESTED_ARRAY_DIM_HPP
#define NMTOOLS_META_BITS_ARRAY_NESTED_ARRAY_DIM_HPP

#include "nmtools/meta/bits/traits/is_num.hpp"
#include "nmtools/meta/bits/traits/has_square_bracket.hpp"
#include "nmtools/meta/bits/transform/remove_cvref.hpp"

namespace nmtools::meta
{

    namespace error
    {
        template<typename...>
        struct DIM_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    // TODO: rename to dim
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
        static constexpr auto value = [](){
            return 0ul;
            // TODO: update
            // if constexpr (is_num_v<T>) {
            //     return 0ul;
            // } else {
            //     return error::DIM_UNSUPPORTED<T>{};
            // }
        }();
    }; // nested_array_dim

    // NOTE: use sfinae to allow recursion
    // TODO: cleanup
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
        using value_type = remove_reference_t<expr::square_bracket<T,size_t>>;
        static constexpr auto value = 1 + nested_array_dim<value_type>::value;
    }; // nested_array_dim

    // TODO: rename to dim_v
    /**
     * @brief helper variable template for nested_array_dim.
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr auto nested_array_dim_v = nested_array_dim<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_NESTED_ARRAY_DIM_HPP