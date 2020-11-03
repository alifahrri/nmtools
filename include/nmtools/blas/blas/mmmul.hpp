#ifndef NMTOOLS_BLAS_BLAS_MMMUL_HPP
#define NMTOOLS_BLAS_BLAS_MMMUL_HPP

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
     * @brief tag to resolve operation type of matrix-matrix multiplication
     * 
     */
    struct mmmul_select_resizeable_t;
} // namespace nmtools::blas

namespace nmtools::meta
{
    template <typename m1_t, typename m2_t>
    struct resolve_optype<void,blas::mmmul_select_resizeable_t,m1_t,m2_t>
    {
        static constexpr auto _get()
        {
            if constexpr (traits::is_resizeable2d_v<m1_t> && !traits::is_resizeable2d_v<m2_t>)
                return m1_t{};
            else if constexpr (!traits::is_resizeable2d_v<m1_t> && traits::is_resizeable2d_v<m2_t>)
                return m2_t{};
            else if constexpr (traits::is_resizeable2d_v<m1_t> && traits::is_resizeable2d_v<m2_t>)
                return m1_t{};
            else if constexpr (traits::is_resizeable_v<m1_t> && !traits::is_resizeable_v<m2_t>)
                return m1_t{};
            else if constexpr (!traits::is_resizeable_v<m1_t> && traits::is_resizeable_v<m2_t>)
                return m2_t{};
            else if constexpr (traits::is_resizeable_v<m1_t> && traits::is_resizeable_v<m2_t>)
                return m1_t{};
            else if constexpr (!traits::is_resizeable_v<m1_t> && !traits::is_resizeable_v<m2_t>)
                return detail::fail_t{};
        } // _get()
        using type = traits::remove_cvref_t<detail::fail_to_void_t<decltype(_get())>>;
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
        template <typename common_t>
        constexpr auto mmmul_impl(auto& mat, const auto& A, const auto &B, auto row_a, auto col_a, auto col_b) {
            for (int i=0; i<row_a; i++) {
                for (int j=0; j<col_b; j++) {
                    auto sum = static_cast<common_t>(0);
                    for (int k=0; k<col_a; k++)
                        sum += at(A,i,k) * at(B,k,j);
                    at(mat,i,j) = sum;
                }
            }
        } // mmmul_impl
    } // namespace detail

    /**
     * @brief matrix-matrix multiplication A*B
     * 
     * @tparam M1 matrix-like
     * @tparam M2 matrix-like
     * @param A 
     * @param B 
     * @return constexpr auto 
     */
    template <typename M1, typename M2>
    constexpr auto mmmul(const M1& A, const M2& B)
    {
        static_assert(
            traits::is_matrix_like_v<M1> &&
            traits::is_matrix_like_v<M2>,
            "unsupported type M1 & M2 of A & B for mmmul"
        );

        /* deduce row type and element type */
        using m1_t = meta::transform_bounded_array_t<M1>;
        using m2_t = meta::transform_bounded_array_t<M2>;
        using a_t = meta::get_matrix_value_type_t<m1_t>;
        using b_t = meta::get_matrix_value_type_t<m2_t>;
        using common_t = std::common_type_t<a_t,b_t>;

        using detail::mmmul_impl;

        constexpr auto is_fixed_size_mat_A = traits::is_fixed_size_matrix_v<m1_t>;
        constexpr auto is_fixed_size_mat_B = traits::is_fixed_size_matrix_v<m2_t>;

        /* dispatch compile-time version 
            both are fixed size matrix, the resulting shape will be known at compile time */
        if constexpr (is_fixed_size_mat_A && is_fixed_size_mat_B) {
            constexpr auto ashape = fixed_matrix_size_v<m1_t>;
            constexpr auto row_a = get<0>(ashape);
            constexpr auto col_a = get<1>(ashape);

            constexpr auto bshape = fixed_matrix_size_v<m2_t>;
            constexpr auto row_b = get<0>(bshape);
            constexpr auto col_b = get<1>(bshape);

            static_assert (col_a==row_b && row_a==col_b);

            /* prepare placeholder for the resulting matrix */
            auto mat = zeros<m1_t,row_a,col_b>();
            mmmul_impl<common_t>(mat,A,B,row_a,col_a,col_b);
            return mat;
        }
        /* dispatch runtime version
            one of the matrix are dynamic, the resulting shape will be known at runtime time */
        else {
            auto [row_a, col_a] = matrix_size(A);
            auto [row_b, col_b] = matrix_size(B);

            assert (col_a == row_b);
            assert (row_a == col_b);

            /* select resizeable mat over fixed ones for return type */
            using return_t = meta::resolve_optype_t<mmmul_select_resizeable_t,m1_t,m2_t>;
            static_assert( !std::is_same_v<return_t,void>
                , "can't resolve return type for mmadd"
            );
            auto mat = zeros<return_t>(row_a,col_b);
            mmmul_impl<common_t>(mat,A,B,row_a,col_a,col_b);
            return mat;
        }
    } // constexpr auto mmmul(const M1& A, const M2& B)

    /** @} */ // end group blas
}

#endif // NMTOOLS_BLAS_BLAS_MMMUL_HPP