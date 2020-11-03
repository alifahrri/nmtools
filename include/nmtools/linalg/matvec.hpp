#ifndef NMTOOLS_LINALG_MATVEC_HPP
#define NMTOOLS_LINALG_MATVEC_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include <type_traits>
#include <cmath>
#include <cassert>

namespace nmtools::linalg {

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

        using meta::is_array1d_v;
        using meta::is_array2d_v;
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

    /* make symbols accessible for unqualified-lookup */
    using std::size;
    using std::tuple_size;
    
    /**
     * @brief make zeros array, given size known at compile-time
     * 
     * @tparam Array vector-like
     * @tparam n number of elements
     * @return constexpr auto 
     */
    template <typename Array, size_t N>
    constexpr auto zeros()
    {
        static_assert(
            meta::is_array1d_v<Array> && meta::has_value_type_v<Array>,
            "unsupported type Array for zeros<size_t>"
        );
        using value_t   = meta::remove_cvref_t<typename Array::value_type>;
        using new_size  = std::integral_constant<size_t,N>;
        using new_array = meta::replace_template_parameter<Array,value_t,new_size>;
        using return_t  = typename new_array::type;
        static_assert(!std::is_same_v<return_t,void>);
        auto zero = return_t{};
        return zero;
    }

    /**
     * @brief make zeros array, given size & type
     * 
     * @tparam Array matrix-like, resizeable
     * @param m number of rows
     * @param n number of columns
     * @return constexpr auto
     */
    template <typename Array>
    auto zeros(size_t m, size_t n)
    {
        static_assert(
            meta::is_array2d_v<Array> && meta::is_resizeable_v<Array>,
            "unsupported type Array for zeros(size_t,size_t)"
        );
        using value_t = meta::remove_cvref_t<typename Array::value_type>;
        auto z = Array{};
        /* TODO: check if this expr is well-formed first! */
        z.resize(m, value_t(m));
        return z;
    }

    /**
     * @brief make zeros array, given size known at compile-time
     * 
     * @tparam m number of rows
     * @tparam n number of columns
     * @tparam Array matrix-like, has_tuple_size, has_value_type
     * @return constexpr auto 
     */
    template <typename Array, size_t M, size_t N>
    constexpr auto zeros()
    {
        static_assert(
            meta::is_array2d_v<Array> && meta::has_tuple_size_v<Array>,
            "unsupported type Array for zeros<size_t,size_t>()"
        );
        using row_t = Array;
        using col_t = meta::remove_cvref_t<typename row_t::value_type>;
        using element_t = meta::remove_cvref_t<typename col_t::value_type>;
        using new_col_size = std::integral_constant<size_t,N>;
        using new_row_size = std::integral_constant<size_t,M>;
        using new_col_t = meta::replace_template_parameter<col_t,element_t,new_col_size>;
        using new_row_t = meta::replace_template_parameter<row_t,typename new_col_t::type,new_row_size>;
        using return_t = typename new_row_t::type;
        static_assert(!std::is_same_v<return_t,void>);
        auto z = return_t{};
        return z;
    }

    /**
     * @brief make zeros array, given size & type
     * 
     * @tparam Array vector-like
     * @param n number of elements
     * @return constexpr auto 
     */
    template <typename Array>
    auto zeros(size_t n)
    {
        static_assert(
            meta::is_array1d_v<Array> && meta::is_resizeable_v<Array>,
            "unsupported type Array for zeros(size_t)"
        );
        auto z = Array{};
        z.resize(n);
        return z;
    }

    /**
     * @brief create zero matrix/vector 
     * 
     * @tparam T matrix/vector/arithmetic
     * @param a example of existing matrix/vector
     * @return constexpr auto 
     */
    template <typename T>
    constexpr auto zeros_like(const T& a)
    {
        /** TODO: proper constraints **/
        static_assert(
            meta::is_array1d_v<T> ||
            meta::is_array2d_v<T> ||
            std::is_arithmetic_v<T>,
            "unsupported type for zeros_like"
        );
        using meta::remove_cvref_t;
        using meta::transform_bounded_array_t;
        using return_t = transform_bounded_array_t<remove_cvref_t<T>>;
        auto ret = return_t{};
        /* ret is aritmethic type (scalr), return as it is */
        if constexpr (std::is_arithmetic_v<T>)
            return static_cast<T>(0);
        /* ret is conteiner, for each elements call zeros_like */
        else {
            if constexpr (meta::is_resizeable_v<T>)
                ret.resize(size(a));
            for (size_t i=0; i<size(a); i++)
                ret[i] = zeros_like(a[i]);
            return ret;
        }
    }

