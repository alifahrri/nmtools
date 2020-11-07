#ifndef NMTOOLS_ARRAY_UTILITY_SHAPE_HPP
#define NMTOOLS_ARRAY_UTILITY_SHAPE_HPP

#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"

/* TODO: should we include array and std::array specialization here? */
#include <array>
#include <tuple>
#include <type_traits>

namespace nmtools
{
    /** @addtogroup utility
    * @ingroup array
    * Collections of utility functions for array-like objects
    * @{
    */

    using std::size;
    using std::get;

    /**
     * @brief generic function to get size of dynamic-matrix, assuming nested vector.
     * May be specialized for custom dynamic-matrix type.
     * 
     * @tparam Matrix matrix-like
     * @param M matrix to check
     * @return std::pair<size_t,size_t> row-col pair
     */
    template <typename Matrix>
    constexpr auto matrix_size(const Matrix& M) -> std::enable_if_t<meta::is_nested_array2d_v<Matrix>,std::pair<size_t,size_t>>
    {
        static_assert(
            meta::is_array2d_v<Matrix>
            /* TODO: meaningful error message */
        );
        /* TODO: check all size for each rows. 
        Nested vector container may have different size at axis 0 */
        return std::make_pair(size(M), size(at(M,0)));
    } // std::pair<size_t,size_t> matrix_size(const Matrix& M)

    /**
     * @brief generic function to get size of dynamic-vector (as in math vector, not container).
     * May be specialized for custom dynamic-matrix type.
     * 
     * @tparam Vector vector-like
     * @param v vector to check
     * @return size_t 
     */
    template <typename Vector>
    constexpr auto vector_size(const Vector& v)
        -> std::enable_if_t<
            std::is_same_v<std::void_t<decltype(size(v))>,void>
            && !meta::is_fixed_size_vector_v<Vector>, size_t >
    {
        static_assert(
            meta::is_array1d_v<Vector>
            /* TODO: meaningful error message */
        );

        return size(v);
    } // size_t vector_size(const Vector& v)

    template <typename Vector>
    constexpr auto vector_size(const Vector& v)
        -> std::enable_if_t< meta::is_fixed_size_vector_v<Vector>, size_t>
    {
        return meta::fixed_vector_size_v<Vector>;
    }

    /** @} */ // end group utility
} // namespace nmtools

#endif // NMTOOLS_ARRAY_UTILITY_SHAPE_HPP