#ifndef NMTOOLS_ARRAY_UTILITY_SUM_HPP
#define NMTOOLS_ARRAY_UTILITY_SUM_HPP

/* common tag for preconditions, e.g. size assertion */
#include "nmtools/utility/tag.hpp"
/* common array (as in matrix/vector) utility */
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include <type_traits>
#include <cmath>
#include <cassert>

namespace nmtools
{
    namespace detail {
        /**
         * @brief implementation of sum for 1D array
         * 
         * @param sum input/output sum
         * @param a array to be summed
         * @param n number of elements in array a
         * @return constexpr auto 
         */
        template <typename return_t, typename array_t, typename size_type>
        constexpr auto sum_impl(return_t& sum, const array_t& a, size_type n)
        {
            using idx_t = meta::remove_cvref_t<decltype(n)>;
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
        template <typename return_t, typename array_t, typename rows_t, typename cols_t>
        constexpr auto sum_impl(return_t& sum, const array_t& a, rows_t rows, cols_t cols)
        {
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
            meta::is_array1d_v<Array>
            || meta::is_array2d_v<Array>,
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
        if constexpr (meta::is_array2d_v<Array>) {
            /* TODO: consider to read matrix_size as constexpr whenever possible */
            auto [rows, cols] = matrix_size(a);
            detail::sum_impl(result,a,rows,cols);
        }
        /* otherwise, dispatch if a is 1D array */
        else if constexpr (meta::is_array1d_v<Array>) {
            auto n = vector_size(a);
            detail::sum_impl(result,a,n);
        }
        return result;
    } // constexpr auto sum(const Array& a)
}

#endif // NMTOOLS_ARRAY_UTILITY_SUM_HPP