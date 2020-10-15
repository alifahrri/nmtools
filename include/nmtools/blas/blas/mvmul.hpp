#ifndef NMTOOLS_BLAS_BLAS_MVMUL_HPP
#define NMTOOLS_BLAS_BLAS_MVMUL_HPP

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
    namespace detail
    {
        template <typename common_t>
        constexpr auto mvmul_impl(auto& ret, const auto& m, const auto& v, auto mrows, auto mcols)
        {
            for (size_t i=0; i<mrows; i++)
            {
                /* NOTE: can't use dot for now 
                    since at only support returning reference for accessing row
                    while some matrix type returning value with reference_wrapper
                */
                /* TODO: use dot product */
                // at(ret,i) = dot(at(m,i),v);

                auto sum = static_cast<common_t>(0);
                for (size_t j=0; j<mcols; j++)
                    sum += at(m,i,j) * at(v,j);
                
                at(ret,i) = sum;
            }
        } // mvmul_impl
    } // namespace detail

    /**
     * @ingroup blas
     * @brief matrix-vector multiplication
     * 
     * @tparam M matrix-like
     * @tparam V vector-like
     * @param m left-hand-side matrix
     * @param v right-hand-side vector
     * @return constexpr auto vector-like
     * @cite gene2013matrix_mvmul_gaxpy
     */
    template <typename M, typename V>
    constexpr auto mvmul(const M& m, const V& v)
    {
        static_assert(
            traits::is_array2d_v<M>
            && traits::is_array1d_v<V>,
            "unsupported type for mvmul"
        );

        /* get row type of matrix M, element type of M & v, and common type */
        using m_t = meta::transform_bounded_array_t<M>;
        using v_t = meta::transform_bounded_array_t<V>;
        using me_t = meta::get_matrix_value_type_t<M>;
        using ve_t = meta::get_vector_value_type_t<V>;
        using common_t = std::common_type_t<me_t,ve_t>;
        using return_t = meta::transform_bounded_array_t<V>;

        using detail::mvmul_impl;

        /* deduce resulting size of matrix */
        constexpr auto is_fixed_size_M = traits::is_fixed_size_matrix_v<m_t>;
        constexpr auto is_fixed_size_V = traits::is_fixed_size_vector_v<v_t>;

        /* dispatch compile-time version when both are fixed size,
            the resulting shape will also be known at compile time */
        if constexpr (is_fixed_size_M && is_fixed_size_V) {
            constexpr auto shape = fixed_matrix_size_v<m_t>;
            constexpr auto mrows = get<0>(shape);
            constexpr auto mcols = get<1>(shape);
            constexpr auto vrows = fixed_vector_size_v<v_t>;
            static_assert(mcols==vrows);

            /* prepare placeholder for the resulting matrix */
            auto ret = zeros<return_t,mrows>();
            mvmul_impl<common_t>(ret,m,v,mrows,mcols);
            return ret;
        }
        /* dispatch runtime version when one of the matrix are dynamic,
            the resulting shape will only be known at runtime time */
        else {
            auto [mrows, mcols] = matrix_size(m);
            auto vrows = vector_size(v);

            assert (mcols==vrows);

            /* make sure one of the matrix type is resizeable */
            static_assert(
                traits::is_resizeable_v<V>
                /* TODO: helpful error message here */
            );
            auto ret = zeros<return_t>(mrows);
            mvmul_impl<common_t>(ret,m,v,mrows,mcols);
            return ret;
        }
    } // constexpr auto mvmul(const M& m, const V& v)
} // namespace nmtools::blas

#endif // NMTOOLS_BLAS_BLAS_MVMUL_HPP