#ifndef NMTOOLS_ARRAY_UTILITY_ROW_HPP
#define NMTOOLS_ARRAY_UTILITY_ROW_HPP

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
     * @brief given marix M, get its r-th row.
     * 
     * @tparam Matrix matrix-like
     * @param M matrix in which its row to be taken.
     * @param r row.
     * @return constexpr auto 
     */
    template <typename Matrix>
    constexpr auto row(const Matrix& M, size_t r)
    {
        static_assert(
            traits::is_array2d_v<Matrix>
            /* TODO: helpful error message here */
        );
        // assuming possibly nested matrix or its
        // at operator support single indexing
        return at(M,r);
    } // constexpr auto row(const Matrix, size_type r)

    /**
     * @brief specialization of row function for nested raw array.
     * 
     * @tparam T element type of raw array
     * @tparam M size of array at first axis, automatically deduced
     * @tparam N size of array at second axis, automatically deduced
     * @param r row
     * @return constexpr auto 
     */
    template <typename T, size_t M, size_t N>
    constexpr auto row(const T(&t)[M][N], size_t r)
    {
        using array_t = std::array<T,N>;
        using index_t = std::make_index_sequence<N>;
        return detail::make_array<array_t>(t[r],index_t{});
    } // constexpr auto row

    /** @} */ // end group utility
} // namespace nmtools

#endif // NMTOOLS_ARRAY_UTILITY_ROW_HPP