    /**
     * @brief create matrix/vector filled with 1s
     * 
     * @tparam T matrix/vector/arithmetic
     * @param a example of existing matrix/vector
     * @return constexpr auto 
     */
    template <typename T>
    constexpr auto ones_like(const T& a)
    {
        /** TODO: proper constraints **/
        static_assert(
            meta::is_array1d_v<T> ||
            meta::is_array2d_v<T> ||
            std::is_arithmetic_v<T>,
            "unsupported type for zeros_like"
        );
        using meta::remove_cvref_t;
        using meta::transform_bounded_array_t;
        using return_t = transform_bounded_array_t<remove_cvref_t<T>>;
        auto ret = return_t{};
        /* ret is aritmethic type (scalr), return as it is */
        if constexpr (std::is_arithmetic_v<T>)
            return static_cast<T>(1);
        /* ret is conteiner, for each elements call zeros_like */
        else {
            if constexpr (meta::is_resizeable_v<T>)
                ret.resize(size(a));
            for (size_t i=0; i<size(a); i++)
                ret[i] = ones_like(a[i]);
            return ret;
        }
    }

    namespace detail {
        /**
         * @brief make array
         * 
         * @tparam Args 
         * @param args 
         * @return std::array<std::common_type_t<Args...>, sizeof...(Args)> 
         */
        template <typename... Args>
        constexpr auto make_array(Args&&... args)
        {
            using common_t = std::common_type_t<Args...>;
            using return_t = std::array<common_t, sizeof...(Args)>;
            return return_t{{std::forward<Args>(args)...}};
        }

        /**
         * @brief vector-scalar multiplication
         * 
         * @tparam V vector-like 
         * @tparam S scalar 
         * @param v left-hand-side vector
         * @param s right-hand-side scalar
         * @return constexpr auto vector-like
         */
        template <typename V, typename S>
        constexpr auto vsmul(const V& v, const S& s)
        {
            auto ret = v;
            for (auto& e : ret)
                e *= s;
            return ret;
        }

        /**
         * @brief matrix-scalar multiplication
         * 
         * @tparam M matrix-like
         * @tparam S scalar 
         * @param m left-hand-side matrix
         * @param s right-hand-side scalar
         * @return constexpr auto matrix-like
         */
        template <typename M, typename S>
        constexpr auto msmul(const M& m, const S& s)
        {
            auto ret = zeros_like(m);
            auto n = size(ret);
            for (size_t i=0; i<n; i++)
                ret[i] = vsmul(m[i],s);
            return ret;
        }

        /**
         * @brief dot product of v1 & v2
         * 
         * @tparam V1 vector-like
         * @tparam V2 vector-like
         * @param v1 left-hand-side vector
         * @param v2 right-hand-side vector
         * @return constexpr auto scalar, common type of element v1 & v2
         */
        template <typename V1, typename V2>
        constexpr auto dot(const V1& v1, const V2& v2)
        {
            static_assert(
                (
                    meta::is_array1d_v<V1>
                    && meta::is_array1d_v<V2>
                ) ||
                (
                    std::is_arithmetic_v<V1>
                    && std::is_arithmetic_v<V2>
                )
                , "unsupported type for dot"
            );
            using std::remove_cv_t;
            using std::remove_reference_t;
            using meta::get_value_type_or_same_t;

            using e1_t = remove_cv_t<remove_reference_t<get_value_type_or_same_t<V1>>>;
            using e2_t = remove_cv_t<remove_reference_t<get_value_type_or_same_t<V2>>>;
            using value_t = std::common_type_t<e1_t,e2_t>;

            if constexpr (std::is_arithmetic_v<V1>)
                return value_t{v1 * v2};
            else {
                value_t ret{0};
                auto n1 = size(v1);
                auto n2 = size(v2);
                /* TODO: make assertio optional (?) */
                assert(n1==n2);
                
                for (size_t i = 0; i < n1; i++)
                    ret += v1[i] * v2[i];
                return ret;
            }
        }

