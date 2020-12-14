#ifndef NMTOOLS_BLAS_BLAS_OUTER_HPP
#define NMTOOLS_BLAS_BLAS_OUTER_HPP

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

namespace nmtools::blas
{
    /**
     * @ingroup blas
     * @{
     */

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
        template <typename return_t, typename a_t, typename b_t, typename rows_t, typename cols_t>
        constexpr auto outer_impl(return_t& matrix, const a_t& v1, const b_t& v2, rows_t m, cols_t n)
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
            meta::is_array1d_v<V1>
            && meta::is_array1d_v<V2>
            /* TODO: helpful error message here */
        );

        using detail::outer_impl;
        using v1_t = meta::transform_bounded_array_t<V1>;
        using v2_t = meta::transform_bounded_array_t<V2>;

        /* first, let's deduce the resulting type */
        using matrix_t = meta::make_outer_matrix_t<v1_t,v2_t>;

        static_assert(
            meta::is_array2d_v<matrix_t>
            /* TODO: helpful error message here */
        );

        constexpr auto is_fixed_size_matrix = meta::is_fixed_size_matrix_v<matrix_t>;

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

    /** @} */ // end group blas
} // namespace nmtools::blas

#endif // NMTOOLS_BLAS_BLAS_OUTER_HPP