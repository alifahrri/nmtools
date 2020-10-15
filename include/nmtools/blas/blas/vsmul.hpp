#ifndef NMTOOLS_BLAS_BLAS_VSMUL_HPP
#define NMTOOLS_BLAS_BLAS_VSMUL_HPP

/* common tag for preconditions, e.g. size assertion */
#include "nmtools/utility/tag.hpp"
/* common array (as in matrix/vector) utility */
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/clone.hpp"
#include "nmtools/array/utility/shape.hpp"

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

    /**
     * @brief vector-scalar multiplication
     * 
     * @tparam V vector-like 
     * @tparam S scalar 
     * @param v left-hand-side vector
     * @param s right-hand-side scalar
     * @return constexpr auto vector-like
     */
    template <typename V, typename S>
    constexpr auto vsmul(const V& v, const S& s)
    {
        static_assert(
            traits::is_array1d_v<V>
            && std::is_arithmetic_v<S>
            /* TODO: helpful error message here */
        );
        auto ret = clone(v);
        for (size_t i=0; i<size(ret); i++)
            at(ret,i) = at(ret,i) * s;
        return ret;
    } // constexpr auto vsmul(const V& v, const S& s)

    /** @} */ // end group blas
}

#endif // NMTOOLS_BLAS_BLAS_VSMUL_HPP