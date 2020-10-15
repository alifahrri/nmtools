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
            // invalid
            using type = void;
        };

        /**
         * @brief get vector-vector ops tag
         * 
         * @tparam T lhs
         * @tparam U rhs
         */
        template <typename T, typename U>
        struct get<T,U,void_t<
            enable_if_vector_t  <T>, enable_if_vector_t  <U>,
            disable_if_matrix_t <T>, disable_if_matrix_t <U>,
            disable_if_scalar_t <T>, disable_if_scalar_t <U>
        >> {
            using type = vector_vector_t;
        };

        /**
         * @brief get matrix-matrix ops tag
         * 
         * @tparam T lhs
         * @tparam U rhs
         */
        template <typename T, typename U>
        struct get<T,U,void_t<
            /* current impl have matrix-like is subset of vector-like */
            // disable_if_vector_t <T>, disable_if_vector_t <U>,
            enable_if_matrix_t  <T>, enable_if_matrix_t  <U>,
            disable_if_scalar_t <T>, disable_if_scalar_t <U>
        >> {
            using type = matrix_matrix_t;
        };

        /**
         * @brief get scalar-scalar ops tag
         * 
         * @tparam T lhs
         * @tparam U rhs
         */
        template <typename T, typename U>
        struct get<T,U,void_t<
            disable_if_vector_t <T>, disable_if_vector_t <U>,
            disable_if_matrix_t <T>, disable_if_matrix_t <U>,
            enable_if_scalar_t  <T>, enable_if_scalar_t  <U>
        >> {
            using type = scalar_scalar_t;
        };

        /**
         * @brief get matrix-vector ops tag
         * 
         * @tparam T lhs
         * @tparam U rhs
         */
        template <typename T, typename U>
        struct get<T,U,void_t<
            /* current impl have matrix-like is subset of vector-like */
            /* disable_if_vector_t <T>, */ enable_if_vector_t  <U>,
            enable_if_matrix_t  <T>, disable_if_matrix_t <U>,
            disable_if_scalar_t <T>, disable_if_scalar_t <U>
        >> {
            using type = matrix_vector_t;
        };

        /**
         * @brief get matrix-scalar ops tag
         * 
         * @tparam T lhs
         * @tparam U rhs
         */
        template <typename T, typename U>
        struct get<T,U,void_t<
            /* current impl have matrix-like is subset of vector-like */
            /* disable_if_vector_t <T>, */ disable_if_vector_t <U>,
            enable_if_matrix_t  <T>, disable_if_matrix_t <U>,
            disable_if_scalar_t <T>, enable_if_scalar_t  <U>
        >> {
            using type = matrix_scalar_t;
        };

        /**
         * @brief get vector-scalar ops tag
         * 
         * @tparam T lhs
         * @tparam U rhs
         */
        template <typename T, typename U>
        struct get<T,U,void_t<
            enable_if_vector_t  <T>, disable_if_vector_t <U>,
            disable_if_matrix_t <T>, disable_if_matrix_t <U>,
            disable_if_scalar_t <T>, enable_if_scalar_t  <U>
        >> {
            using type = vector_scalar_t;
        }; 

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