        /**
         * @brief matrix-vector multiplication
         * 
         * @tparam M matrix-like
         * @tparam V vector-like
         * @param m left-hand-side matrix
         * @param v right-hand-side vector
         * @return constexpr auto vector-like
         */
        template <typename M, typename V>
        constexpr auto mvmul(const M& m, const V& v)
        {
            static_assert(
                meta::is_array2d_v<M> &&
                meta::is_array1d_v<V> &&
                meta::has_value_type_v<M> && 
                meta::has_value_type_v<V>,
                "unsupported type for mvmul"
            );

            /* deduce resulting size of matrix */
            /* TODO: consider to provide traits to check if type has fixed size mat traits */
            constexpr auto is_fixed_size_M = meta::has_tuple_size_v<M>;
            constexpr auto is_fixed_size_V = meta::has_tuple_size_v<V>;

            /* get row type of matrix M, element type of M & v, and common type */
            using row_t = typename M::value_type;
            /* TODO: handle if M1 is not a nested container type! (theris no RowA::value_type) */
            using m_t = typename row_t::value_type;
            using v_t = typename V::value_type;
            using common_t = std::common_type_t<m_t,v_t>;

            /* dispatch compile-time version 
                both are fixed size, the resulting shape will be known at compile time */
            if constexpr (is_fixed_size_M && is_fixed_size_V) {
                constexpr auto n = std::tuple_size_v<M>;
                /* TODO: check if this expr well-formed first! */
                constexpr auto n1 = std::tuple_size_v<row_t>;
                constexpr auto n2 = std::tuple_size_v<V>;
                static_assert(n1==n2);

                /* prepare placeholder for the resulting matrix */
                auto ret = zeros<V,n>();

                for (size_t i=0; i<n; i++)
                    ret[i] = dot(m[i], v);
                return ret;
            }
            /* dispatch runtime version
                one of the matrix are dynamic, the resulting shape will be known at runtime time */
            else {
                auto n = size(m);
                auto n1 = size(m[0]);
                auto n2 = size(v);
                /* TODO: make assertion optional (?) */
                assert(n1==n2);

                /* make sure one of the matrix type is resizeable */
                static_assert(
                    meta::is_resizeable_v<M> ||
                    meta::is_resizeable_v<V>
                );
                /* select resizeable mat over fixed ones for return type */
                using return_t = meta::select_resizeable_mat_t<M,V>;
                auto ret = zeros<return_t>(n);

                for (size_t i=0; i<n; i++)
                    ret[i] = dot(m[i], v);
                return ret;
            }
        }

