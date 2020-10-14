#ifndef NMTOOLS_ARRAY_UTILITY_SQUEEZE_HPP
#define NMTOOLS_ARRAY_UTILITY_SQUEEZE_HPP

#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"

/* TODO: should we include array and std::array specialization here? */
#include <array>
#include <tuple>
#include <type_traits>

namespace nmtools
{
    /** @addtogroup utility
    * @ingroup array
    * Collections of utility functions for array-like objects
    * @{
    */

    using traits::remove_cvref_t;
    using std::common_type_t;

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

#endif // NMTOOLS_ARRAY_UTILITY_SQUEEZE_HPP