#ifndef NMTOOLS_BLAS_ADD_HPP
#define NMTOOLS_BLAS_ADD_HPP

#include "nmtools/blas/blas/mmadd.hpp"
#include "nmtools/blas/blas/vvadd.hpp"
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
     * @brief perform lhs + rhs.
     * Dispatch one of the following expression (ordered by priority):
     * (1) lhs + rhs;
     * (2) vvadd(lhs,rhs);
     * (3) mmadd(lhs,rhs);
     * 
     * @tparam A vector-like or matrix-like or scalar
     * @tparam B vector-like or matrix-like or scalar
     * @param lhs 
     * @param rhs 
     * @return constexpr auto 
     */
    template <typename A, typename B>
    constexpr auto add(const A& lhs, const B& rhs)
    {
        using traits::is_additive_v;

        /* get operation tag */
        using op_t = tag::get_t<A,B>;

        static_assert(
            is_additive_v<A,B>
            || (
                !std::is_same_v<op_t,void> 
                && !std::is_same_v<op_t,tag::vector_scalar_t>
                && !std::is_same_v<op_t,tag::matrix_scalar_t>
                && !std::is_same_v<op_t,tag::matrix_vector_t>
            )
            , "unsupported type(s) for add(lhs,rhs)"
        );

        /* dispatch if A & B is additive */
        if constexpr (is_additive_v<A,B>)
            return lhs + rhs;
        /* dispatch vector-vector addition */
        else if constexpr (std::is_same_v<op_t,tag::vector_vector_t>)
            return vvadd(lhs, rhs);
        /* dispatch matrix-matrix addition */
        else if constexpr (std::is_same_v<op_t,tag::matrix_matrix_t>)
            return mmadd(lhs, rhs);
        else {
            // TODO: compile error here
        }
    } // constexpr auto add(const A& lhs, const B& rhs)
}

#endif // NMTOOLS_BLAS_ADD_HPP