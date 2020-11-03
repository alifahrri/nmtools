#ifndef NMTOOLS_ARRAY_UTILITY_SLICE_HPP
#define NMTOOLS_ARRAY_UTILITY_SLICE_HPP

#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"

/* TODO: should we include array and std::array specialization here? */
#include <array>
#include <tuple>
#include <type_traits>

#include "nmtools/array/index.hpp"

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
        using meta::remove_cvref_t;

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
     * @brief given a 1D or 2D array, return new array
     * containing value of `a` from `start` index until `stop` index,
     * e.g. `v[start:stop]` in python.
     * 
     * @tparam T vector-like & resizeable
     * @tparam start_t start type of start index, can be integer, meta::index_constant, or pair-like of integer/meta::index_constant
     * @tparam stop_t stop type of stop index, can be integer, meta::index_constant, or pair-like of integer/meta::index_constant/end_t
     * @param a
     * @param start start index
     * @param stop stop index
     * @return constexpr auto 
     * @see nmtools::detail::slice_impl
     * @see nmtools::meta::is_fixed_size_vector_v
     * @see nmtools::meta::resize_fixed_vector_t
     * @see nmtools::meta::is_resizeable_v
     * @see nmtools::make_slice_index
     * @see nmtools::end_t
     * @note when using fixed array, start and stop should be known at compile-time
     * @todo consider to allow runtime start and stop for fixed array by providing fixed -> dynamic metafunction
     */
    template <typename start_t, typename stop_t, typename T>
    constexpr auto slice(const T& a, const start_t& start=start_t{}, const stop_t& stop=stop_t{})
    {
        static_assert(
            meta::is_array1d_v<T>
            || meta::is_array2d_v<T>,
            "only support resizeable 1D or 2D array for now"
        );
        using meta::remove_cvref_t;
        // note: need to remove_cvref because is_tuple doesnt remove cvref and start_t may be cvref
        constexpr auto start_is_tuple = meta::is_tuple_v<remove_cvref_t<start_t>>;
        constexpr auto stop_is_tuple  = meta::is_tuple_v<remove_cvref_t<stop_t>>;
        static_assert (start_is_tuple == stop_is_tuple,
            "only support same traits for both start_t & stop_t, "
            "either both is tuple-like or not"
        );
        static_assert (
            // not tuple and 1D array, start stop is simply integer
            (!start_is_tuple && meta::is_array1d_v<T>)
            // tuple and 2d array, start stop is pair of integer
            || (start_is_tuple && meta::is_array2d_v<T>),
            "for tuple like index, T should be matrix like"
        );
        using detail::slice_impl;
        using detail::unpack_slice_indices;
        using ::nmtools::matrix_size;

        constexpr auto is_fixed_size = meta::is_fixed_size_matrix_v<T> || meta::is_fixed_size_vector_v<T>;
    
        // handle fixed size 2D array, start_t and stop_t must be tuple
        if constexpr (start_is_tuple && stop_is_tuple && is_fixed_size) {
            // get resulting size from given start & stop pair
            /* TODO: support step */
            // when using fixed array, start and stop must be constexpr
            constexpr auto ct_start = start_t{};
            constexpr auto ct_stop  = stop_t{};
            // workaround for clang (which turns out to be correct)
            // parameter to unpack_slice_indices must be constexpr,
            // since we have fixed-size array, the size is embedded to the type itself
            // assuming fixed-size array are constexpr-ready
            // @todo pass value to unpack slice indices not the object itself
            constexpr T a_{};
            constexpr auto indices = unpack_slice_indices(a_,ct_start,ct_stop);
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
            // workaround for clang (which turns out to be correct)
            // parameter to unpack_slice_indices must be constexpr,
            // since we have fixed-size array, the size is embedded to the type itself
            // assuming fixed-size array are constexpr-ready
            // @todo pass value to unpack slice indices not the object itself
            constexpr T a_{};
            constexpr auto indices = unpack_slice_indices(a_,ct_start,ct_stop);
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
            if constexpr (meta::is_resizeable2d_v<T>)
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