#ifndef NMTOOLS_BLAS_BLAS_MMADD_HPP
#define NMTOOLS_BLAS_BLAS_MMADD_HPP

/* common tag for preconditions, e.g. size assertion */
#include "nmtools/utility/tag.hpp"
/* common array (as in matrix/vector) utility */
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/utility/zeros.hpp"

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include <type_traits>
#include <cmath>
#include <cassert>

namespace nmtools::blas
{
    /**
     * @brief tag to resolve optype
     * 
     */
    struct mmadd_select_resizeable_t;
} // namespace nmtools::blas

namespace nmtools::meta
{
    template <typename m1_t, typename m2_t>
    struct resolve_optype<void,blas::mmadd_select_resizeable_t,m1_t,m2_t>
    {
        /**
         * @brief helper static fn to select resizeable matrix.
         *
         * Implemented as helper function instead of clunky enable_if_t to
         * utilize constexpr-if.
         * 
         * @return constexpr auto 
         */
        static constexpr auto _get()
        {
            if constexpr (meta::is_resizeable2d_v<m1_t> && !meta::is_resizeable2d_v<m2_t>)
                return m1_t{};
            else if constexpr (!meta::is_resizeable2d_v<m1_t> && meta::is_resizeable2d_v<m2_t>)
                return m2_t{};
            else if constexpr (meta::is_resizeable2d_v<m1_t> && meta::is_resizeable2d_v<m2_t>)
                return m1_t{};
            else if constexpr (meta::is_resizeable_v<m1_t> && !meta::is_resizeable_v<m2_t>)
                return m1_t{};
            else if constexpr (!meta::is_resizeable_v<m1_t> && meta::is_resizeable_v<m2_t>)
                return m2_t{};
            else if constexpr (meta::is_resizeable_v<m1_t> && meta::is_resizeable_v<m2_t>)
                return m1_t{};
            else if constexpr (!meta::is_resizeable_v<m1_t> && !meta::is_resizeable_v<m2_t>)
                return detail::fail_t{};
        } // _get()
        using type = meta::remove_cvref_t<detail::fail_to_void_t<decltype(_get())>>;
    };
} // namespace nmtools::meta

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
            meta::is_matrix_like_v<M1> &&
            meta::is_matrix_like_v<M2>,
            "unsupported type M1 & M2 of A & B for mmadd"
        );

        using meta::transform_bounded_array_t;
        using m1_t = transform_bounded_array_t<M1>;
        using m2_t = transform_bounded_array_t<M2>;
        using meta::get_matrix_value_type_t;

        using detail::mmadd_impl;

        /* check if these matrices are fixed-size */
        constexpr auto is_fixed_size_mat_A = meta::is_fixed_size_matrix_v<m1_t>;
        constexpr auto is_fixed_size_mat_B = meta::is_fixed_size_matrix_v<m2_t>;

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
            constexpr auto shape_a = meta::fixed_matrix_size_v<M1>;
            constexpr auto shape_b = meta::fixed_matrix_size_v<M2>;
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

            /* select resizeable mat over fixed ones for return type */
            using return_t = meta::resolve_optype_t<mmadd_select_resizeable_t,m1_t,m2_t>;
            static_assert( !std::is_same_v<return_t,void>
                , "can't resolve return type for mmadd"
            );
            auto mat = zeros<return_t>(row_a,col_a);
            mmadd_impl(mat,A,B,row_a,col_b);
            return mat;
        }
    } // constexpr auto mmadd(const M1& A, const M2& B)

    /** @} */ // end group blas
}

#endif // NMTOOLS_BLAS_BLAS_MMADD_HPP