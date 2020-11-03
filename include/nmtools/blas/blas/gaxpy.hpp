#ifndef NMTOOLS_BLAS_BLAS_GAXPY_HPP
#define NMTOOLS_BLAS_BLAS_GAXPY_HPP

#include "nmtools/blas/blas/mul.hpp"
#include "nmtools/blas/blas/add.hpp"
#include "nmtools/blas/blas/tag.hpp"

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include <cmath>
#include <cassert>
#include <type_traits>

namespace nmtools::blas
{
    /* make sure use common tag namespace */
    using ::nmtools::tag::is_tag_enabled_v;
    using ::nmtools::tag::size_assert_t;
    using ::nmtools::tag::is_assert_v;

    /**
     * @ingroup blas
     * @{
     */

    /**
     * @brief perform level-3 blas generalized saxpy
     * 
     * @tparam tag_t=size_assert_t 
     * @tparam Matrix 
     * @tparam X 
     * @tparam Y 
     * @param A 
     * @param x 
     * @param y 
     * @return constexpr auto 
     * @cite gene2013matrix_mvmul_gaxpy
     */
    template <typename tag_t=size_assert_t, typename Matrix, typename X, typename Y>
    constexpr auto gaxpy(const Matrix& A, const X& x, const Y& y)
    {
        static_assert(
            meta::is_array2d_v<Matrix>
            && meta::is_array1d_v<X>
            && meta::is_array1d_v<Y>
            /* TODO: helpful error message */
        );

        /* check if we should perform size assertion */
        /* TODO: consider to provide helper function for this check */
        if constexpr (is_assert_v<tag_t>) {
            /* check if all array-like is fixed-size one */
            constexpr auto is_fixed_A = meta::is_fixed_size_matrix_v<Matrix>;
            constexpr auto is_fixed_x = meta::is_fixed_size_vector_v<X>;
            constexpr auto is_fixed_y = meta::is_fixed_size_vector_v<Y>;

            /* perform size assertion at compile-time if all array-like has fixed size */
            if constexpr (is_fixed_A && is_fixed_x && is_fixed_y) {
                /* get pair first, then unpack row & col */
                constexpr auto nA = fixed_matrix_size_v<Matrix>;
                /* assuming col-major */
                constexpr auto row_A = get<0>(nA);
                constexpr auto col_A = get<1>(nA);
                /* vector size */
                constexpr auto nx = fixed_vector_size_v<X>;
                constexpr auto ny = fixed_vector_size_v<Y>;
                static_assert(
                    (nx == col_A)
                    && (ny == row_A)
                    /* TODO: helpful error message */
                );
            }
            /* perform check at runtime otherwise */
            else {
                auto [row_A, col_A] = matrix_size(A);
                auto nx = vector_size(x);
                auto ny = vector_size(y);
                assert (
                    (nx == col_A)
                    && (ny == row_A)
                    /* TODO: helpful error message */
                );
            }
        } // if constexpr (is_assert_v<tag_t>)

        /* placeholder for results */
        /* use clone instead of zeros_like to allow update 
            instead of fresh-compute */
        auto res = clone(y);

        for (size_t i=0; i<size(y); i++)
            for (size_t j=0; j<size(x); j++)
                at(res, i) = add(at(res,i), mul(at(x,j),at(A,i,j)));
        
        return res;

    } // constexpr auto gaxpy(const Matrix& A, const X& x, const Y& y)

    /** @} */ // end group blas
}

#endif // NMTOOLS_BLAS_BLAS_GAXPY_HPP