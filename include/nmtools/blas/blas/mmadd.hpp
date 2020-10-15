#ifndef NMTOOLS_BLAS_BLAS_MMADD_HPP
#define NMTOOLS_BLAS_BLAS_MMADD_HPP

/* common tag for preconditions, e.g. size assertion */
#include "nmtools/utility/tag.hpp"
/* common array (as in matrix/vector) utility */
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/shape.hpp"
#include "nmtools/array/utility/zeros.hpp"

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
    
    namespace detail
    {
        constexpr auto mmadd_impl(auto &mat, const auto& A, const auto &B, auto row_a, auto row_b){
            for (int i=0; i<row_a; i++)
                for (int j=0; j<row_b; j++)
                    at(mat,i,j) = at(A,i,j) + at(B,i,j);
        } // mmadd_impl
    } // namespace detail

    /**
     * @brief matrix matrix additon A+B
     * 
     * @tparam M1 matrix-like
     * @tparam M2 matrix-like
     * @param A lhs
     * @param B rhs
     * @return constexpr auto 
     */
    template <typename M1, typename M2>
    constexpr auto mmadd(const M1& A, const M2& B)
    {
        static_assert(
            traits::is_matrix_like_v<M1> &&
            traits::is_matrix_like_v<M2>,
            "unsupported type M1 & M2 of A & B for mmadd"
        );

        using meta::transform_bounded_array_t;
        using m1_t = transform_bounded_array_t<M1>;
        using m2_t = transform_bounded_array_t<M2>;
        using meta::get_matrix_value_type_t;

        using detail::mmadd_impl;

        /* check if these matrices are fixed-size */
        constexpr auto is_fixed_size_mat_A = traits::is_fixed_size_matrix_v<m1_t>;
        constexpr auto is_fixed_size_mat_B = traits::is_fixed_size_matrix_v<m2_t>;

        /* TODO: provide convinient meta-function to get element type of a matrix */
        /* element type of matrix A */
        using a_t = get_matrix_value_type_t<m1_t>;
        /* element type of matrix B */
        using b_t = get_matrix_value_type_t<m2_t>;
        /* get common type of matrix A & B */
        using common_t = std::common_type_t<a_t,b_t>;

        /* dispatch compile-time version 
            both are fixed size matrix, the resulting shape will be known at compile time */
        if constexpr (is_fixed_size_mat_A && is_fixed_size_mat_B) {
            /* deduce row type and element type */
            constexpr auto shape_a = matrix_size(A);
            constexpr auto shape_b = matrix_size(B);
            constexpr auto row_a = get<0>(shape_a);
            constexpr auto row_b = get<0>(shape_b);
            constexpr auto col_a = get<1>(shape_a);
            constexpr auto col_b = get<1>(shape_b);

            static_assert(row_a == row_b);
            static_assert(col_a == col_b);

            /* prepare placeholder for the resulting matrix */
            auto mat = zeros<m1_t,row_a,col_b>();
            mmadd_impl(mat,A,B,row_a,col_b);
            return mat;
        }
        /* dispatch runtime version
            one of the matrix are dynamic, the resulting shape will be known at runtime time */
        else {
            auto [row_a, col_a] = matrix_size(A);
            auto [row_b, col_b] = matrix_size(B);

            /* addition requires matrix to be in the same shape */
            assert (col_a == col_b);
            assert (row_a == row_b);

            /* make sure one of the matrix type is resizeable */
            static_assert(
                traits::is_resizeable_v<M1> ||
                traits::is_resizeable_v<M2>
            );
            /* select resizeable mat over fixed ones for return type */
            using return_t = meta::select_resizeable_mat_t<m1_t,m2_t>;
            auto mat = zeros<return_t>(row_a,col_a);
            mmadd_impl(mat,A,B,row_a,col_b);
            return mat;
        }
    } // constexpr auto mmadd(const M1& A, const M2& B)

    /** @} */ // end group blas
}

#endif // NMTOOLS_BLAS_BLAS_MMADD_HPP