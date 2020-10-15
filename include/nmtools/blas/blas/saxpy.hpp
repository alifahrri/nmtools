#ifndef NMTOOLS_BLAS_BLAS_SAXPY_HPP
#define NMTOOLS_BLAS_BLAS_SAXPY_HPP

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
     * @brief perform level-2 blas saxpy (ax + y)
     * 
     * @tparam Scalar arithmetic
     * @tparam X vector-like
     * @tparam Y vector-like
     * @param a scalar
     * @param x 
     * @param y 
     * @return constexpr auto 
     * @cite gene2013matrix_dot_saxpy
     */
    template <typename tag_t=size_assert_t, typename Scalar, typename X, typename Y>
    constexpr auto saxpy(const Scalar& a, const X& x, const Y& y, tag_t=tag_t{})
    {
        static_assert(
            std::is_arithmetic_v<Scalar>
            && traits::is_array1d_v<X>
            && traits::is_array1d_v<Y>
            /* TODO: helpful error message */
        );

        /* check if we should perform size assertion */
        /* TODO: consider to provide helper function for this check */
        if constexpr (is_assert_v<tag_t>) {
            /* check if both x and y is fixed size */
            constexpr auto is_fixed_size_vec_x = traits::is_fixed_size_vector_v<X>;
            constexpr auto is_fixed_size_vec_y = traits::is_fixed_size_vector_v<Y>;

            /* when both vector is fixed size, perform size assertion at compile time */
            if constexpr (is_fixed_size_vec_x && is_fixed_size_vec_y) {
                constexpr auto nx = fixed_vector_size_v<X>;
                constexpr auto ny = fixed_vector_size_v<Y>;
                static_assert(
                    nx==ny
                    /* TODO: helpful error message */
                );
            }
            /* size assertion at runtime */
            else {
                auto nx = vector_size(x);
                auto ny = vector_size(y);
                assert (nx==ny);
            }
        } // if constexpr (is_assert_v<tag_t>)

        /* placeholder for results */
        auto res = zeros_like(y);
        
        /* call add and mul for each elements */
        /* at this point mul(x[i], a) should dispatch scalar-scalar mul, 
            no allocation e.g. zeros_like called*/
        for (size_t i=0; i<size(y); i++)
            at(res,i) = add(at(y,i), mul(at(x,i), a));
        
        return res;
    } // constexpr auto saxpy(const Scalar& a, const X& x, const Y& y)

    /** @} */ // end group blas
}

#endif // NMTOOLS_BLAS_BLAS_SAXPY_HPP