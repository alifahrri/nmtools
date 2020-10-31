#ifndef NMTOOLS_BLAS_TAG_HPP
#define NMTOOLS_BLAS_TAG_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include <cmath>
#include <cassert>
#include <type_traits>

namespace nmtools::blas
{
    /**
     * @ingroup blas
     * @{
     */

    namespace tag {

        /**
         * @brief tag for vector vector ops
         * 
         */
        struct vector_vector_t {};
        
        /**
         * @brief tag for matrix matrix ops
         * 
         */
        struct matrix_matrix_t {};

        /**
         * @brief tag for matrix vector ops
         * 
         */
        struct matrix_vector_t {};

        /**
         * @brief tag for vector scalar ops
         * 
         */
        struct vector_scalar_t {};

        /**
         * @brief tag for matrix scalar ops
         * 
         */
        struct matrix_scalar_t {};

        /**
         * @brief tag for scalar scalar ops
         * 
         */
        struct scalar_scalar_t {};

        using traits::is_array1d_v;
        using traits::is_array2d_v;
        using std::enable_if_t;
        using std::void_t;

        /**
         * @brief helper alias template to add specialization to overload set if T is vector-like
         * 
         * @tparam T type to check
         */
        template <typename T>
        using enable_if_vector_t = enable_if_t<is_array1d_v<T>>;

        /**
         * @brief helper alias template to add specialization to overload set if T is matrix-like
         * 
         * @tparam T type to check
         */
        template <typename T>
        using enable_if_matrix_t = enable_if_t<is_array2d_v<T>>;

        /**
         * @brief helper alias template to add specialization to overload set if T is arithmetic
         * 
         * @tparam T type to check
         */
        template <typename T>
        using enable_if_scalar_t = enable_if_t<std::is_arithmetic_v<T>>;

        /**
         * @brief helper alias template to remove specialization from overload set if T is vector-like
         * 
         * @tparam T type to check
         */
        template <typename T>
        using disable_if_vector_t = enable_if_t<!is_array1d_v<T>>;

        /**
         * @brief helper alias template to remove specialization from overload set if T is matrix-like
         * 
         * @tparam T type to check
         */
        template <typename T>
        using disable_if_matrix_t = enable_if_t<!is_array2d_v<T>>;

        /**
         * @brief helper alias template to remove specialization from overload set if T is arithmetic
         * 
         * @tparam T 
         */
        template <typename T>
        using disable_if_scalar_t = enable_if_t<!std::is_arithmetic_v<T>>;

        /**
         * @brief resolve matvec ops tag
         * 
         * @tparam T lhs
         * @tparam U rhs
         * @tparam typename=void 
         */
        template <typename T, typename U, typename=void>
        struct get {
            /**
             * @brief default implementation to get the matvec ops tag.
             *
             * Implemented as static member function instead of clunky enable_if_t sfinae
             * for more readability and to make use of constexpr-if.
             * 
             * @return constexpr auto 
             */
            static constexpr auto _get() {
                if constexpr (traits::is_array2d_v<T> && traits::is_array2d_v<U>)
                    return matrix_matrix_t{};
                else if constexpr (traits::is_array2d_v<T> && traits::is_array1d_v<U>)
                    return matrix_vector_t{};
                else if constexpr (traits::is_array2d_v<T> && std::is_arithmetic_v<U>)
                    return matrix_scalar_t{};
                else if constexpr (traits::is_array1d_v<T> && traits::is_array1d_v<U>)
                    return vector_vector_t{};
                else if constexpr (traits::is_array1d_v<T> && std::is_arithmetic_v<U>)
                    return vector_scalar_t{};
                else if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>)
                    return scalar_scalar_t{};
                else return meta::detail::fail_t{};
            } // _get()
            using type = traits::remove_cvref_t<meta::detail::fail_to_void_t<decltype(_get())>>;
        }; // get

        /**
         * @brief helper alias template to get op tag
         * 
         * @tparam T lhs
         * @tparam U rhs
         */
        template <typename T, typename U>
        using get_t = typename get<T,U>::type;
    } // namespace tag

    /** @} */ // end group blas
}

#endif // NMTOOLS_BLAS_TAG_HPP