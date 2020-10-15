#ifndef NMTOOLS_ARRAY_UTILITY_COL_SUM_HPP
#define NMTOOLS_ARRAY_UTILITY_COL_SUM_HPP

/* common tag for preconditions, e.g. size assertion */
#include "nmtools/utility/tag.hpp"
/* common array (as in matrix/vector) utility */
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/shape.hpp"

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include <type_traits>
#include <cmath>
#include <cassert>

namespace nmtools
{
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
}

#endif // NMTOOLS_ARRAY_UTILITY_COL_SUM_HPP