        /**
         * @brief matrix-matrix multiplication A*B
         * 
         * @tparam M1 matrix-like
         * @tparam M2 matrix-like
         * @param A 
         * @param B 
         * @return constexpr auto 
         */
        template <typename M1, typename M2>
        constexpr auto mmmul(const M1& A, const M2& B)
        {
            static_assert(
                meta::is_matrix_like_v<M1> &&
                meta::is_matrix_like_v<M2>,
                "unsupported type M1 & M2 of A & B for mmmul"
            );

            /* deduce resulting size of matrix */
            /* TODO: consider to provide traits to check if type has fixed size mat traits */
            constexpr auto is_fixed_size_mat_A = meta::has_tuple_size_v<M1>;
            constexpr auto is_fixed_size_mat_B = meta::has_tuple_size_v<M2>;

            /* deduce row type and element type */
            /* TODO: check if this expr is well-formed first! */
            using RowA = typename M1::value_type;
            using RowB = typename M2::value_type;
            /* TODO: handle if M1 is not a nested container type! (theris no RowA::value_type) */
            using a_t = typename RowA::value_type;
            using b_t = typename RowB::value_type;
            /* get common type of matrix A & B */
            using common_t = std::common_type_t<a_t,b_t>;

            /* dispatch compile-time version 
                both are fixed size matrix, the resulting shape will be known at compile time */
            if constexpr (is_fixed_size_mat_A && is_fixed_size_mat_B) {
                constexpr auto row_a = tuple_size<M1>::value;
                constexpr auto row_b = tuple_size<M2>::value;
                constexpr auto col_a = tuple_size<RowA>::value;
                constexpr auto col_b = tuple_size<RowB>::value;
                static_assert(col_a == row_b);
                static_assert(row_a == col_b);

                /* prepare placeholder for the resulting matrix */
                auto mat = zeros<M1,row_a,col_b>();

                /* naively multiply for each element */
                /* TODO: figure-out best way to perform this op */
                for (int i=0; i<row_a; i++) {
                    for (int j=0; j<col_b; j++) {
                        auto sum = static_cast<common_t>(0);
                        for (int k=0; k<col_a; k++)
                            sum += A[i][k] * B[k][j];
                        mat[i][j] = sum;
                    }
                }
                return mat;
            }
            /* dispatch runtime version
                one of the matrix are dynamic, the resulting shape will be known at runtime time */
            else {
                /* TODO: consider to provide 'shape' helper function */
                auto row_a = size(A);
                auto col_a = size(A[0]);
                auto row_b = size(B);
                auto col_b = size(B[0]);

                assert (col_a == row_b);
                assert (row_a == col_b);

                /* make sure one of the matrix type is resizeable */
                static_assert(
                    meta::is_resizeable_v<M1> ||
                    meta::is_resizeable_v<M2>
                );
                /* select resizeable mat over fixed ones for return type */
                using return_t = meta::select_resizeable_mat_t<M1,M2>;
                auto mat = zeros<return_t>(row_a,col_b);

                /* naively multiply for each element */
                /* TODO: figure-out best way to perform this op */
                for (int i=0; i<row_a; i++) {
                    for (int j=0; j<col_b; j++) {
                        auto sum = static_cast<common_t>(0);
                        for (int k=0; k<col_a; k++)
                            sum += A[i][k] * B[k][j];
                        mat[i][j] = sum;
                    }
                }

                return mat;
            }
        }

        /**
         * @brief vector vector addition a+b
         * 
         * @tparam V1 vector-like
         * @tparam V2 vector-like
         * @param v1 lhs
         * @param v2 rhs
         * @return constexpr auto 
         */
        template <typename V1, typename V2>
        constexpr auto vvadd(const V1& a, const V2& b)
        {
            static_assert(
                meta::is_array1d_v<V1>
                && meta::is_array1d_v<V2>,
                "unsupported type for vvadd"
            );

            /* deduce resulting size of matrix */
            /* TODO: consider to provide traits to check if type has fixed size mat traits */
            constexpr auto is_fixed_size_vec_A = meta::has_tuple_size_v<V1>;
            constexpr auto is_fixed_size_vec_B = meta::has_tuple_size_v<V2>;

            using std::remove_cv_t;
            using std::remove_reference_t;
            using meta::get_value_type_or_same_t;

            using e1_t = remove_cv_t<remove_reference_t<get_value_type_or_same_t<V1>>>;
            using e2_t = remove_cv_t<remove_reference_t<get_value_type_or_same_t<V2>>>;
            using return_t = std::common_type_t<e1_t,e2_t>;

            /* dispatch compile time ver. */
            if constexpr (is_fixed_size_vec_A && is_fixed_size_vec_B) {
                constexpr auto n1 = size(a);
                constexpr auto n2 = size(b);
                constexpr auto n  = n1;

                static_assert (n1==n2);

                auto ret = zeros<V1,n>();
                for (size_t i=0; i<n; i++)
                    ret[i] = a[i] + b[i];
                return ret;
            }
            /* dispatch runtime ver. */
            else {
                /* make sure one of the matrix type is resizeable */
                static_assert(
                    meta::is_resizeable_v<V1> ||
                    meta::is_resizeable_v<V2>
                );

                auto n1 = size(a);
                auto n2 = size(b);
                /* TODO: make assertio optional (?) */
                assert(n1==n2);
                auto n = n1;

                /* select resizeable mat over fixed ones for return type */
                using return_t = meta::select_resizeable_mat_t<V1,V2>;
                auto ret = zeros<return_t>(n);

                for (size_t i=0; i<n; i++)
                    ret[i] = a[i] + b[i];
                return ret;
            }
        }

