#ifndef NMTOOLS_ARRAY_UTILITY_HPP
#define NMTOOLS_ARRAY_UTILITY_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

/* TODO: should we include array and std::array specialization here? */
#include <array>
#include <tuple>
#include <type_traits>

namespace nmtools {

    /** @addtogroup utility
    * @ingroup array
    * Collections of utility functions for array-like objects
    * @{
    */

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

    /**
     * @brief helper variable template for fixed_vector_size
     * 
     * @tparam V 
     */
    template <typename V>
    inline constexpr auto fixed_vector_size_v = fixed_vector_size<V>::value;

    using std::size;
    using std::get;

    /**
     * @brief access element at i-th index.
     * Dispatch one of the following expression whenever possible (ordered by priority):
     * (1) a.at(i);
     * (2) a[i];
     * (3) a(i);
     * 
     * @tparam Array 
     * @tparam size_type 
     * @param a 
     * @param i 
     * @return constexpr auto& 
     */
    template <typename Array, typename size_type>
    constexpr auto& at(const Array& a, size_type i)
    {
        /* TODO: this fn is returning reference,
            find out how to also support return by value
         */
        using namespace traits;

        static_assert(
            has_at_v<const Array&,size_type>
            || has_square_bracket_v<const Array&,size_type>
            || has_bracket_v<const Array&,size_type>
            /* TODO : meaningful error message here */
        );

        if constexpr (has_at_v<const Array&,size_type>)
            return a.at(i);
        else if constexpr (has_square_bracket_v<const Array&,size_type>)
            return a[i];
        else if constexpr (has_bracket_v<const Array&,size_type>)
            return a(i);
        else {
            /* compile errror */
            static_assert(has_bracket_v<const Array&,size_type>);
        }
    }

    template <auto i, typename Array>
    constexpr auto& at(const Array& a)
    {
        /* TODO: this fn is returning reference,
            find out how to also support return by value
         */
        using namespace traits;
        using size_type = decltype(i);

        static_assert(
            has_square_bracket_v<const Array&,size_type>
            || has_bracket_v<const Array&,size_type>
            /* TODO : meaningful error message here */
        );
        static_assert(
            is_fixed_size_vector_v<Array>
            && (i<fixed_vector_size_v<Array>)
        );

        if constexpr (has_square_bracket_v<const Array&,size_type>)
            return a[i];
        else if constexpr (has_bracket_v<const Array&,size_type>)
            return a(i);
        else {
            /* compile errror */
            static_assert(has_bracket_v<const Array&,size_type>);
        }
    }

    /**
     * @brief access element at i-th index.
     * Dispatch one of the following expression whenever possible (ordered by priority):
     * (1) a.at(i);
     * (2) a[i];
     * (3) a(i);
     * 
     * @tparam Array 
     * @tparam size_type 
     * @param a 
     * @param i 
     * @return constexpr auto& 
     */
    template <typename Array, typename size_type>
    constexpr auto& at(Array& a, size_type i)
    {
        using namespace traits;
        static_assert(
            has_at_v<Array&,size_type>
            || has_square_bracket_v<Array&,size_type>
            || has_bracket_v<Array&,size_type>
            /* TODO : meaningful error message here */
        );

        if constexpr (has_at_v<Array&,size_type>)
            return a.at(i);
        else if constexpr (has_square_bracket_v<Array&,size_type>)
            return a[i];
        else if constexpr (has_bracket_v<Array&,size_type>)
            return a(i);
        else {
            /* compile errror */
            static_assert(has_bracket_v<Array&,size_type>);
        }
    } // constexpr auto& at

    /**
     * @brief access element at (i,j) index.
     * Dispatch the following expression whenever possible (ordered by priority):
     * (1) a.at(i,j);
     * (2) a[i,j];
     * (3) a(i,j);
     * (4) at(at(a,i),j);
     * 
     * @tparam Array 
     * @tparam size_type 
     * @param a 
     * @param i 
     * @param j 
     * @return constexpr auto& 
     */
    template <typename Array, typename size_type>
    constexpr auto& at(const Array& a, size_type i, size_type j)
    {
        /* TODO: this fn is returning reference,
            find out how to also support return by value
         */
        using namespace traits;
        if constexpr (has_at2d_v<const Array&,size_type>)
            return a.at(i,j);
        else if constexpr (has_square_bracket2d_v<const Array&,size_type>)
            return a[i,j];
        else if constexpr (has_bracket2d_v<const Array&,size_type>)
            return a(i,j);
        else {
            return at(at(a,i),j);
        }
    } // constexpr auto& at(const Array& a, size_type i, size_type j)

