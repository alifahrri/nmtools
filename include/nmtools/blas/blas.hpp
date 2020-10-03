#ifndef NMTOOLS_BLAS_BLAS_HPP
#define NMTOOLS_BLAS_BLAS_HPP

/* common tag for preconditions, e.g. size assertion */
#include "nmtools/utility/tag.hpp"
/* common array (as in matrix/vector) utility */
#include "nmtools/array/utility.hpp"

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include <type_traits>
#include <cmath>
#include <cassert>

namespace nmtools::blas {

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
        } // constexpr auto make_array(Args&&... args)

    } // namespace detail

    /* make symbols accessible for unqualified-lookup */
    using std::get;
    using std::size;
    using std::fabs;
    using std::sqrt;
    using std::tuple_size;
    using std::tuple_size_v;

    /** @defgroup blas
    * Collections of blas functions.
    * @{
    */
    
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
            traits::is_array1d_v<Array> && traits::has_value_type_v<Array>,
            "unsupported type Array for zeros<size_t>"
        );
        /* deduce type using helper metafunction 
            to allows partial specialization for
                arbitraty custom type Array*/
        using return_t = meta::make_zeros_vector_t<Array,N>;
        /* make sure valid type */
        static_assert(!std::is_same_v<return_t,void>);
        /* assuming the deduced type can be instantiated this way */
        auto zero = return_t{};
        return zero;
    } // constexpr auto zeros()

    /**
     * @brief make zeros array, given size & type
     * 
     * @tparam Array matrix-like, resizeable
     * @param m number of rows
     * @param n number of columns
     * @return constexpr auto
     */
    template <typename Array, typename size_type>
    auto zeros(size_type m, size_type n)
    {
        static_assert(
            /* TODO: consider to use is_matrix_like instead of is_array2d */
            traits::is_array2d_v<Array> &&
            (
                traits::is_resizeable_v<Array>
                || traits::is_resizeable2d_v<Array>
            ),
            "unsupported type Array for zeros(size_t,size_t)"
        );
        /* TODO: make sure Array can be constructed this way */
        auto z = Array{};
        /* TODO: consider to provide free function resize */
        /* can directly resize with m, n as arguments */
        if constexpr (traits::is_resizeable2d_v<Array>)
            z.resize(m,n);
        /* doesnt have resize 2d, let's resize each elements */
        else {
            z.resize(m);
            if constexpr (traits::is_resizeable_v<traits::remove_cvref_t<decltype(at(z,0))>>)
                for (size_t i=0; i<size(z); i++)
                    at(z,i).resize(n);
            else {
                /* assuming at(z,0) has fixed size n */
                /* TODO: make assertion optional (?) */
                constexpr auto N = fixed_vector_size_v<traits::remove_cvref_t<decltype(at(z,0))>>;
                assert (N==n);
            }
        }
        return z;
    } // auto zeros(size_t m, size_t n)

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
            traits::is_array2d_v<Array>
            && traits::is_fixed_size_matrix_v<Array>,
            "unsupported type Array for zeros<size_t,size_t>()"
        );        
        using return_t = meta::make_zeros_matrix_t<Array,M,N>;
        static_assert(!std::is_same_v<return_t,void>);
        auto z = return_t{};
        return z;
    } // constexpr auto zeros()

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
            traits::is_array1d_v<Array>
            && traits::is_resizeable_v<Array>,
            "unsupported type Array for zeros(size_t)"
        );
        auto z = Array{};
        z.resize(n);
        return z;
    } // auto zeros(size_t n)

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
            traits::is_array1d_v<T> ||
            traits::is_array2d_v<T> ||
            std::is_arithmetic_v<T>,
            "unsupported type for zeros_like"
        );
        using traits::remove_cvref_t;
        using meta::transform_bounded_array_t;
        using return_t = transform_bounded_array_t<remove_cvref_t<T>>;
        /* TODO: check if return_t can be instantiated this way */
        auto ret = return_t{};
        /* ret is aritmethic type (scalr), return casted zero */
        if constexpr (std::is_arithmetic_v<T>)
            return static_cast<T>(0);
        /* ret is conteiner, for each elements call zeros_like */
        else {
            /* when T can be resized with 2 arguments, meaning that it is matrix, 
                then we should resize it that way */
            if constexpr (traits::is_array2d_v<T> && traits::is_resizeable2d_v<T>)
            {
                auto [rows, cols] = matrix_size(a);
                ret.resize(rows, cols);
            }
            /* otherwise, also resize each elements of ret */
            else if constexpr (traits::is_resizeable_v<T>) {
                /* TODO: should we use vector_size instead of size? */
                ret.resize(size(a));
                for (size_t i=0; i<size(a); i++)
                    at(ret,i) = zeros_like(at(a,i));
            }
            return ret;
        }
    } // constexpr auto zeros_like(const T& a)

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
            traits::is_array1d_v<T> ||
            traits::is_array2d_v<T> ||
            std::is_arithmetic_v<T>,
            "unsupported type for zeros_like"
        );
        using traits::remove_cvref_t;
        using meta::transform_bounded_array_t;
        using return_t = transform_bounded_array_t<remove_cvref_t<T>>;
        auto ret = return_t{};
        /* ret is aritmethic type (scalr), return as it is */
        if constexpr (std::is_arithmetic_v<T>)
            return static_cast<T>(1);
        /* ret is conteiner, for each elements call zeros_like */
        else {
            auto ret = zeros_like(a);
            using return_t = traits::remove_cvref_t<decltype(ret)>;
            /* array2d implementation */
            if constexpr (traits::is_array2d_v<return_t>)
            {
                /* common implementation loop for both fixed and dynamic */
                auto ones_like2d_impl = [](auto &ret, auto rows, auto cols){
                    for (size_t i=0; i<rows; i++)
                        for (size_t j=0; j<cols; j++)
                            at(ret,i,j) = 1;
                };
                constexpr auto is_fixed_size = traits::is_fixed_size_matrix_v<return_t>;
                if constexpr (is_fixed_size) {
                    /* TODO: find-out if reading matrix_size as constexpr is beneficial */
                    constexpr auto shape = matrix_size(ret);
                    constexpr auto rows = std::get<0>(shape);
                    constexpr auto cols = std::get<1>(shape);
                    ones_like2d_impl(ret,rows,cols);
                }
                else {
                    auto [rows, cols] = matrix_size(ret);
                    ones_like2d_impl(ret,rows,cols);
                }
            }
            /* array1d implementation */
            else {
                /* common implementation loop for 1d fixed and dynamic */
                auto ones_like1d_impl = [](auto &ret, auto n){
                    for (size_t i=0; i<n; i++)
                        at(ret,i) = 1;
                };
                constexpr auto is_fixed_size = traits::is_fixed_size_vector_v<return_t>;
                if constexpr (is_fixed_size) {
                    constexpr auto n = vector_size(ret);
                    ones_like1d_impl(ret,n);
                }
                else {
                    auto n = vector_size(ret);
                    ones_like1d_impl(ret,n);
                }
            }
            return ret;
        }
    } // constexpr auto ones_like(const T& a)

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
        static_assert(
            traits::is_array2d_v<Array>,
            "transpose only support 2D array for now"
        );

        using meta::get_container_value_type_t;
        using traits::has_tuple_size_v;

        using std::get;
        using traits::remove_cvref_t;
        using meta::transform_bounded_array_t;
        using return_t = transform_bounded_array_t<remove_cvref_t<Array>>;

        constexpr auto is_fixed_size = traits::is_fixed_size_matrix_v<return_t>;

        /* common loop implementation for both fixed and dynamic */
        auto transpose_impl = [](auto &transposed, const auto& a, auto rows, auto cols) {
            for (int i=0; i<cols; i++)
                for (int j=0; j<rows; j++)
                    at(transposed,i,j) = at(a,j,i);
        };

        if constexpr (is_fixed_size) {
            /* TODO: find-out if reading shape as constexpr here is beneficial */
            constexpr auto shape = matrix_size(a);
            constexpr auto rows = get<0>(shape);
            constexpr auto cols = get<1>(shape);
            /* make zeros with transposed size */
            auto transposed = zeros<return_t,cols,rows>();
            transpose_impl(transposed,a,rows,cols);
            return transposed;
        }
        else {
            auto [rows,cols] = matrix_size(a);
            /* make zeros with transposed size */
            auto transposed = zeros<return_t>(cols,rows);
            transpose_impl(transposed,a,rows,cols);
            return transposed;
        }
    } // constexpr auto transpose(const Array& a)

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
            traits::is_array1d_v<Array>
            || traits::is_array2d_v<Array>
            || std::is_arithmetic_v<Array>,
            "unsupported type for clone"
        );
        /* ret is aritmethic type (scalr), return as it is */
        if constexpr (std::is_arithmetic_v<Array>)
            return a;
        /* ret is conteiner, for each elements call zeros_like */
        else {
            auto ret = zeros_like(a);
            using return_t = traits::remove_cvref_t<decltype(ret)>;
            /* array2d implementation */
            if constexpr (traits::is_array2d_v<return_t>)
            {
                /* common implementation loop for both fixed and dynamic */
                auto clone2d_impl = [](auto &ret, const auto& a, auto rows, auto cols){
                    for (size_t i=0; i<rows; i++)
                        for (size_t j=0; j<cols; j++)
                            at(ret,i,j) = at(a,i,j);
                };
                constexpr auto is_fixed_size = traits::is_fixed_size_matrix_v<return_t>;
                if constexpr (is_fixed_size) {
                    /* TODO: find-out if reading matrix_size as constexpr is beneficial */
                    constexpr auto shape = matrix_size(ret);
                    constexpr auto rows = std::get<0>(shape);
                    constexpr auto cols = std::get<1>(shape);
                    clone2d_impl(ret,a,rows,cols);
                }
                else {
                    auto [rows, cols] = matrix_size(ret);
                    clone2d_impl(ret,a,rows,cols);
                }
            }
            /* array1d implementation */
            else {
                /* common implementation loop for 1d fixed and dynamic */
                auto clone1d_impl = [](auto &ret, const auto& a, auto n){
                    for (size_t i=0; i<n; i++)
                        at(ret,i) = at(a,i);
                };
                constexpr auto is_fixed_size = traits::is_fixed_size_vector_v<return_t>;
                if constexpr (is_fixed_size) {
                    constexpr auto n = vector_size(ret);
                    clone1d_impl(ret,a,n);
                }
                else {
                    auto n = vector_size(ret);
                    clone1d_impl(ret,a,n);
                }
            }
            return ret;
        }
    } // constexpr auto clone(const Array& a)

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
        using traits::is_array2d_v;

        static_assert(
            is_array2d_v<Array>,
            "only support 2D array"
        );

        /* remove cv-ref to make sure we get non const */
        using element_t = meta::get_matrix_value_type_t<Array>;

        auto ret = zeros_like(a);
        auto [n,m] = matrix_size(a);
        assert (m==n);

        for (size_t i=0; i<m; i++)
            at(ret,i,i) = static_cast<element_t>(1);
        return ret;
    } // constexpr auto identity(const Array& a)

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
            traits::is_array1d_v<Array>,
            "unsupported type of array"
        );
        using value_type = meta::get_vector_value_type_t<Array>;
        value_type m = std::numeric_limits<value_type>::min();
        for (const auto e : a)
            if (e > m)
                m = e;
        return m;
    } // constexpr auto max(const Array& a)

    namespace detail {
        /**
         * @brief implementation of sum for 1D array
         * 
         * @param sum input/output sum
         * @param a array to be summed
         * @param n number of elements in array a
         * @return constexpr auto 
         */
        constexpr auto sum_impl(auto& sum, const auto& a, auto n)
        {
            using idx_t = traits::remove_cvref_t<decltype(n)>;
            for (idx_t i=0; i<n; i++)
                sum += at(a,i);
        } // sum_impl
        /**
         * @brief implementation of sum for 2D array
         * 
         * @param sum input/output sum
         * @param a array to be summed
         * @param rows number of row in array a
         * @param cols number of column in array a
         * @return constexpr auto 
         */
        constexpr auto sum_impl(auto& sum, const auto& a, auto rows, auto cols)
        {
            using rows_t = traits::remove_cvref_t<decltype(rows)>;
            using cols_t = traits::remove_cvref_t<decltype(cols)>;
            using index_t = std::common_type_t<rows_t,cols_t>;
            for (index_t i=0; i<rows; i++)
                for (index_t j=0; j<cols; j++)
                    sum += at(a,i,j);
        } // sum_impl
    } // namespace detail

    /**
     * @brief sum-element
     * 
     * @tparam Array vector-like
     * @param a vector
     * @return constexpr auto 
     */
    template <typename Array>
    constexpr auto sum(const Array& a)
    {
        static_assert(
            traits::is_array1d_v<Array>
            || traits::is_array2d_v<Array>,
            "unsupported type of array, "
            "only support 1D and 2D array for now"
        );
        using value_type = meta::get_element_type_t<Array>;
        static_assert(
            std::is_arithmetic_v<value_type>,
            "unsupported element type from Array for operator sum, "
            "may be specialization of meta::get_element_type required (?)"
        );
        auto result = value_type{0};
        /* dispatch if a is 2D array */
        if constexpr (traits::is_array2d_v<Array>) {
            /* TODO: consider to read matrix_size as constexpr whenever possible */
            auto [rows, cols] = matrix_size(a);
            detail::sum_impl(result,a,rows,cols);
        }
        /* otherwise, dispatch if a is 1D array */
        else if constexpr (traits::is_array1d_v<Array>) {
            auto n = vector_size(a);
            detail::sum_impl(result,a,n);
        }
        return result;
    } // constexpr auto sum(const Array& a)

    namespace detail {
        /**
         * @brief implementation of sumsq for 1D array
         * 
         * @param sum input/output sum
         * @param a array to be summed
         * @param n number of elements in array a
         * @return constexpr auto 
         */
        constexpr auto sumsq_impl(auto& sum, const auto& a, auto n)
        {
            using idx_t = traits::remove_cvref_t<decltype(n)>;
            for (idx_t i=0; i<n; i++)
                sum += at(a,i)*at(a,i);
        } // sumsq_impl
        /**
         * @brief implementation of sumsq for 2D array
         * 
         * @param sum input/output sum
         * @param a array to be summed
         * @param rows number of row in array a
         * @param cols number of column in array a
         * @return constexpr auto 
         */
        constexpr auto sumsq_impl(auto& sum, const auto& a, auto rows, auto cols)
        {
            using rows_t = traits::remove_cvref_t<decltype(rows)>;
            using cols_t = traits::remove_cvref_t<decltype(cols)>;
            using index_t = std::common_type_t<rows_t,cols_t>;
            for (index_t i=0; i<rows; i++)
                for (index_t j=0; j<cols; j++)
                    sum += at(a,i,j)*at(a,i,j);
        } // sumsq_impl
    } // namespace detail

    template <typename Array>
    constexpr auto sumsq(const Array& a)
    {
        static_assert(
            traits::is_array1d_v<Array>
            || traits::is_array2d_v<Array>,
            "unsupported type of array, "
            "only support 1D and 2D array for now"
        );
        using detail::sumsq_impl;
        using value_type = meta::get_element_type_t<Array>;
        static_assert(
            std::is_arithmetic_v<value_type>,
            "unsupported element type from Array for operator sumsq, "
            "may be specialization of meta::get_element_type required (?)"
        );
        auto result = value_type{0};
        /* dispatch if a is 2D array */
        if constexpr (traits::is_array2d_v<Array>) {
            /* TODO: consider to read matrix_size as constexpr whenever possible */
            auto [rows, cols] = matrix_size(a);
            sumsq_impl(result,a,rows,cols);
        }
        /* otherwise, dispatch if a is 1D array */
        else if constexpr (traits::is_array1d_v<Array>) {
            auto n = vector_size(a);
            sumsq_impl(result,a,n);
        }
        return result;
    } // constexpr auto sum(const Array& a)

    namespace detail {
        /**
         * @brief implementation of row_sum
         * 
         * @param sum input/output sum
         * @param a array to be summed
         * @param rows number of row in array a
         * @param cols number of column in array a
         * @return constexpr auto 
         */
        constexpr auto row_sum_impl(auto& sum, const auto& a, auto rows, auto cols)
        {
            using rows_t = traits::remove_cvref_t<decltype(rows)>;
            using cols_t = traits::remove_cvref_t<decltype(cols)>;
            using index_t = std::common_type_t<rows_t,cols_t>;
            for (index_t i=0; i<rows; i++)
                for (index_t j=0; j<cols; j++)
                    at(sum, j) += at(a,i,j);
        } // constexpr auto row_sum_impl
    } // namespace detail

    /**
     * @brief perform row sum operation, similar to `sum(A,1)` in octave.
     * 
     * @tparam Array 
     * @param a 
     * @return constexpr auto 
     * @see nmtools::meta::get_column_type
     */
    template <typename Array>
    constexpr auto row_sum(const Array& a)
    {
        static_assert(
            traits::is_array2d_v<Array>,
            "unsupported type of array, "
            "only support 2D array for now"
        );
        using detail::row_sum_impl;
        using sum_t = meta::get_column_type_t<Array>;
        static_assert(
            !std::is_same_v<sum_t,void>,
            "unsupported column type for sum, may be specialization "
            "of nmtools::meta::get_column_type needed (?)"
        );

        constexpr auto is_fixed_size = traits::is_fixed_size_vector_v<sum_t>;
        constexpr auto is_resizeable = traits::is_resizeable_v<sum_t>;
        static_assert(is_fixed_size || is_resizeable);

        if constexpr (is_fixed_size) {
            auto sum = sum_t{};
            constexpr auto shape = matrix_size(a);
            constexpr auto rows = get<0>(shape);
            constexpr auto cols = get<1>(shape);
            row_sum_impl(sum,a,rows,cols);
            return sum;
        }
        else if constexpr (is_resizeable) {
            auto sum = sum_t{};
            auto [rows, cols] = matrix_size(a);
            sum.resize(cols);
            row_sum_impl(sum,a,rows,cols);
            return sum;
        }
    } // constexpr auto row_sum

    namespace detail {
        /**
         * @brief implementation of col_sum
         * 
         * @param sum input/output sum
         * @param a array to be summed
         * @param rows number of row in array a
         * @param cols number of column in array a
         * @return constexpr auto 
         */
        constexpr auto col_sum_impl(auto& sum, const auto& a, auto rows, auto cols)
        {
            using rows_t = traits::remove_cvref_t<decltype(rows)>;
            using cols_t = traits::remove_cvref_t<decltype(cols)>;
            using index_t = std::common_type_t<rows_t,cols_t>;
            for (index_t j=0; j<cols; j++)
                for (index_t i=0; i<rows; i++)
                    at(sum,i) += at(a,i,j);
        } // constexpr auto col_sum_impl
    } // namespace detail

    /**
     * @brief perform column sum operation
     * 
     * @tparam Array 
     * @param a 
     * @return constexpr auto 
     * @see nmtools::meta::get_row_type
     */
    template <typename Array>
    constexpr auto col_sum(const Array& a)
    {
        static_assert(
            traits::is_array2d_v<Array>,
            "unsupported type of array, "
            "only support 2D array for now"
        );
        using detail::col_sum_impl;
        using sum_t = meta::get_row_type_t<Array>;
        static_assert(
            !std::is_same_v<sum_t,void>,
            "unsupported column type for sum, may be specialization "
            "of nmtools::meta::get_row_type needed (?)"
        );

        constexpr auto is_fixed_size = traits::is_fixed_size_vector_v<sum_t>;
        constexpr auto is_resizeable = traits::is_resizeable_v<sum_t>;
        static_assert(is_fixed_size || is_resizeable);

        if constexpr (is_fixed_size) {
            auto sum = sum_t{};
            constexpr auto shape = matrix_size(a);
            constexpr auto rows = get<0>(shape);
            constexpr auto cols = get<1>(shape);
            col_sum_impl(sum,a,rows,cols);
            return sum;
        }
        else if constexpr (is_resizeable) {
            auto sum = sum_t{};
            auto [rows, cols] = matrix_size(a);
            sum.resize(rows);
            col_sum_impl(sum,a,rows,cols);
            return sum;
        }
    } // constexpr auto col_sum

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
        using traits::is_array1d_v;
        using traits::is_array2d_v;
        using std::is_arithmetic_v;

        static_assert(
            is_array1d_v<Array> ||
            is_array2d_v<Array> ||
            is_arithmetic_v<Array>,
            "unsupported type for fabs"
        );

        /* dispatch if Array is 1d or 2d */
        if constexpr (is_array2d_v<Array>) {
            auto ret = zeros_like(a);
            auto [rows,cols] = matrix_size(a);
            for (size_t i=0; i<rows; i++)
                for (size_t j=0; j<cols; j++)
                    at(ret,i,j) = fabs(at(a,i,j));
            return ret;
        }
        else if constexpr (is_array1d_v<Array>) {
            auto ret = zeros_like(a);
            auto n = vector_size(a);
            for (size_t i=0; i<n; i++)
                at(ret,i) = fabs(at(a,i));
            return ret;
        }
        /* dispatch if Array is arithmetic type */
        else {
            auto ret = fabs(a);
            return ret;
        }
    } // constexpr auto fabs(const Array& a)

    /**
     * @brief dot product of v1 & v2
     * 
     * @tparam V1 vector-like
     * @tparam V2 vector-like
     * @param v1 left-hand-side vector
     * @param v2 right-hand-side vector
     * @return constexpr auto scalar, common type of element v1 & v2
     * @cite gene2013matrix_dot_saxpy
     */
    template <typename V1, typename V2>
    constexpr auto dot(const V1& v1, const V2& v2)
    {
        static_assert(
            (
                traits::is_array1d_v<V1>
                && traits::is_array1d_v<V2>
            ) ||
            /* TODO: consider to drop arithmetic mul for this fn */
            (
                std::is_arithmetic_v<V1>
                && std::is_arithmetic_v<V2>
            )
            , "unsupported type for dot"
        );
        using std::remove_cv_t;
        using std::remove_reference_t;
        using meta::get_value_type_or_same_t;

        using e1_t = meta::get_vector_value_type_t<V1>;
        using e2_t = meta::get_vector_value_type_t<V2>;
        using value_t = std::common_type_t<e1_t,e2_t>;

        /* TODO: consider to drop arithmetic mul for this fn */
        if constexpr (std::is_arithmetic_v<V1>)
            return value_t{v1 * v2};
        else {
            value_t ret{0};
            auto n1 = vector_size(v1);
            auto n2 = vector_size(v2);
            /* TODO: make assertio optional (?) */
            assert(n1==n2);
            
            for (size_t i = 0; i < n1; i++)
                ret += at(v1,i) * at(v2,i);
            return ret;
        }
    } // constexpr auto dot(const V1& v1, const V2& v2)

    namespace detail {
        /**
         * @brief 
         * 
         * @param matrix 
         * @param v1 
         * @param v2 
         * @param m 
         * @param n 
         * @return constexpr auto 
         */
        constexpr auto outer_impl(auto& matrix, const auto& v1, const auto& v2, auto m, auto n)
        {
            for (size_t i=0; i<m; i++)
                for (size_t j=0; j<n; j++)
                    at(matrix,i,j) = at(v1,i) * at(v2,j);
        }
    } // namespace detail

    /**
     * @brief perform outer product computation
     * 
     * @tparam V1 vector-like
     * @tparam V2 vector-like
     * @param v1 left vector
     * @param v2 right vector
     * @return constexpr auto matrix-like wher the type is deduced from meta::make_outer_matrix
     * @cite gene2013matrix_outer
     */
    template <typename V1, typename V2>
    constexpr auto outer(const V1& v1, const V2& v2)
    {
        static_assert(
            traits::is_array1d_v<V1>
            && traits::is_array1d_v<V2>
            /* TODO: helpful error message here */
        );

        using detail::outer_impl;
        using v1_t = meta::transform_bounded_array_t<V1>;
        using v2_t = meta::transform_bounded_array_t<V2>;

        /* first, let's deduce the resulting type */
        using matrix_t = meta::make_outer_matrix_t<v1_t,v2_t>;

        static_assert(
            traits::is_array2d_v<matrix_t>
            /* TODO: helpful error message here */
        );

        constexpr auto is_fixed_size_matrix = traits::is_fixed_size_matrix_v<matrix_t>;

        if constexpr (is_fixed_size_matrix) {
            /* prepare placeholder for the resulting matrix */
            auto product = matrix_t{};

            constexpr auto shape = matrix_size(product);
            constexpr auto m = get<0>(shape);
            constexpr auto n = get<1>(shape);

            /* product update */
            outer_impl(product,v1,v2,m,n);

            return product;
        }
        else {
            auto m = vector_size(v1);
            auto n = vector_size(v2);

            auto product = zeros<matrix_t>(m,n);

            /* product update */
            outer_impl(product,v1,v2,m,n);

            return product;
        }
    } // constexpr auto outer(const V1& v1, const V2& v2)

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
        static_assert(
            traits::is_array1d_v<V>
            && std::is_arithmetic_v<S>
            /* TODO: helpful error message here */
        );
        auto ret = clone(v);
        for (size_t i=0; i<size(ret); i++)
            at(ret,i) = at(ret,i) * s;
        return ret;
    } // constexpr auto vsmul(const V& v, const S& s)

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
        static_assert(
            traits::is_array2d_v<M>
            && std::is_arithmetic_v<S>
            /* TODO: helpful error message here */
        );
        auto ret = zeros_like(m);
        auto [rows, cols] = matrix_size(m);
        for (size_t i=0; i<rows; i++) {
            /* NOTE: cant use vsmul for now since
                at requires to be returning reference
                while some matrix type returning value with
                reference wrapper */
            /* TODO: use vsmul instead */
            // at(ret,i) = vsmul(at(m,i),s);
            for (size_t j=0; j<cols; j++)
                at(ret,i,j) = at(m,i,j) * s;
        }
        return ret;
    } // constexpr auto msmul(const M& m, const S& s)

    /**
     * @brief matrix-vector multiplication
     * 
     * @tparam M matrix-like
     * @tparam V vector-like
     * @param m left-hand-side matrix
     * @param v right-hand-side vector
     * @return constexpr auto vector-like
     * @cite gene2013matrix_mvmul_gaxpy
     */
    template <typename M, typename V>
    constexpr auto mvmul(const M& m, const V& v)
    {
        static_assert(
            traits::is_array2d_v<M>
            && traits::is_array1d_v<V>,
            "unsupported type for mvmul"
        );

        /* get row type of matrix M, element type of M & v, and common type */
        using m_t = meta::transform_bounded_array_t<M>;
        using v_t = meta::transform_bounded_array_t<V>;
        using me_t = meta::get_matrix_value_type_t<M>;
        using ve_t = meta::get_vector_value_type_t<V>;
        using common_t = std::common_type_t<me_t,ve_t>;
        using return_t = meta::transform_bounded_array_t<V>;

        /* deduce resulting size of matrix */
        constexpr auto is_fixed_size_M = traits::is_fixed_size_matrix_v<m_t>;
        constexpr auto is_fixed_size_V = traits::is_fixed_size_vector_v<v_t>;

        auto mvmul_impl = [](auto& ret, const auto& m, const auto& v, auto mrows, auto mcols){
            for (size_t i=0; i<mrows; i++)
            {
                /* NOTE: can't use dot for now 
                    since at only support returning reference for accessing row
                    while some matrix type returning value with reference_wrapper
                */
                /* TODO: use dot product */
                // at(ret,i) = dot(at(m,i),v);

                auto sum = static_cast<common_t>(0);
                for (size_t j=0; j<mcols; j++)
                    sum += at(m,i,j) * at(v,j);
                
                at(ret,i) = sum;
            }
        };

        /* dispatch compile-time version when both are fixed size,
            the resulting shape will also be known at compile time */
        if constexpr (is_fixed_size_M && is_fixed_size_V) {
            constexpr auto shape = fixed_matrix_size_v<m_t>;
            constexpr auto mrows = get<0>(shape);
            constexpr auto mcols = get<1>(shape);
            constexpr auto vrows = fixed_vector_size_v<v_t>;
            static_assert(mcols==vrows);

            /* prepare placeholder for the resulting matrix */
            auto ret = zeros<return_t,mrows>();
            mvmul_impl(ret,m,v,mrows,mcols);
            return ret;
        }
        /* dispatch runtime version when one of the matrix are dynamic,
            the resulting shape will only be known at runtime time */
        else {
            auto [mrows, mcols] = matrix_size(m);
            auto vrows = vector_size(v);

            assert (mcols==vrows);

            /* make sure one of the matrix type is resizeable */
            static_assert(
                traits::is_resizeable_v<V>
                /* TODO: helpful error message here */
            );
            auto ret = zeros<return_t>(mrows);
            mvmul_impl(ret,m,v,mrows,mcols);
            return ret;
        }
    } // constexpr auto mvmul(const M& m, const V& v)

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
            traits::is_matrix_like_v<M1> &&
            traits::is_matrix_like_v<M2>,
            "unsupported type M1 & M2 of A & B for mmmul"
        );

        /* deduce row type and element type */
        using m1_t = meta::transform_bounded_array_t<M1>;
        using m2_t = meta::transform_bounded_array_t<M2>;
        using a_t = meta::get_matrix_value_type_t<m1_t>;
        using b_t = meta::get_matrix_value_type_t<m2_t>;
        using common_t = std::common_type_t<a_t,b_t>;

        constexpr auto is_fixed_size_mat_A = traits::is_fixed_size_matrix_v<m1_t>;
        constexpr auto is_fixed_size_mat_B = traits::is_fixed_size_matrix_v<m2_t>;

        auto mmmul_impl = [](auto& mat, const auto& A, const auto &B, auto row_a, auto col_a, auto col_b) {
            for (int i=0; i<row_a; i++) {
                for (int j=0; j<col_b; j++) {
                    auto sum = static_cast<common_t>(0);
                    for (int k=0; k<col_a; k++)
                        sum += at(A,i,k) * at(B,k,j);
                    at(mat,i,j) = sum;
                }
            }
        };

        /* dispatch compile-time version 
            both are fixed size matrix, the resulting shape will be known at compile time */
        if constexpr (is_fixed_size_mat_A && is_fixed_size_mat_B) {
            constexpr auto ashape = fixed_matrix_size_v<m1_t>;
            constexpr auto row_a = get<0>(ashape);
            constexpr auto col_a = get<1>(ashape);

            constexpr auto bshape = fixed_matrix_size_v<m2_t>;
            constexpr auto row_b = get<0>(bshape);
            constexpr auto col_b = get<1>(bshape);

            static_assert (col_a==row_b && row_a==col_b);

            /* prepare placeholder for the resulting matrix */
            auto mat = zeros<m1_t,row_a,col_b>();
            mmmul_impl(mat,A,B,row_a,col_a,col_b);
            return mat;
        }
        /* dispatch runtime version
            one of the matrix are dynamic, the resulting shape will be known at runtime time */
        else {
            auto [row_a, col_a] = matrix_size(A);
            auto [row_b, col_b] = matrix_size(B);

            assert (col_a == row_b);
            assert (row_a == col_b);

            /* make sure one of the matrix type is resizeable */
            static_assert(
                traits::is_resizeable_v<m1_t> ||
                traits::is_resizeable_v<m2_t>
            );
            /* select resizeable mat over fixed ones for return type */
            using return_t = meta::select_resizeable_matrix_t<m1_t,m2_t>;
            auto mat = zeros<return_t>(row_a,col_b);
            mmmul_impl(mat,A,B,row_a,col_a,col_b);
            return mat;
        }
    } // constexpr auto mmmul(const M1& A, const M2& B)

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
            traits::is_array1d_v<V1>
            && traits::is_array1d_v<V2>,
            "unsupported type for vvadd"
        );

        using traits::remove_cvref_t;
        using meta::get_value_type_or_same_t;
        using meta::transform_bounded_array_t;

        using v1_t = transform_bounded_array_t<V1>;
        using v2_t = transform_bounded_array_t<V2>;

        /* deduce resulting size of matrix */
        constexpr auto is_fixed_size_vec_A = traits::is_fixed_size_vector_v<v1_t>;
        constexpr auto is_fixed_size_vec_B = traits::is_fixed_size_vector_v<v2_t>;

        using e1_t = remove_cvref_t<get_value_type_or_same_t<v1_t>>;
        using e2_t = remove_cvref_t<get_value_type_or_same_t<v2_t>>;
        using return_t = std::common_type_t<e1_t,e2_t>;

        auto vvadd_impl = [](auto& ret, const auto& a, const auto& b, auto n) {
            for (size_t i=0; i<n; i++)
                at(ret,i) = at(a,i) + at(b,i);
        };

        /* dispatch compile time ver. */
        if constexpr (is_fixed_size_vec_A && is_fixed_size_vec_B) {
            constexpr auto n1 = fixed_vector_size_v<v1_t>;
            constexpr auto n2 = fixed_vector_size_v<v2_t>;
            constexpr auto n  = n1;

            static_assert (n1==n2);

            auto ret = zeros<v1_t,n>();
            // for (size_t i=0; i<n; i++)
            //     at(ret,i) = at(a,i) + at(b,i);
            vvadd_impl(ret,a,b,n);
            return ret;
        }
        /* dispatch runtime ver. */
        else {
            /* make sure one of the matrix type is resizeable */
            static_assert(
                traits::is_resizeable_v<v1_t> ||
                traits::is_resizeable_v<v2_t>
            );

            auto n1 = size(a);
            auto n2 = size(b);
            /* TODO: make assertio optional (?) */
            assert(n1==n2);
            auto n = n1;

            /* select resizeable mat over fixed ones for return type */
            using return_t = meta::select_resizeable_mat_t<v1_t,v2_t>;
            auto ret = zeros<return_t>(n);
            // for (size_t i=0; i<n; i++)
            //     at(ret,i) = at(a,i) + at(b,i);
            vvadd_impl(ret,a,b,n);
            return ret;
        }
    } // constexpr auto vvadd(const V1& a, const V2& b)

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
            traits::is_matrix_like_v<M1> &&
            traits::is_matrix_like_v<M2>,
            "unsupported type M1 & M2 of A & B for mmadd"
        );

        using meta::transform_bounded_array_t;
        using m1_t = transform_bounded_array_t<M1>;
        using m2_t = transform_bounded_array_t<M2>;
        using meta::get_matrix_value_type_t;

        /* check if these matrices are fixed-size */
        constexpr auto is_fixed_size_mat_A = traits::is_fixed_size_matrix_v<m1_t>;
        constexpr auto is_fixed_size_mat_B = traits::is_fixed_size_matrix_v<m2_t>;

        /* TODO: provide convinient meta-function to get element type of a matrix */
        /* element type of matrix A */
        using a_t = get_matrix_value_type_t<m1_t>;
        /* element type of matrix B */
        using b_t = get_matrix_value_type_t<m2_t>;
        /* get common type of matrix A & B */
        using common_t = std::common_type_t<a_t,b_t>;

        /* common implemenatation for loop for fixed and dynamic */
        auto mmadd_impl = [](auto &mat, const auto& A, const auto &B, auto row_a, auto row_b){
            for (int i=0; i<row_a; i++)
                for (int j=0; j<row_b; j++)
                    at(mat,i,j) = at(A,i,j) + at(B,i,j);
        };

        /* dispatch compile-time version 
            both are fixed size matrix, the resulting shape will be known at compile time */
        if constexpr (is_fixed_size_mat_A && is_fixed_size_mat_B) {
            /* deduce row type and element type */
            constexpr auto shape_a = matrix_size(A);
            constexpr auto shape_b = matrix_size(B);
            constexpr auto row_a = get<0>(shape_a);
            constexpr auto row_b = get<0>(shape_b);
            constexpr auto col_a = get<1>(shape_a);
            constexpr auto col_b = get<1>(shape_b);

            static_assert(row_a == row_b);
            static_assert(col_a == col_b);

            /* prepare placeholder for the resulting matrix */
            auto mat = zeros<m1_t,row_a,col_b>();
            mmadd_impl(mat,A,B,row_a,col_b);
            return mat;
        }
        /* dispatch runtime version
            one of the matrix are dynamic, the resulting shape will be known at runtime time */
        else {
            auto [row_a, col_a] = matrix_size(A);
            auto [row_b, col_b] = matrix_size(B);

            /* addition requires matrix to be in the same shape */
            assert (col_a == col_b);
            assert (row_a == row_b);

            /* make sure one of the matrix type is resizeable */
            static_assert(
                traits::is_resizeable_v<M1> ||
                traits::is_resizeable_v<M2>
            );
            /* select resizeable mat over fixed ones for return type */
            using return_t = meta::select_resizeable_mat_t<m1_t,m2_t>;
            auto mat = zeros<return_t>(row_a,col_a);
            mmadd_impl(mat,A,B,row_a,col_b);
            return mat;
        }
    } // constexpr auto mmadd(const M1& A, const M2& B)

    /**
     * @brief perform lhs * rhs.
     * Dispatch one of the following (ordered by priority):
     * (1) lhs*rhs;
     * (2) mmmul(lhs,rhs);
     * (3) mvmul(lhs,rhs);
     * (4) vsmul(lhs,rhs);
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
        using traits::is_multiplicative_v;

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
    } // constexpr auto mul(const A& lhs, const B& rhs)

    /**
     * @brief perform lhs + rhs.
     * Dispatch one of the following expression (ordered by priority):
     * (1) lhs + rhs;
     * (2) vvadd(lhs,rhs);
     * (3) mmadd(lhs,rhs);
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
        using traits::is_additive_v;

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
    } // constexpr auto add(const A& lhs, const B& rhs)

    /* make sure use common tag namespace */
    using ::nmtools::tag::is_tag_enabled_v;
    using ::nmtools::tag::size_assert_t;
    using ::nmtools::tag::is_assert_v;

    /**
     * @brief perform level-2 blas saxpy (ax + y)
     * 
     * @tparam Scalar arithmetic
     * @tparam X vector-like
     * @tparam Y vector-like
     * @param a scalar
     * @param x 
     * @param y 
     * @return constexpr auto 
     * @cite gene2013matrix_dot_saxpy
     */
    template <typename tag_t=size_assert_t, typename Scalar, typename X, typename Y>
    constexpr auto saxpy(const Scalar& a, const X& x, const Y& y, tag_t=tag_t{})
    {
        static_assert(
            std::is_arithmetic_v<Scalar>
            && traits::is_array1d_v<X>
            && traits::is_array1d_v<Y>
            /* TODO: helpful error message */
        );

        /* check if we should perform size assertion */
        /* TODO: consider to provide helper function for this check */
        if constexpr (is_assert_v<tag_t>) {
            /* check if both x and y is fixed size */
            constexpr auto is_fixed_size_vec_x = traits::is_fixed_size_vector_v<X>;
            constexpr auto is_fixed_size_vec_y = traits::is_fixed_size_vector_v<Y>;

            /* when both vector is fixed size, perform size assertion at compile time */
            if constexpr (is_fixed_size_vec_x && is_fixed_size_vec_y) {
                constexpr auto nx = fixed_vector_size_v<X>;
                constexpr auto ny = fixed_vector_size_v<Y>;
                static_assert(
                    nx==ny
                    /* TODO: helpful error message */
                );
            }
            /* size assertion at runtime */
            else {
                auto nx = vector_size(x);
                auto ny = vector_size(y);
                assert (nx==ny);
            }
        } // if constexpr (is_assert_v<tag_t>)

        /* placeholder for results */
        auto res = zeros_like(y);
        
        /* call add and mul for each elements */
        /* at this point mul(x[i], a) should dispatch scalar-scalar mul, 
            no allocation e.g. zeros_like called*/
        for (size_t i=0; i<size(y); i++)
            at(res,i) = add(at(y,i), mul(at(x,i), a));
        
        return res;
    } // constexpr auto saxpy(const Scalar& a, const X& x, const Y& y)

    /**
     * @brief perform level-3 blas generalized saxpy
     * 
     * @tparam tag_t=size_assert_t 
     * @tparam Matrix 
     * @tparam X 
     * @tparam Y 
     * @param A 
     * @param x 
     * @param y 
     * @return constexpr auto 
     * @cite gene2013matrix_mvmul_gaxpy
     */
    template <typename tag_t=size_assert_t, typename Matrix, typename X, typename Y>
    constexpr auto gaxpy(const Matrix& A, const X& x, const Y& y)
    {
        static_assert(
            traits::is_array2d_v<Matrix>
            && traits::is_array1d_v<X>
            && traits::is_array1d_v<Y>
            /* TODO: helpful error message */
        );

        /* check if we should perform size assertion */
        /* TODO: consider to provide helper function for this check */
        if constexpr (is_assert_v<tag_t>) {
            /* check if all array-like is fixed-size one */
            constexpr auto is_fixed_A = traits::is_fixed_size_matrix_v<Matrix>;
            constexpr auto is_fixed_x = traits::is_fixed_size_vector_v<X>;
            constexpr auto is_fixed_y = traits::is_fixed_size_vector_v<Y>;

            /* perform size assertion at compile-time if all array-like has fixed size */
            if constexpr (is_fixed_A && is_fixed_x && is_fixed_y) {
                /* get pair first, then unpack row & col */
                constexpr auto nA = fixed_matrix_size_v<Matrix>;
                /* assuming col-major */
                constexpr auto row_A = get<0>(nA);
                constexpr auto col_A = get<1>(nA);
                /* vector size */
                constexpr auto nx = fixed_vector_size_v<X>;
                constexpr auto ny = fixed_vector_size_v<Y>;
                static_assert(
                    (nx == col_A)
                    && (ny == row_A)
                    /* TODO: helpful error message */
                );
            }
            /* perform check at runtime otherwise */
            else {
                auto [row_A, col_A] = matrix_size(A);
                auto nx = vector_size(x);
                auto ny = vector_size(y);
                assert (
                    (nx == col_A)
                    && (ny == row_A)
                    /* TODO: helpful error message */
                );
            }
        } // if constexpr (is_assert_v<tag_t>)

        /* placeholder for results */
        /* use clone instead of zeros_like to allow update 
            instead of fresh-compute */
        auto res = clone(y);

        for (size_t i=0; i<size(y); i++)
            for (size_t j=0; j<size(x); j++)
                at(res, i) = add(at(res,i), mul(at(x,j),at(A,i,j)));
        
        return res;

    } // constexpr auto gaxpy(const Matrix& A, const X& x, const Y& y)

    /**
     * @brief enum for norm type
     * 
     */
    enum struct norm_t {
        /**
         * @brief infinity norm
         * 
         */
        infinity_norm=3,
        /**
         * @brief frobenius norm
         * 
         */
        frobenius_norm=4,
    };

    /**
     * @brief computer P-norm of vector x
     * 
     * @tparam P norm kind: 2, 1, or inf_norm
     * @tparam Vector vector-like
     * @param x vector which its norm is to be computed
     * @return constexpr auto 
     */
    template <auto P, typename Vector>
    constexpr auto vector_norm(const Vector& x)
    {
        using norm_type = decltype(P);
        if constexpr (std::is_same_v<norm_type,norm_t>) {
            /* NOTE: need to be nested so operator== 
                will only evaluated when possible (P is norm_t) */
            if constexpr (P==norm_t::infinity_norm)
                return max(fabs(x));
        }
        else if constexpr (P==2)
            return sqrt(dot(x,x));
        else if constexpr (P==1)
            return sum(fabs(x));
    } // constexpr auto vector_norm
    
    /**
     * @brief overloaded version of vector_norm, where p is runtime value
     * 
     * @tparam Vector vector-like
     * @tparam size_type type of p
     * @param x vector which its norm is to be computed
     * @param p norm kind: 2, 1, or norm_t
     * @return constexpr auto 
     */
    template <typename Vector, typename norm_type>
    constexpr auto vector_norm(const Vector& x, norm_type p)
    {
        if constexpr (std::is_same_v<norm_type,norm_t>) {
            /* NOTE: need to be nested so operator== 
                will only evaluated when possible (P is norm_t) */
            if (p==norm_t::infinity_norm)
                return max(fabs(x));
        }
        else {
            if (p==2)
                return sqrt(dot(x,x));
            else if (p==1)
                return sum(fabs(x));
        }
    } // constexpr auto vector_norm

    template <auto P, typename Matrix>
    constexpr auto matrix_norm(const Matrix& M)
    {
        using norm_type = decltype(P);
        if constexpr (std::is_same_v<norm_type,norm_t>) {
            constexpr auto is_inf = P == norm_t::infinity_norm;
            constexpr auto is_fro = P == norm_t::frobenius_norm;
            static_assert(is_inf || is_fro);
            if constexpr (is_inf)
                return max(col_sum(fabs(M)));
            else if constexpr (is_fro)
                return sqrt(sumsq(M));
        }
        else {
            static_assert(P==1, "only support norm-1 for now");
            return max(row_sum(fabs(M)));
        }
    } // constexpr auto matrix_norm

    template <typename Matrix, typename norm_type>
    constexpr auto matrix_norm(const Matrix& M, norm_type p)
    {
        if constexpr (std::is_same_v<norm_type,norm_t>) {
            auto is_inf = p == norm_t::infinity_norm;
            auto is_fro = p == norm_t::frobenius_norm;
            // assert(is_inf || is_fro);
            if (is_inf)
                return max(col_sum(fabs(M)));
            else if (is_fro)
                return sqrt(sumsq(M));
        }
        else {
            // assert(p==1, "only support norm-1 for now");
            return max(row_sum(fabs(M)));
        }
    } // constexpr auto matrix_norm

    /**
     * @brief compute matrix/vector p-norm
     * 
     * @tparam P norm kind
     * @tparam Array matrix/vector like
     * @param x matrix/vector which it norm is to be computed
     * @return constexpr auto 
     */
    template <auto P, typename Array>
    constexpr auto norm(const Array& x)
    {
        static_assert(
            traits::is_array1d_v<Array>
            || traits::is_array2d_v<Array>
            /* TODO: helpful error message here */
        );
        if constexpr (traits::is_array1d_v<Array>)
            return vector_norm<P>(x);
        else return matrix_norm<P>(x);
    } // constexpr auto norm

    /**
     * @brief overloaded version of norm, with p as runtime value
     * 
     * @tparam Array 
     * @tparam size_type 
     * @param x 
     * @param p 
     * @return constexpr auto 
     */
    template <typename Array, typename size_type>
    constexpr auto norm(const Array& x, size_type p)
    {
        static_assert(
            traits::is_array1d_v<Array>
            || traits::is_array2d_v<Array>
            /* TODO: helpful error message here */
        );
        if constexpr (traits::is_array1d_v<Array>)
            return vector_norm(x,p);
        else return matrix_norm(x,p);
    } // constexpr auto norm

    /** @} */ // end group blas

} // namespace nmtools::blas

namespace std {
    /**
     * @ingroup blas
     * @brief overload to std::to_string for nmtools::blas::norm_t
     * 
     * @param norm norm kind
     * @return std::string "infinity" or "frobenius"
     * @note defined as inline to avoid linking error
     */
    inline std::string to_string(nmtools::blas::norm_t norm) {
        using nmtools::blas::norm_t;
        if (norm == norm_t::infinity_norm)
            return "infinity_norm";
        else if (norm == norm_t::frobenius_norm)
            return "frobenius_norm";
    }
}

#endif // NMTOOLS_BLAS_BLAS_HPP