        /**
         * @brief matrix matrix additon A+B
         * 
         * @tparam M1 matrix-like
         * @tparam M2 matrix-like
         * @param A lhs
         * @param B rhs
         * @return constexpr auto 
         */
        template <typename M1, typename M2>
        constexpr auto mmadd(const M1& A, const M2& B)
        {
            static_assert(
                meta::is_matrix_like_v<M1> &&
                meta::is_matrix_like_v<M2>,
                "unsupported type M1 & M2 of A & B for mmadd"
            );

            /* deduce resulting size of matrix */
            /* TODO: consider to provide traits to check if type has fixed size mat traits */
            constexpr auto is_fixed_size_mat_A = meta::has_tuple_size_v<M1>;
            constexpr auto is_fixed_size_mat_B = meta::has_tuple_size_v<M2>;

            /* deduce row type and element type */
            /* TODO: check if this expr is well-formed first! */
            using RowA = typename M1::value_type;
            using RowB = typename M2::value_type;
            /* TODO: handle if M1 is not a nested container type! (theris no RowA::value_type) */
            using a_t = typename RowA::value_type;
            using b_t = typename RowB::value_type;
            /* get common type of matrix A & B */
            using common_t = std::common_type_t<a_t,b_t>;

            /* dispatch compile-time version 
                both are fixed size matrix, the resulting shape will be known at compile time */
            if constexpr (is_fixed_size_mat_A && is_fixed_size_mat_B) {
                constexpr auto row_a = tuple_size<M1>::value;
                constexpr auto row_b = tuple_size<M2>::value;
                constexpr auto col_a = tuple_size<RowA>::value;
                constexpr auto col_b = tuple_size<RowB>::value;
                static_assert(col_a == row_b);
                static_assert(row_a == col_b);

                /* prepare placeholder for the resulting matrix */
                auto mat = zeros<M1,row_a,col_b>();

                /* naively multiply for each element */
                /* TODO: figure-out best way to perform this op */
                for (int i=0; i<row_a; i++)
                    for (int j=0; j<col_b; j++)
                        mat[i][j] = A[i][j] + B[i][j];
                return mat;
            }
            /* dispatch runtime version
                one of the matrix are dynamic, the resulting shape will be known at runtime time */
            else {
                /* TODO: consider to provide 'shape' helper function */
                auto row_a = size(A);
                auto col_a = size(A[0]);
                auto row_b = size(B);
                auto col_b = size(B[0]);

                assert (col_a == row_b);
                assert (row_a == col_b);

                /* make sure one of the matrix type is resizeable */
                static_assert(
                    meta::is_resizeable_v<M1> ||
                    meta::is_resizeable_v<M2>
                );
                /* select resizeable mat over fixed ones for return type */
                using return_t = meta::select_resizeable_mat_t<M1,M2>;
                auto mat = zeros<return_t>(row_a,col_b);

                /* naively multiply for each element */
                /* TODO: figure-out best way to perform this op */
                for (int i=0; i<row_a; i++)
                    for (int j=0; j<col_b; j++)
                        mat[i][j] = A[i][j] + B[i][j];
                return mat;
            }
        }

    } // namespace detail

    /* make symbols accessible for unqualified-lookup */
    using detail::mmmul;
    using detail::msmul;
    using detail::mvmul;
    using detail::vsmul;
    using detail::vvadd;
    using detail::mmadd;
    using detail::dot;
    using std::fabs;

