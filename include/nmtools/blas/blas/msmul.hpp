#ifndef NMTOOLS_BLAS_BLAS_MSMUL_HPP
#define NMTOOLS_BLAS_BLAS_MSMUL_HPP

/* common tag for preconditions, e.g. size assertion */
#include "nmtools/utility/tag.hpp"
/* common array (as in matrix/vector) utility */
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/utility/zeros_like.hpp"

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
        constexpr auto msmul_impl(auto& ret, const auto& m, const auto& s, auto rows, auto cols)
        {
            for (size_t i=0; i<rows; i++) {
                /* NOTE: cant use vsmul for now since
                    at requires to be returning reference
                    while some matrix type returning value with
                    reference wrapper */
                /* TODO: use vsmul instead */
                // at(ret,i) = vsmul(at(m,i),s);
                for (size_t j=0; j<cols; j++)
                    at(ret,i,j) = at(m,i,j) * s;
            }
        } // msmul_impl
    } // namespace detail

    /**
     * @brief matrix-scalar multiplication
     * 
     * @tparam M matrix-like
     * @tparam S scalar 
     * @param m left-hand-side matrix
     * @param s right-hand-side scalar
     * @return constexpr auto matrix-like
     */
    template <typename M, typename S>
    constexpr auto msmul(const M& m, const S& s)
    {
        static_assert(
            meta::is_array2d_v<M>
            && std::is_arithmetic_v<S>
            /* TODO: helpful error message here */
        );
        auto ret = zeros_like(m);
        auto [rows, cols] = matrix_size(m);

        using detail::msmul_impl;
        msmul_impl(ret,m,s,rows,cols);

        return ret;
    } // constexpr auto msmul(const M& m, const S& s)

    /** @} */ // end group blas
}

#endif // NMTOOLS_BLAS_BLAS_MSMUL_HPP