#ifndef NMTOOLS_BLAS_BLAS_NORM_HPP
#define NMTOOLS_BLAS_BLAS_NORM_HPP

#include "nmtools/array/utility/max.hpp"
#include "nmtools/array/utility/fabs.hpp"
#include "nmtools/array/utility/sum.hpp"
#include "nmtools/array/utility/sumsq.hpp"
#include "nmtools/array/utility/col_sum.hpp"
#include "nmtools/array/utility/row_sum.hpp"

#include "nmtools/blas/blas/dot.hpp"

namespace nmtools::blas
{
    /**
     * @ingroup blas
     * @{
     */
    
    /**
     * @brief enum for norm type
     * 
     */
    enum struct norm_t {
        /**
         * @brief infinity norm
         * 
         */
        infinity_norm=3,
        /**
         * @brief frobenius norm
         * 
         */
        frobenius_norm=4,
    };

    /**
     * @brief computer P-norm of vector x
     * 
     * @tparam P norm kind: 2, 1, or inf_norm
     * @tparam Vector vector-like
     * @param x vector which its norm is to be computed
     * @return constexpr auto 
     */
    template <auto P, typename Vector>
    constexpr auto vector_norm(const Vector& x)
    {
        using norm_type = decltype(P);
        if constexpr (std::is_same_v<norm_type,norm_t>) {
            /* NOTE: need to be nested so operator== 
                will only evaluated when possible (P is norm_t) */
            if constexpr (P==norm_t::infinity_norm)
                return max(fabs(x));
        }
        else if constexpr (P==2)
            return sqrt(dot(x,x));
        else if constexpr (P==1)
            return sum(fabs(x));
    } // constexpr auto vector_norm
    
    /**
     * @brief overloaded version of vector_norm, where p is runtime value
     * 
     * @tparam Vector vector-like
     * @tparam size_type type of p
     * @param x vector which its norm is to be computed
     * @param p norm kind: 2, 1, or norm_t
     * @return constexpr auto 
     */
    template <typename Vector, typename norm_type>
    constexpr auto vector_norm(const Vector& x, norm_type p)
    {
        if constexpr (std::is_same_v<norm_type,norm_t>) {
            /* NOTE: need to be nested so operator== 
                will only evaluated when possible (P is norm_t) */
            if (p==norm_t::infinity_norm)
                return max(fabs(x));
        }
        else {
            if (p==2)
                return sqrt(dot(x,x));
            else if (p==1)
                return sum(fabs(x));
        }
    } // constexpr auto vector_norm

    template <auto P, typename Matrix>
    constexpr auto matrix_norm(const Matrix& M)
    {
        using norm_type = decltype(P);
        if constexpr (std::is_same_v<norm_type,norm_t>) {
            constexpr auto is_inf = P == norm_t::infinity_norm;
            constexpr auto is_fro = P == norm_t::frobenius_norm;
            static_assert(is_inf || is_fro);
            if constexpr (is_inf)
                return max(col_sum(fabs(M)));
            else if constexpr (is_fro)
                return sqrt(sumsq(M));
        }
        else {
            static_assert(P==1, "only support norm-1 for now");
            return max(row_sum(fabs(M)));
        }
    } // constexpr auto matrix_norm

    template <typename Matrix, typename norm_type>
    constexpr auto matrix_norm(const Matrix& M, norm_type p)
    {
        if constexpr (std::is_same_v<norm_type,norm_t>) {
            auto is_inf = p == norm_t::infinity_norm;
            auto is_fro = p == norm_t::frobenius_norm;
            // assert(is_inf || is_fro);
            if (is_inf)
                return max(col_sum(fabs(M)));
            else if (is_fro)
                return sqrt(sumsq(M));
        }
        else {
            // assert(p==1, "only support norm-1 for now");
            return max(row_sum(fabs(M)));
        }
    } // constexpr auto matrix_norm

    /**
     * @brief compute matrix/vector p-norm
     * 
     * @tparam P norm kind
     * @tparam Array matrix/vector like
     * @param x matrix/vector which it norm is to be computed
     * @return constexpr auto 
     */
    template <auto P, typename Array>
    constexpr auto norm(const Array& x)
    {
        static_assert(
            traits::is_array1d_v<Array>
            || traits::is_array2d_v<Array>
            /* TODO: helpful error message here */
        );
        if constexpr (traits::is_array1d_v<Array>)
            return vector_norm<P>(x);
        else return matrix_norm<P>(x);
    } // constexpr auto norm

    /**
     * @brief overloaded version of norm, with p as runtime value
     * 
     * @tparam Array 
     * @tparam size_type 
     * @param x 
     * @param p 
     * @return constexpr auto 
     */
    template <typename Array, typename size_type>
    constexpr auto norm(const Array& x, size_type p)
    {
        static_assert(
            traits::is_array1d_v<Array>
            || traits::is_array2d_v<Array>
            /* TODO: helpful error message here */
        );
        if constexpr (traits::is_array1d_v<Array>)
            return vector_norm(x,p);
        else return matrix_norm(x,p);
    } // constexpr auto norm

    /** @} */ // end group blas
}
#endif // NMTOOLS_BLAS_BLAS_NORM_HPP