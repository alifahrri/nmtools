#ifndef NMTOOLS_ARRAY_META_HPP
#define NMTOOLS_ARRAY_META_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
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
     * @todo move to meta
     * @todo provide specialization for is_fixed_size_vector/matrix/ndarray
     */
    template <typename T, typename=void>
    struct fixed_array_shape {};

    /**
     * @brief specialization of fixed_array_shape for std::array
     * 
     * @tparam T value type of std::array
     * @tparam N number of elements of std::array
     * @todo find out a way to generalize nested std::array
     * @todo remove, prefer specialization of is_fixed_size_vector/matrix/ndarray
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
     * @todo remove, prefer specialization of is_fixed_size_vector/matrix/ndarray
     */
    template <typename T, size_t Rows, size_t Cols>
    struct fixed_array_shape<std::array<std::array<T,Cols>,Rows>>
    {
        static inline constexpr auto value = std::make_tuple(Rows,Cols);
        using value_type = decltype(value);
    };

    template <typename F, size_t...Is>
    constexpr auto template_for(F&& f, std::index_sequence<Is...>)
    {
        (f(std::integral_constant<size_t,Is>{}),...);
    } // template_for

    template <size_t N, typename F>
    constexpr auto template_for(F&& f)
    {
        using index_t = std::make_index_sequence<N>;
        template_for(f,index_t{});
    } // template_for

    template <typename T>
    struct fixed_array_shape<T,std::enable_if_t<std::is_array_v<T>>>
    {
        static constexpr auto _get() {
            constexpr auto rank = std::rank_v<T>;
            auto shape = std::array<size_t,rank>{};
            template_for<rank>([&](auto index) {
                constexpr auto i = decltype(index)::value;
                constexpr auto n = std::extent_v<T,i>;
                shape[i] = n;
            });
            return shape;
        }
        static inline constexpr auto value = _get();
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

    template <typename T, size_t Rows, size_t Cols>
    struct fixed_matrix_size<T[Rows][Cols]>
    {
        static constexpr inline auto value = std::make_pair(Rows,Cols);
        using value_type = decltype(value);
    }; // fixed_matrix_size

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

    namespace meta
    {
        /* extend traits for fixed_size_matrix & fixed_size_vector */

        /**
         * @addtogroup traits
         * @{
         */

        /**
         * @brief specializtion of is_fixed_size_ndarray when fixed_array_shape
         * yields valid value.
         * 
         * @tparam T type to check
         * @todo consider to move to primary template instead of specialize + sfinae
         */
        template <typename T>
        struct is_fixed_size_ndarray<T
            , enable_if_t<has_value_type_v<fixed_array_shape<T>>
                && !std::is_same_v<typename fixed_array_shape<T>::value_type,void>
            >
        > : std::true_type {};

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
    } // namespace meta

    /**
     * @brief helper variable template for fixed_vector_size
     * 
     * @tparam V 
     */
    template <typename V>
    inline constexpr auto fixed_vector_size_v = fixed_vector_size<V>::value;
} // namespace nmtools

#endif // NMTOOLS_ARRAY_META_HPP