    template <auto i, auto j, typename Array>
    constexpr auto& at(const Array& a)
    {
        /* TODO: this fn is returning reference,
            find out how to also support return by value
         */
        using namespace traits;
        using size_type = std::common_type_t<decltype(i),decltype(j)>;
        constexpr auto shape = fixed_matrix_size_v<Array>;
        constexpr auto rows = get<0>(shape);
        constexpr auto cols = get<1>(shape);
        static_assert(
            is_fixed_size_matrix_v<Array>
            && (i<rows && j<cols)
        );
        if constexpr (has_square_bracket2d_v<const Array&,size_type>)
            return a[i,j];
        else if constexpr (has_bracket2d_v<const Array&,size_type>)
            return a(i,j);
        else {
            return at<j>(at<i>(a));
        }
    } // constexpr auto& at(const Array& a, size_type i, size_type j)

    /**
     * @brief access element at (i,j) index.
     * Dispatch the following expression whenever possible (ordered by priority):
     * (1) a.at(i,j);
     * (2) a[i,j];
     * (3) a(i,j);
     * (4) at(at(a,i),j);
     * 
     * @tparam Array 
     * @tparam size_type 
     * @param a 
     * @param i 
     * @param j 
     * @return constexpr auto& 
     */
    template <typename Array, typename size_type>
    constexpr auto& at(Array& a, size_type i, size_type j)
    {
        using namespace traits;
        if constexpr (has_at2d_v<Array&,size_type>)
            return a.at(i,j);
        else if constexpr (has_square_bracket2d_v<Array&,size_type>)
            return a[i,j];
        else if constexpr (has_bracket2d_v<Array&,size_type>)
            return a(i,j);
        else {
            return at(at(a,i),j);
        }
    } // constexpr auto& at(Array& a, size_type i, size_type j)

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
     * @brief specialization of fixed_vector size for raw arary
     * 
     * @tparam T element type of raw array, automatically deduced
     * @tparam N size of raw array, automatically deduced
     */
    template <typename T, size_t N>
    struct fixed_vector_size<T[N]>
    {
        static inline constexpr auto value = N;
    };

    /**
     * @brief generic function to get size of dynamic-matrix, assuming nested vector.
     * May be specialized for custom dynamic-matrix type.
     * 
     * @tparam Matrix matrix-like
     * @param M matrix to check
     * @return std::pair<size_t,size_t> row-col pair
     */
    template <typename Matrix>
    constexpr auto matrix_size(const Matrix& M)
    {
        static_assert(
            traits::is_array2d_v<Matrix>
            /* TODO: meaningful error message */
        );
        /* TODO: check all size for each rows. 
        Nested vector container may have different size at axis 0 */
        return std::make_pair(size(M), size(at(M,0)));
    } // std::pair<size_t,size_t> matrix_size(const Matrix& M)

    /**
     * @brief generic function to get size of dynamic-vector (as in math vector, not container).
     * May be specialized for custom dynamic-matrix type.
     * 
     * @tparam Vector vector-like
     * @param v vector to check
     * @return size_t 
     */
    template <typename Vector>
    constexpr size_t vector_size(const Vector& v)
    {
        static_assert(
            traits::is_array1d_v<Vector>
            /* TODO: meaningful error message */
        );

        return size(v);
    } // size_t matrix_size(const Vector& v)

    /**
     * @brief given marix M, get its r-th row.
     * 
     * @tparam Matrix matrix-like
     * @param M matrix in which its row to be taken.
     * @param r row.
     * @return constexpr auto 
     */
    template <typename Matrix>
    constexpr auto row(const Matrix& M, size_t r)
    {
        static_assert(
            traits::is_array2d_v<Matrix>
            /* TODO: helpful error message here */
        );
        // assuming possibly nested matrix or its
        // at operator support single indexing
        return at(M,r);
    } // constexpr auto row(const Matrix, size_type r)

    namespace detail {
        /**

         * @brief given array-like a, make array of type array_t,
         * where the element is initialized using elements of array-like a
         * at indices I... with offset, e.g. {a[I+offset]...}.
         * 
         * @tparam array_t desired array_t, asuming aggregate initialization is well-formed
         * @tparam T array-like
         * @tparam I integer sequence to take elements of a
         * @param a array to initialize the resulting array
         * @param offset index offset
         * @return constexpr auto 
         */
        template <typename array_t, typename T, size_t ...I>
        constexpr auto make_array(const T &a, std::integer_sequence<size_t, I...>, size_t offset=0)
        {
            return array_t{a[I+offset]...};
        }
    }

    /**
     * @brief specialization of row function for nested raw array.
     * 
     * @tparam T element type of raw array
     * @tparam M size of array at first axis, automatically deduced
     * @tparam N size of array at second axis, automatically deduced
     * @param r row
     * @return constexpr auto 
     */
    template <typename T, size_t M, size_t N>
    constexpr auto row(const T(&t)[M][N], size_t r)
    {
        using array_t = std::array<T,N>;
        using index_t = std::make_index_sequence<N>;
        return detail::make_array<array_t>(t[r],index_t{});
    } // constexpr auto row

