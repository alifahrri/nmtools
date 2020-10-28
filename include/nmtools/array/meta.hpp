#ifndef NMTOOLS_ARRAY_META_HPP
#define NMTOOLS_ARRAY_META_HPP

#include "nmtools/traits.hpp"
#include <type_traits>
#include <tuple>

namespace nmtools
{
    /**
     * @brief get fixed-array size at compile-time.
     * well-formed specialization should have `value` and `value_type`.
     * 
     * @tparam T type to check
     * @tparam typename optional for sfinae
     */
    template <typename T, typename=void>
    struct fixed_array_shape {};

    /**
     * @brief specialization of fixed_array_shape for std::array
     * 
     * @tparam T value type of std::array
     * @tparam N number of elements of std::array
     * @todo find out a way to generalize nested std::array
     */
    template <typename T, size_t N>
    struct fixed_array_shape<std::array<T,N>>
    {
        static inline constexpr auto value = std::make_tuple(N);
        using value_type = decltype(value);
    };

    /**
     * @brief specaialization of fixed_array_shape for nested 2D std::array
     * 
     * @tparam T value type of std::array
     * @tparam Rows number of elements for the first axis
     * @tparam Cols number of elements for the second axis
     * @todo find out a way to generalize nested std::array
     */
    template <typename T, size_t Rows, size_t Cols>
    struct fixed_array_shape<std::array<std::array<T,Cols>,Rows>>
    {
        static inline constexpr auto value = std::make_tuple(Rows,Cols);
        using value_type = decltype(value);
    };

    /**
     * @brief helper variable template to get fixed-array size at compile-time.
     * well-formed specialization should have `value` and `value_type`.
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr auto fixed_array_shape_v = fixed_array_shape<T>::value;

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
         * 
         * Enabled when fixed_matrix_size<T> is well-formed and has value_type member type
         * and the value_type is not void.
         * 
         * @tparam T type to check
         * @see nmtools::fixed_matrix_size
         * @note it is recommended to specialize fixed_matrix_size instead of specializing this trait
         */
        template <typename T>
        struct is_fixed_size_matrix<T,
            enable_if_t<has_value_type_v<fixed_matrix_size<T>> 
                && !std::is_same_v<typename fixed_matrix_size<T>::value_type,void>
        > > : std::true_type {};

        /**
         * @brief specialization of is_fixed_size_vector fo true case.
         * 
         * Enabled when fixed_vector_size is well-formed and has value_type member type
         * and the value_type is not void.
         * 
         * @tparam T type to check
         * @see nmtools::fixed_vector_size
         * @note it is recommended to specialize fixed_vector_size instead of specializing this trait
         */
        template <typename T>
        struct is_fixed_size_vector<T,
            enable_if_t<has_value_type_v<fixed_vector_size<T>>
                && !std::is_same_v<typename fixed_vector_size<T>::value_type,void>
        > > : std::true_type {};

        /** @} */ // end group traits
    } // namespace traits

    /**
     * @brief helper variable template for fixed_vector_size
     * 
     * @tparam V 
     */
    template <typename V>
    inline constexpr auto fixed_vector_size_v = fixed_vector_size<V>::value;
} // namespace nmtools

namespace nmtools::traits
{
    /**
     * @addtogroup traits
     * @{
     */

    /**
     * @brief return compile-time boolean indicating the referenced array has compile-time shape
     * 
     * @tparam array_type
     * @see nmtools::traits::is_fixed_size_vector
     * @see nmtools::traits::is_fixed_size_matrix
     * @see nmtools::traits::is_fixed_ndarray
     * @todo consider to move to traits
     */
    template <typename array_type>
    struct is_fixed_shape
    {
        using array_t = traits::remove_cvref_t<array_type>;
        static inline constexpr bool value = traits::is_fixed_size_vector_v<array_t> 
            || traits::is_fixed_size_matrix_v<array_t>
            || traits::is_fixed_ndarray_v<array_t>;
    }; // is_fixed_shape

    /**
     * @brief return compile-time boolean indicating the referenced array has compile-time shape
     * 
     * @tparam array_type
     * @see nmtools::traits::is_fixed_size_vector
     * @see nmtools::traits::is_fixed_size_matrix
     * @see nmtools::traits::is_fixed_ndarray
     * @todo consider to move to traits
     */
    template <typename array_type>
    static inline constexpr bool is_fixed_shape_v = is_fixed_shape<array_type>::value;

    /** @} */ // end group traits

} // nmtools::traits

#endif // NMTOOLS_ARRAY_META_HPP