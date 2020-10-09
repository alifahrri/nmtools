#ifndef NMTOOLS_ARRAY_UTILITY_HPP
#define NMTOOLS_ARRAY_UTILITY_HPP

#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp"
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
            || has_bracket_v<const Array&,size_type>,
            "unsupported type Array for at"
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
    constexpr auto matrix_size(const Matrix& M) -> std::enable_if_t<traits::is_nested_array2d_v<Matrix>,std::pair<size_t,size_t>>
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
    } // size_t vector_size(const Vector& v)

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
         * @brief implementation of slice for 1D array,
         * assuming `x` is already resized / has size of stop-start.
         * 
         * @param x array-like to be filled with v at corresponding indices
         * @param v array-like to fill `x`
         * @param start start index
         * @param stop stop index
         * @return constexpr auto 
         * @see nmtools::slice
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

        /**
         * @brief implementation of slice for 2D array,
         * assuming `x` is already resized.
         * 
         * @param x array-like to be filled with v at corresponding indices
         * @param m array-like to fill `x`
         * @param row_start 
         * @param col_start 
         * @param row_stop 
         * @param col_stop 
         * @return constexpr auto 
         * @see nmtools::slice
         */
        constexpr auto slice_impl(auto &x, const auto& m, auto row_start, auto col_start, auto row_stop, auto col_stop)
        {
            /* TODO: support step */
            using row_start_t = decltype(row_start);
            using row_stop_t  = decltype(row_stop);
            using col_start_t = decltype(col_start);
            using col_stop_t  = decltype(col_stop);
            using _idx_t  = common_type_t<row_start_t,row_stop_t,col_start_t,col_stop_t>;
            using idx_t   = remove_cvref_t<_idx_t>;
            auto rows = row_stop - row_start;
            auto cols = col_stop - col_start;
            auto step = idx_t{1};
            for (idx_t i=0; i<rows; i+=step)
                for (idx_t j=0; j<cols; j+=step)
                    at(x,i,j) = at(m,i+row_start,j+col_start);
        } // constexpr auto slice_impl
        
    } // namespace detail

    /**
     * @brief special tag to represent end index, used for slicing.
     * 
     * @see nmtools::slice
     */
    struct end_t {};

    /**
     * @brief helper alias template for std::integral_constant<size_t,...>
     * 
     * @tparam N 
     * @see nmtools::slice
     * @see nmtools::make_slice_index
     */
    template <size_t N>
    using index_constant = std::integral_constant<size_t,N>;

    /**
     * @brief helper function to create compile-time slice index
     * 
     * @tparam i non-type template parameter representing slicing index
     * @return constexpr auto index_constant
     * @see nmtools::slice
     * @see nmtools::index_constant
     */
    template <auto i>
    constexpr auto make_slice_index()
    {
        return index_constant<i>{};
    } // make_slice_index

    /**
     * @brief helper function to create compile-time slice index
     * 
     * @tparam i template parameter representing slicing index
     * @return constexpr auto index_constant
     * @see nmtools::slice
     * @see nmtools::index_constant
     * @todo constraint to nmtools::end_t only
     */
    template <typename i>
    constexpr auto make_slice_index()
    {
        return i{};
    } // make_slice_index

    /**
     * @brief helper function to create compile-time slice indices,
     * effectively maps compile-time value to type.
     * 
     * @tparam i index of 1st axis, expects a value
     * @tparam j index of 2nd axis, expects a value
     * @return constexpr auto tuple of index_constant
     * @see nmtools::index_constant
     * @note that this is workaround for c++17 since NTTP is not supported until c++20
     */
    template <auto i, auto j>
    constexpr auto make_slice_index()
    {
        return std::make_tuple(index_constant<i>{},index_constant<j>{});
    } // make_slice_index

    /**
     * @brief helper function to create compile-time slice indices
     * effectively maps compile-time value to type.
     * 
     * @tparam i index of 1st axis, expects a type, e.g. nmtools::end_t
     * @tparam j index of 2nd axis, expects a type, e.g. nmtools::end_t
     * @return constexpr auto tuple of index_constant
     * @see nmtools::end_t
     * @note that this is workaround for c++17 since NTTP is not supported until c++20
     */
    template <typename i, typename j>
    constexpr auto make_slice_index()
    {
        return std::make_tuple(i{},j{});
    } // make_slice_index

    /**
     * @brief helper function to create compile-time slice indices
     * effectively maps compile-time value to type.
     * 
     * @tparam i index of 1st axis, expects a value
     * @tparam j index of 2nd axis, expects a type, e.g. nmtools::end_t
     * @return constexpr auto tuple of index_constant and given type
     * @see nmtools::end_t
     * @see nmtools::index_constant
     * @note that this is workaround for c++17 since NTTP is not supported until c++20
     */
    template <auto i, typename j>
    constexpr auto make_slice_index()
    {
        return std::make_tuple(index_constant<i>{},j{});
    } // make_slice_index

    /**
     * @brief helper function to create compile-time slice indices
     * effectively maps compile-time value to type.
     * 
     * @tparam i index of 1st axis, expects a type, e.g. nmtools::end_t
     * @tparam j index of 2nd axis, expects a value
     * @return constexpr auto tuple of given type and index_constant
     * @see nmtools::end_t
     * @see nmtools::index_constant
     * @note that this is workaround for c++17 since NTTP is not supported until c++20
     */
    template <typename i, auto j>
    constexpr auto make_slice_index()
    {
        return std::make_tuple(i{},index_constant<j>{});
    } // make_slice_index

    namespace detail {
        using std::is_same_v;
        using std::is_integral_v;
        using traits::is_array2d_v;
        using traits::is_array1d_v;
        using traits::is_fixed_size_matrix_v;
        using traits::is_fixed_size_vector_v;
        using traits::is_integral_constant_v;
        /**
         * @brief return type for unpack_slice_indices for 2D array
         * 
         */
        using array2d_slice_indices_t = std::tuple<std::tuple<size_t,size_t>,std::tuple<size_t,size_t>>;
        /**
         * @brief return type for unpack_slice_indices for 1D array
         * 
         */
        using array1d_slice_indices_t = std::tuple<size_t,size_t>;

        /**
         * @brief helper function to unpack slice indices for 2D array
         * in which start & stop may be pair of integral_constant & special tag end_t
         * 
         * @tparam Array fixed-size 2D array
         * @param start compile-time start indices pair
         * @param stop compile-time stop indices pair
         * @return std::enable_if_t<is_array2d_v<Array>,array2d_slice_indices_t> 
         * @see array2d_slice_indices_t
         * @see slice
         */
        template <typename Array>
        constexpr auto unpack_slice_indices(const Array& a, auto start, auto stop)
            -> std::enable_if_t<is_array2d_v<Array>, array2d_slice_indices_t>
        {
            // unpack start & stop
            auto [row_start_, col_start_] = start;
            auto [row_stop_, col_stop_] = stop;
            using row_start_t = decltype(row_start_);
            using col_start_t = decltype(col_start_);
            using row_stop_t  = decltype(row_stop_);
            using col_stop_t  = decltype(col_stop_);
            constexpr bool valid_row_stop = is_integral_v<row_stop_t> || is_integral_constant_v<row_stop_t> || is_same_v<row_stop_t,end_t>;
            constexpr bool valid_col_stop = is_integral_v<col_stop_t> || is_integral_constant_v<col_stop_t> || is_same_v<col_stop_t,end_t>;
            // assuming 2D array
            // make sure valid type, strictly integral_constant for start
            // while stop is possibly contains end_t
            static_assert (
                traits::is_array2d_v<Array>
                && (is_integral_constant_v<row_start_t> || is_integral_v<row_start_t>)
                && (is_integral_constant_v<col_start_t> || is_integral_v<col_start_t>)
                && valid_row_stop && valid_col_stop,
                "failed to unpack slice indices, expects packed type of "
                " start_t is integral_constant and"
                " packed type of stop_t may be integral_constant or end_t"
            );
            auto [rows, cols] = matrix_size(a);
            // unpack integral constant type to value
            // use immediately invoked lambda to expose variable to outer scope while actual packing is
            // dispatched based on the type using constexpr if
            auto istart = [&](){
                if constexpr (is_integral_constant_v<row_start_t> && is_integral_constant_v<col_start_t>)
                    return std::make_tuple(row_start_(), col_start_());
                else
                    return std::make_tuple(row_start_, col_start_);
            }();
            auto istop = [&](){
                // both stop is end tag
                if constexpr (is_same_v<row_stop_t,end_t> && is_same_v<col_stop_t,end_t>)
                    return std::make_tuple(rows, cols);
                // only row is end tag, col stop is compile time constant
                else if constexpr (is_same_v<row_stop_t,end_t> && is_integral_constant_v<col_stop_t>)
                    return std::make_tuple(rows, col_stop_());
                // only col is end tag, row stop is compile time constant
                else if constexpr (is_integral_constant_v<row_stop_t> && is_same_v<col_stop_t,end_t>)
                    return std::make_tuple(row_stop_(), cols);
                // both is compile time constant
                else if constexpr (is_integral_constant_v<row_stop_t> && is_integral_constant_v<col_stop_t>)
                    return std::make_tuple(row_stop_(), col_stop_());
                // only row is end tag, col stop is simply integer
                else if constexpr (is_same_v<row_stop_t,end_t> && is_integral_v<col_stop_t>)
                    return std::make_tuple(rows, col_stop_);
                // only col is end tag, row stop is simply integer
                else if constexpr (is_integral_v<row_stop_t> && is_same_v<col_stop_t,end_t>)
                    return std::make_tuple(row_stop_, cols);
                // both is simpy integer
                else if constexpr (is_integral_v<row_stop_t> && is_integral_v<col_stop_t>)
                    return std::make_tuple(row_stop_, col_stop_);
            }();
            return std::make_tuple(istart, istop);
        } // constexpr auto unpack_slice_indices

        /**
         * @brief helper function to unpack slice indices for 1D array
         * in which start is integral_constant and stop may be integral_constant or special tag end_t
         * 
         * @tparam Array fixed-size 1D array
         * @param start compile-time start index
         * @param stop compile-time stop index
         * @return std::enable_if_t<!is_array2d_v<Array> && is_array1d_v<Array>,array1d_slice_indices_t> 
         */
        template <typename Array>
        constexpr auto unpack_slice_indices(const Array& a, auto start, auto stop)
            -> std::enable_if_t<!is_array2d_v<Array> && is_array1d_v<Array>,array1d_slice_indices_t>
        {
            using start_t = decltype(start);
            using stop_t  = decltype(stop);
            auto n = vector_size(a);
            if constexpr (is_integral_constant_v<start_t> && is_same_v<stop_t,end_t>)
                return std::make_tuple(start(),n);
            else if constexpr (is_integral_constant_v<start_t> && is_integral_constant_v<stop_t>)
                return std::make_tuple(start(),stop());
            else if constexpr (is_integral_v<start_t> && is_same_v<stop_t,end_t>)
                return std::make_tuple(start,n);
            else if constexpr (is_integral_v<start_t> && is_integral_v<stop_t>)
                return std::make_tuple(start,stop);
        } // constexpr auto unpack_slice_indices
    } // namespace detail

    /**
     * @brief given a 1D or 2D array, return new array
     * containing value of `a` from `start` index until `stop` index,
     * e.g. `v[start:stop]` in python.
     * 
     * @tparam T vector-like & resizeable
     * @tparam start_t start type of start index, can be integer, index_constant, or pair-like of integer/index_constant
     * @tparam stop_t stop type of stop index, can be integer, index_constant, or pair-like of integer/index_constant/end_t
     * @param a
     * @param start start index
     * @param stop stop index
     * @return constexpr auto 
     * @see nmtools::detail::slice_impl
     * @see nmtools::traits::is_fixed_size_vector_v
     * @see nmtools::meta::resize_fixed_vector_t
     * @see nmtools::traits::is_resizeable_v
     * @see nmtools::make_slice_index
     * @see nmtools::end_t
     * @note when using fixed array, start and stop should be known at compile-time
     * @todo consider to allow runtime start and stop for fixed array by providing fixed -> dynamic metafunction
     */
    template <typename start_t, typename stop_t, typename T>
    constexpr auto slice(const T& a, const start_t& start=start_t{}, const stop_t& stop=stop_t{})
    {
        static_assert(
            traits::is_array1d_v<T>
            || traits::is_array2d_v<T>,
            "only support resizeable 1D or 2D array for now"
        );
        using traits::remove_cvref_t;
        // note: need to remove_cvref because is_tuple doesnt remove cvref and start_t may be cvref
        constexpr auto start_is_tuple = traits::is_tuple_v<remove_cvref_t<start_t>>;
        constexpr auto stop_is_tuple  = traits::is_tuple_v<remove_cvref_t<stop_t>>;
        static_assert (start_is_tuple == stop_is_tuple,
            "only support same traits for both start_t & stop_t, "
            "either both is tuple-like or not"
        );
        static_assert (
            // not tuple and 1D array, start stop is simply integer
            (!start_is_tuple && traits::is_array1d_v<T>)
            // tuple and 2d array, start stop is pair of integer
            || (start_is_tuple && traits::is_array2d_v<T>),
            "for tuple like index, T should be matrix like"
        );
        using detail::slice_impl;
        using detail::unpack_slice_indices;
        using ::nmtools::matrix_size;

        constexpr auto is_fixed_size = traits::is_fixed_size_matrix_v<T> || traits::is_fixed_size_vector_v<T>;
    
        // handle fixed size 2D array, start_t and stop_t must be tuple
        if constexpr (start_is_tuple && stop_is_tuple && is_fixed_size) {
            // get resulting size from given start & stop pair
            /* TODO: support step */
            // when using fixed array, start and stop must be constexpr
            constexpr auto ct_start = start_t{};
            constexpr auto ct_stop  = stop_t{};
            constexpr auto indices = unpack_slice_indices(a,ct_start,ct_stop);
            constexpr auto start_indices = std::get<0>(indices);
            constexpr auto stop_indices  = std::get<1>(indices);
            constexpr auto row_start = std::get<0>(start_indices);
            constexpr auto col_start = std::get<1>(start_indices);
            constexpr auto row_stop  = std::get<0>(stop_indices);
            constexpr auto col_stop  = std::get<1>(stop_indices);
            constexpr auto rows = row_stop - row_start;
            constexpr auto cols = col_stop - col_start;

            using sliced_t = meta::resize_fixed_matrix_t<T,rows,cols>;
            static_assert(!std::is_same_v<sliced_t,void>,
                "failed to get return type of slice, may be specialization of"
                " nmtools::meta::resize_fixed_matrix required (?)"
            );
            auto sliced = sliced_t{};

            slice_impl(sliced,a,row_start,col_start,row_stop,col_stop);
            return sliced;
        }
        // handle fixed size 1D array, start_t and stop_t are simply integral constant
        else if constexpr (!start_is_tuple && !stop_is_tuple && is_fixed_size) {
            // when using fixed array, start and stop must be constexpr
            constexpr auto ct_start = start_t{};
            constexpr auto ct_stop  = stop_t{};
            constexpr auto indices = unpack_slice_indices(a,ct_start,ct_stop);
            /* TODO: support step */
            constexpr auto start_ = std::get<0>(indices);
            constexpr auto stop_  = std::get<1>(indices);
            constexpr auto new_size = stop_ - start_;
            // slice fixed array, get resized type using resize_fixed_vector metafunction
            using sliced_t = meta::resize_fixed_vector_t<T,new_size>;
            static_assert (!std::is_same_v<sliced_t,void>,
                "failed to get return type of slice, may be specialization of"
                " nmtools::meta::resize_fixed_vector required (?)"
            );
            auto sliced = sliced_t{};

            slice_impl(sliced,a,start_,stop_);
            return sliced;
        }
        // both index is tuple like and T is matrix-like
        // resizeable matrix slice, v should be 2D
        else if constexpr (start_is_tuple && stop_is_tuple && !is_fixed_size) {
            auto sliced = T{};
            auto [start_, stop_] = unpack_slice_indices(a,start,stop);
            auto [row_start, col_start] = start_;
            auto [row_stop, col_stop]   = stop_;
            /* TODO: support step */
            auto rows = row_stop - row_start;
            auto cols = col_stop - col_start;
            // TODO: consider to provide helper function for resize
            if constexpr (traits::is_resizeable2d_v<T>)
                sliced.resize(rows, cols);
            else {
                sliced.resize(rows);
                for (auto& s : sliced)
                    s.resize(cols);
            }
            // call overloaded slice_impl
            slice_impl(sliced,a,row_start,col_start,row_stop,col_stop);
            return sliced;
        } // matrix slice
        // resizeable vector slice, v should be 1D
        else if constexpr (!start_is_tuple && !stop_is_tuple && !is_fixed_size) {
            auto sliced = T{};
            auto [start_, stop_] = unpack_slice_indices(a,start,stop);
            /* TODO: support step */
            auto new_size = stop_ - start_;
            sliced.resize(new_size);
            // call default slice_impl
            slice_impl(sliced,a,start_,stop_);
            return sliced;
        } // vector slice
    } // constexpr auto slice

    namespace detail {

        /**
         * @brief implementation loop of squeeze when it is actually possible (single dimensional shape detected)
         * 
         * @tparam single_dim axis which single dimension is detected
         * @tparam row_t type of row size
         * @tparam col_t type of column size
         * @param squeezed placeholder for result
         * @param array array to be squeezed
         * @param rows number of rows
         * @param cols number of cols
         * @return std::enable_if_t<single_dim==0||single_dim==1> 
         * @note this may be simply copy the array elements
         * @todo support view
         */
        template <size_t single_dim, typename row_t, typename col_t>
        constexpr auto squeeze_impl(auto &squeezed, const auto& array, row_t rows, col_t cols, index_constant<single_dim>)
            -> std::enable_if_t<single_dim==0||single_dim==1>
        {
            using idx_t = remove_cvref_t<common_type_t<row_t,col_t>>;
            auto numel = [&](){
                if constexpr (single_dim==0) return cols;
                else return rows;
            }();
            for (idx_t i=0; i<numel; i++)
                at(squeezed,i) = [&](){
                    if constexpr (single_dim==0)
                        return at(array,idx_t{0},i);
                    else return at(array,i,idx_t{0});
                }();
        } // squeeze_impl

        /**
         * @brief implementation loop of squeeze when squeeze is not detected at compile-time.
         * 
         * @tparam size_type either simply integer or integral_constant
         * @tparam row_t type of row size
         * @tparam col_t type of column size
         * @param squeezed placeholder for result
         * @param array array to be squeezed
         * @param rows number of rows
         * @param cols number of cols
         * @param single_dim axis which single dimension is detected
         * @return constexpr auto 
         */
        template <typename size_type, typename row_t, typename col_t>
        constexpr auto squeeze_impl(auto &squeezed, const auto& array, row_t rows, col_t cols, size_type single_dim)
        {
            auto numel = [&]()->int{
                if (single_dim==0) return cols;
                else if (single_dim==1) return rows;
                else return -1;
            }();
            using idx_t = remove_cvref_t<common_type_t<row_t,col_t,decltype(numel)>>;
            if constexpr (traits::is_integral_constant_v<size_type>) {
                for (idx_t i=0; i<rows; i++)
                    for (idx_t j=0; j<cols; j++)
                        at(squeezed,i,j) = at(array,i,j);
            }
            else {
                for (idx_t i=0; i<numel; i++)
                    at(squeezed,i) = [&](){
                        if (single_dim==0)
                            return at(array,idx_t{0},i);
                        else return at(array,i,idx_t{0});
                    }();
            }
        } // squeeze_impl
    } // namespace detail

    /**
     * @brief remove single dimensional entries from the shape of an array
     * 
     * @tparam Array 2D array
     * @param a 2D array to be squeezed
     * @return constexpr auto 
     * @note when dynamic matrix is passed, the checking is performed at runtime
     * while the returned result is vector-like
     */
    template <typename Array>
    constexpr auto squeeze(const Array& a)
    {
        static_assert(
            traits::is_array2d_v<Array>,
            "squeeze only support 2D array for now"
        );

        using detail::squeeze_impl;

        constexpr auto is_fixed_size = traits::is_fixed_size_matrix_v<Array>;

        using vector_t   = meta::get_column_type_t<Array>;
        static_assert(!std::is_same_v<vector_t,void>,
            "squeeze unable to deduce vector type from Array, "
            "may be specialization of nmtools::meta::get_column_type required (?)"
        );

        constexpr auto get_single_dim_axis = [&](auto rows, auto cols){
            if (rows==1) return 0;
            else if (cols==1) return 1;
            else return 2;
        };

        if constexpr (is_fixed_size) {
            constexpr auto shape = matrix_size(a);
            constexpr auto rows = std::get<0>(shape);
            constexpr auto cols = std::get<1>(shape);
            // note: use immediately invoked lambda to expose return value to outer scope
            // instead of directly use constexpr if that define new scope
            constexpr auto single_dim_axis = get_single_dim_axis(rows, cols);
            using single_dim_axis_t = index_constant<single_dim_axis>;
            if constexpr ((single_dim_axis==0)||(single_dim_axis==1)) {
                constexpr auto new_size = std::max(rows,cols);
                using squeezed_t = meta::resize_fixed_vector_t<vector_t,new_size>;
                auto squeezed = squeezed_t{};
                squeeze_impl(squeezed, a, rows, cols, single_dim_axis_t{});
                return squeezed;
            }
            else {
                return a;
            }
        }
        else {
            auto [rows, cols] = matrix_size(a);
            auto new_size = std::max(rows,cols);
            auto single_dim_axis = get_single_dim_axis(rows, cols);
            // TODO: explore more error handling
            assert ((single_dim_axis==0) || (single_dim_axis==1));
            auto squeezed = vector_t{};
            squeezed.resize(new_size);
            squeeze_impl(squeezed, a, rows, cols, single_dim_axis);
            return squeezed;
        }
    } // squeeze

    /** @} */ // end group utility
} // namespace nmtools

#endif // NMTOOLS_ARRAY_UTILITY_HPP