    /**
     * @brief compute matrix transpose
     * 
     * @tparam Array matrix-like
     * @param a matrix to be transposed
     * @return constexpr auto 
     */
    template <typename Array>
    constexpr auto transpose(const Array& a)
    {
        using meta::get_container_value_type_t;
        using meta::remove_cvref_t;
        using meta::has_tuple_size_v;
        static_assert(
            meta::is_array2d_v<Array>,
            "transpose only support 2D array for now"
        );
        using row_element_t = remove_cvref_t<get_container_value_type_t<Array>>;
        using col_element_t = remove_cvref_t<get_container_value_type_t<row_element_t>>;
        static_assert(
            has_tuple_size_v<Array> == has_tuple_size_v<row_element_t>,
            "transpose doesn't support mixed dynamic-static container"
        );
        /* dispatch compile-time version */
        if constexpr (has_tuple_size_v<Array>) {
            constexpr auto rows = tuple_size<Array>::value;
            constexpr auto cols = tuple_size<row_element_t>::value;
            auto transposed = zeros<Array,cols,rows>();
            for (int i=0; i<cols; i++)
                for (int j=0; j<rows; j++)
                    transposed[i][j] = a[j][i];
            return transposed;
        }
        /* dispatch runtime version */
        else {
            auto rows = size(a);
            auto cols = size(a[0]);
            auto transposed = zeros<Array>(cols,rows);
            for (int i=0; i<cols; i++)
                for (int j=0; j<rows; j++)
                    transposed[i][j] = a[j][i];
            return transposed;
        }
    }

    /**
     * @brief clone matrix/vector 
     * 
     * @tparam Array 
     * @param a matrix/vector/arithmetic
     * @return constexpr auto 
     */
    template <typename Array>
    constexpr auto clone(const Array& a)
    {
        /** TODO: proper constraints **/
        static_assert(
            meta::is_array1d_v<Array> ||
            meta::is_array2d_v<Array> ||
            std::is_arithmetic_v<Array>,
            "unsupported type for zeros_like"
        );
        using meta::remove_cvref_t;
        using meta::transform_bounded_array_t;
        using return_t = transform_bounded_array_t<remove_cvref_t<Array>>;
        auto ret = return_t{};
        /* ret is aritmethic type (scalr), return as it is */
        if constexpr (std::is_arithmetic_v<Array>)
            return a;
        /* ret is conteiner, for each elements call zeros_like */
        else {
            if constexpr (meta::is_resizeable_v<Array>) {
                ret.resize(size(a));
            }
            for (size_t i=0; i<size(a); i++)
                ret[i] = clone(a[i]);
            return ret;
        }
    }

    /**
     * @brief make identity matrix
     * 
     * @tparam Array matrix-like
     * @param a square matrix
     * @return constexpr auto identity matrix
     */
    template <typename Array>
    constexpr auto identity(const Array& a)
    {
        using meta::remove_cvref_t;
        using meta::get_container_value_type_t;
        using meta::is_resizeable_v;
        using meta::is_array2d_v;

        static_assert(
            is_array2d_v<Array>,
            "only support 2D array"
        );

        /* remove cv-ref to make sure we get non const */
        using element_t = remove_cvref_t<get_container_value_type_t<Array>>;
        using value_t = remove_cvref_t<get_container_value_type_t<element_t>>;

        auto ret = zeros_like(a);
        auto n = size(a);
        auto m = size(a[0]);
        assert (m==n);

        if constexpr (is_resizeable_v<Array>)
            ret.resize(n);

        for (size_t i=0; i<n; i++) {
            if constexpr (is_resizeable_v<element_t>)
                ret[i].resize(m);
            ret[i][i] = static_cast<value_t>(1);
        }
        return ret;
    }

    /**
     * @brief max-element
     * 
     * @tparam Array vector-like
     * @param a vector
     * @return constexpr auto 
     */
    template <typename Array>
    constexpr auto max(const Array& a)
    {
        /* only support 1d array for now */
        static_assert(
            meta::is_array1d_v<Array>,
            "unsupported type of array"
        );
        using value_type = typename Array::value_type;
        value_type m = std::numeric_limits<value_type>::min();
        for (const auto e : a)
            if (e > m)
                m = e;
        return m;
    }

