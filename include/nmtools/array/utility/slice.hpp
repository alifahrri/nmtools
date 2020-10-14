#ifndef NMTOOLS_ARRAY_UTILITY_SLICE_HPP
#define NMTOOLS_ARRAY_UTILITY_SLICE_HPP

#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/shape.hpp"

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

    /** @} */ // end group utility
} // namespace nmtools

#endif // NMTOOLS_ARRAY_UTILITY_SLICE_HPP