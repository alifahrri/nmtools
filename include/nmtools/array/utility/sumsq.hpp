#ifndef NMTOOLS_ARRAY_UTILITY_SUMSQ_HPP
#define NMTOOLS_ARRAY_UTILITY_SUMSQ_HPP

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
}

#endif // NMTOOLS_ARRAY_UTILITY_SUMSQ_HPP