    /**
     * @brief 
     * 
     */
    namespace detail {
        /**

         * @brief 
         * 
         * @param col 
         * @param M 
         * @param c 
         * @param rows 
         * @return constexpr auto 
         */
        constexpr auto column_impl(auto &col, const auto& M, size_t c, size_t rows)
        {
            for (size_t i=0; i<rows; i++)
                at(col,i) = at(M,i,c);
        } // constexpr auto column_impl
    } // namespace detail

    /**
     * @brief 
     * 
     * @tparam T 
     * @param c 
     * @return constexpr auto 
     */
    template <typename T>
    constexpr auto column(const T& M, size_t c)
    {
        static_assert(
            traits::is_array2d_v<T>
            /* TODO: helpful error message here */
        );
        using detail::column_impl;
        using column_t = meta::get_column_type_t<T>;
        static_assert(
            !std::is_same_v<column_t,void>,
            "unsupported column type, may be specialization "
            "of nmtools::meta::get_column_type needed (?)"
        );
        constexpr auto is_fixed_size = traits::is_fixed_size_vector_v<column_t>;
        constexpr auto is_resizeable = traits::is_resizeable_v<column_t>;
        if constexpr (is_fixed_size) {
            // NOTE: move instantiation here to make error message less verbose
            auto col = column_t{};
            constexpr auto rows = vector_size(col);
            column_impl(col,M,c,rows);
            return col;
        }
        else if constexpr (is_resizeable) {
            // NOTE: move instantiation here to make error message less verbose
            auto col = column_t{};
            auto [rows,cols] = matrix_size(M);
            col.resize(rows);
            column_impl(col,M,c,rows);
            return col;
        }
        else {
            static_assert(is_fixed_size || is_resizeable);
        }
    } // constexpr auto column

    /**
     * @brief implementation details for slice
     * 
     */
    namespace detail {

        using std::common_type_t;
        using traits::remove_cvref_t;

        /**

         * @brief implementation of slice,
         * assuming `x` is already resized / has size of stop-start.
         * 
         * @param x array-like to be filled with v at corresponding indices
         * @param v array-like to fill `x`
         * @param start start index
         * @param stop stop index
         * @return constexpr auto 
         */
        constexpr auto slice_impl(auto &x, const auto& v, auto start, auto stop)
        {
            /* TODO: support step */
            using start_t = decltype(start);
            using stop_t  = decltype(stop);
            using idx_t   = remove_cvref_t<common_type_t<start_t,stop_t>>;
            auto n = stop - start;
            auto step = idx_t{1};
            for (idx_t i=0; i<n; i+=step)
                at(x,i) = at(v,i+start);
        } // constexpr auto slice_impl
        
    } // namespace detail

    /**
     * @brief given vector-like v, return new vector-like
     * containing value of `v` from `start` index until `stop` index,
     * e.g. `v[start:stop]` in python.
     * 
     * @tparam T vector-like & resizeable
     * @param v 
     * @param start 
     * @param stop 
     * @return constexpr auto 
     */
    template <typename T>
    constexpr auto slice(const T& v, auto start, auto stop)
    {
        static_assert(
            traits::is_array1d_v<T>
            && traits::is_resizeable_v<T>
            /* TODO: helpful error message here */
        );
        /* TODO: support step */
        auto new_size = stop - start;
        auto sliced = T{};
        sliced.resize(new_size);

        using detail::slice_impl;
        slice_impl(sliced,v,start,stop);

        return sliced;
    } // constexpr auto slice

    /**
     * @brief given vector-like `v`, return new vector-like
     * containing value of `v` from `start` index until `stop` index,
     * e.g. `v[start:stop]` in python.
     * 
     * @tparam start compile-time constant start index
     * @tparam stop compile-time constant stop index
     * @tparam T vector-like
     * @param v 
     * @return constexpr auto 
     */
    template <auto start, auto stop, typename T>
    constexpr auto slice(const T& v)
    {
        using detail::slice_impl;
        static_assert(
            traits::is_array1d_v<T>
            /* TODO: helpful error message here */
        );
        /* TODO: support step */
        constexpr auto new_size = stop - start;
        constexpr auto is_fixed_size = traits::is_fixed_size_vector_v<T>;
        /**
         * @brief slice fixed array, get resized type
         * using resize_fixed_vector metafunction
         * 
         */
        if constexpr (is_fixed_size) {
            using sliced_t = meta::resize_fixed_vector_t<T,new_size>;
            auto sliced = sliced_t{};

            slice_impl(sliced,v,start,stop);

            return sliced;
        }
        /**
         * @brief slice dynamic array
         * 
         */
        else {
            static_assert(traits::is_resizeable_v<T>);
            auto sliced = T{};
            sliced.resize(new_size);

            slice_impl(sliced,v,start,stop);

            return sliced;
        }
    } // constexpr auto slice

    /** @} */ // end group utility
} // namespace nmtools

/* extend traits for fixed_size_matrix & fixed_size_vector */
namespace nmtools::traits {

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
} // namespace nmtools::traits

#endif // NMTOOLS_ARRAY_UTILITY_HPP