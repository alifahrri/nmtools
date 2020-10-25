#ifndef NMTOOLS_ARRAY_INDEX_HPP
#define NMTOOLS_ARRAY_INDEX_HPP

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

namespace nmtools
{
    using std::size;
    using std::get;
    using std::common_type_t;
    using traits::remove_cvref_t;

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
     * @note that this is workaround for c++17 since class NTTP is not supported until c++20
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
     * @note that this is workaround for c++17 since class NTTP is not supported until c++20
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
     * @note that this is workaround for c++17 since class NTTP is not supported until c++20
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
     * @note that this is workaround for c++17 since class NTTP is not supported until c++20
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
} // namespace nmtools

#endif // NMTOOLS_ARRAY_INDEX_HPP