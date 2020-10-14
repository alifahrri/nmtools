#ifndef NMTOOLS_ARRAY_META_HPP
#define NMTOOLS_ARRAY_META_HPP

#include "nmtools/traits.hpp"
#include <type_traits>

namespace nmtools
{
    // TODO: consider to move to meta
    /**
     * @brief get fixed-matrix's size at compile time.
     * well-formed specialization should have `value` and `value_type`.
     * 
     * @tparam T 
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct fixed_matrix_size {};

    // TODO: consider to move to meta
    /**
     * @brief helper variable template to get fixed-matrix's size
     * 
     * @tparam M fixed-matrix
     */
    template <typename M>
    inline constexpr auto fixed_matrix_size_v = fixed_matrix_size<M>::value;

    // TODO: consider to move to meta
    /**
     * @brief get fixed-vector's (math vector, not container) size at compile time
     * 
     * @tparam V 
     * @tparam typename=void 
     */
    template <typename V, typename=void>
    struct fixed_vector_size {};

    // TODO: consider to move to meta
    /**
     * @brief specializaton of fixed_matrix_size for nested array
     * 
     * @tparam T 
     * @tparam n 
     * @tparam m 
     */
    template <typename T, size_t Rows, size_t Cols>
    struct fixed_matrix_size<std::array<std::array<T,Cols>,Rows>> 
    {
        static inline constexpr auto value = std::make_pair(Rows,Cols);
        using value_type = decltype(value); // std::pair
    };

    // TODO: consider to move to meta
    /**
     * @brief specializaton of fixed_vector_size for std::array
     * 
     * @tparam T 
     * @tparam N 
     */
    template <typename T, size_t N>
    struct fixed_vector_size<std::array<T,N>> : std::tuple_size<std::array<T,N>> {};

    /**
     * @brief helper alias template for std::integral_constant<size_t,...>
     * 
     * @tparam N 
     * @see nmtools::slice
     * @see nmtools::make_slice_index
     */
    template <size_t N>
    using index_constant = std::integral_constant<size_t,N>;

    namespace traits
    {
        /* extend traits for fixed_size_matrix & fixed_size_vector */

        /**
         * @addtogroup traits
         * @{
         */

        /**
         * @brief specialization of is_fixed_size_matrix for true case.
         * Enabled when fixed_matrix_size<T> is well-formed and has value_type member type.
         * 
         * @tparam T type to check
         */
        template <typename T>
        struct is_fixed_size_matrix<T,
            enable_if_t<has_value_type_v<fixed_matrix_size<T>>>
        > : std::true_type {};

        /**
         * @brief specialization of is_fixed_size_vector fo true case.
         * Enabled when fixed_vector_size is well-formed and has value_type member type.
         * 
         * @tparam T type to check
         */
        template <typename T>
        struct is_fixed_size_vector<T,
            enable_if_t<has_value_type_v<fixed_vector_size<T>>>
        > : std::true_type {};

        /** @} */ // end group traits
    }

    /**
     * @brief helper variable template for fixed_vector_size
     * 
     * @tparam V 
     */
    template <typename V>
    inline constexpr auto fixed_vector_size_v = fixed_vector_size<V>::value;
} // namespace nmtools

#endif // NMTOOLS_ARRAY_META_HPP