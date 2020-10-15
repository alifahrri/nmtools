#ifndef NMTOOLS_BLAS_MUL_HPP
#define NMTOOLS_BLAS_MUL_HPP

#include "nmtools/blas/blas/vsmul.hpp"
#include "nmtools/blas/blas/msmul.hpp"
#include "nmtools/blas/blas/mvmul.hpp"
#include "nmtools/blas/blas/mmmul.hpp"
#include "nmtools/blas/blas/tag.hpp"

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include <cmath>
#include <cassert>
#include <type_traits>

namespace nmtools::blas
{
    /**
     * @ingroup blas
     * @brief perform lhs * rhs.
     * Dispatch one of the following (ordered by priority):
     * (1) lhs*rhs;
     * (2) mmmul(lhs,rhs);
     * (3) mvmul(lhs,rhs);
     * (4) vsmul(lhs,rhs);
     * 
     * @tparam A matrix-like or vector-like or A*B is multiplicative
     * @tparam B matrix-like or vector-like or arithmetic type or A*B is multiplicative
     * @param lhs 
     * @param rhs 
     * @return constexpr auto 
     */
    template <typename A, typename B>
    constexpr auto mul(const A& lhs, const B& rhs)
    {
        using traits::is_multiplicative_v;

        /* get operation tag */
        using op_t = tag::get_t<A,B>;

        static_assert(
            is_multiplicative_v<A,B>
            || (
                !std::is_same_v<op_t,void> 
                && !std::is_same_v<op_t,tag::vector_vector_t>
            )
            , "unsupported type(s) for mul(lhs,rhs)"
        );

        /* dispatch if A & B is multiplicative */
        if constexpr (is_multiplicative_v<A,B>)
            return lhs * rhs;
        /* dispatch matrix-matrix multiplication */
        else if constexpr (std::is_same_v<op_t,tag::matrix_matrix_t>)
            return mmmul(lhs, rhs);
        /* dispatch matrix-vector multiplication */
        else if constexpr (std::is_same_v<op_t,tag::matrix_vector_t>)
            return mvmul(lhs, rhs);
        /* dispatch matrix-scalar multiplication */
        else if constexpr (std::is_same_v<op_t,tag::matrix_scalar_t>)
            return msmul(lhs, rhs);
        /* dispatch vector-scalar multiplication */
        else if constexpr (std::is_same_v<op_t,tag::vector_scalar_t>)
            return vsmul(lhs, rhs);
        /* dispatch scalar-scalar multiplication, should be multiplicative though */
        else if constexpr (std::is_same_v<op_t,tag::scalar_scalar_t>)
            return lhs * rhs;
        else {
            // vector-vector
            // TODO: compile error here
        }
    } // constexpr auto mul(const A& lhs, const B& rhs)
}

#endif // NMTOOLS_BLAS_MUL_HPP