    /**
     * @brief elementwise absolute value
     * 
     * @tparam Array matrix-like, vector-like, or arithmetic
     * @param a 
     * @return constexpr auto 
     */
    template <typename Array>
    constexpr auto fabs(const Array& a)
    {
        using meta::is_array1d_v;
        using meta::is_array2d_v;
        using std::is_arithmetic_v;

        static_assert(
            is_array1d_v<Array> ||
            is_array2d_v<Array> ||
            is_arithmetic_v<Array>,
            "unsupported type for fabs"
        );

        /* dispatch if Array is 1d or 2d */
        if constexpr (is_array1d_v<Array> || is_array2d_v<Array>) {
            auto ret = zeros_like(a);
            for (size_t i=0; i<size(a); i++)
                ret[i] = fabs(a[i]);
            return ret;
        }
        /* dispatch if Array is arithmetic type */
        else {
            auto ret = fabs(a);
            return ret;
        }
    }

    /**
     * @brief perform lhs * rhs
     * 
     * @tparam A matrix-like or vector-like or A*B is multiplicative
     * @tparam B matrix-like or vector-like or arithmetic type or A*B is multiplicative
     * @param lhs 
     * @param rhs 
     * @return constexpr auto 
     */
    template <typename A, typename B>
    constexpr auto mul(const A& lhs, const B& rhs)
    {
        using meta::is_multiplicative_v;

        /* get operation tag */
        using op_t = tag::get_t<A,B>;

        static_assert(
            is_multiplicative_v<A,B>
            || (
                !std::is_same_v<op_t,void> 
                && !std::is_same_v<op_t,tag::vector_vector_t>
            )
            , "unsupported type(s) for mul(lhs,rhs)"
        );

        /* dispatch if A & B is multiplicative */
        if constexpr (is_multiplicative_v<A,B>)
            return lhs * rhs;
        /* dispatch matrix-matrix multiplication */
        else if constexpr (std::is_same_v<op_t,tag::matrix_matrix_t>)
            return mmmul(lhs, rhs);
        /* dispatch matrix-vector multiplication */
        else if constexpr (std::is_same_v<op_t,tag::matrix_vector_t>)
            return mvmul(lhs, rhs);
        /* dispatch matrix-scalar multiplication */
        else if constexpr (std::is_same_v<op_t,tag::matrix_scalar_t>)
            return msmul(lhs, rhs);
        /* dispatch vector-scalar multiplication */
        else if constexpr (std::is_same_v<op_t,tag::vector_scalar_t>)
            return vsmul(lhs, rhs);
        /* dispatch scalar-scalar multiplication, should be multiplicative though */
        else if constexpr (std::is_same_v<op_t,tag::scalar_scalar_t>)
            return lhs * rhs;
        else {
            // vector-vector
            // TODO: compile error here
        }
    }

    /**
     * @brief perform lhs + rhs
     * 
     * @tparam A vector-like or matrix-like or scalar
     * @tparam B vector-like or matrix-like or scalar
     * @param lhs 
     * @param rhs 
     * @return constexpr auto 
     */
    template <typename A, typename B>
    constexpr auto add(const A& lhs, const B& rhs)
    {
        using meta::is_additive_v;

        /* get operation tag */
        using op_t = tag::get_t<A,B>;

        static_assert(
            is_additive_v<A,B>
            || (
                !std::is_same_v<op_t,void> 
                && !std::is_same_v<op_t,tag::vector_scalar_t>
                && !std::is_same_v<op_t,tag::matrix_scalar_t>
                && !std::is_same_v<op_t,tag::matrix_vector_t>
            )
            , "unsupported type(s) for add(lhs,rhs)"
        );

        /* dispatch if A & B is additive */
        if constexpr (is_additive_v<A,B>)
            return lhs + rhs;
        /* dispatch vector-vector addition */
        else if constexpr (std::is_same_v<op_t,tag::vector_vector_t>)
            return vvadd(lhs, rhs);
        /* dispatch matrix-matrix addition */
        else if constexpr (std::is_same_v<op_t,tag::matrix_matrix_t>)
            return mmadd(lhs, rhs);
        else {
            // TODO: compile error here
        }
    }

} // namespace nmtools::linalg

#endif // NMTOOLS_LINALG_MATVEC_HPP
