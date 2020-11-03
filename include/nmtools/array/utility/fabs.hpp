#ifndef NMTOOLS_ARRAY_UTILITY_FABS_HPP
#define NMTOOLS_ARRAY_UTILITY_FABS_HPP

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

namespace nmtools
{
    /**
     * @brief elementwise absolute value
     * 
     * @tparam Array matrix-like, vector-like, or arithmetic
     * @param a 
     * @return constexpr auto 
     */
    template <typename Array, typename=std::enable_if_t<!std::is_arithmetic_v<Array>>>
    constexpr auto fabs(const Array& a)
    {
        using traits::is_array1d_v;
        using traits::is_array2d_v;
        using std::is_arithmetic_v;

        static_assert(
            is_array1d_v<Array> ||
            is_array2d_v<Array> ||
            is_arithmetic_v<Array>,
            "unsupported type for fabs"
        );

        /* dispatch if Array is 1d or 2d */
        if constexpr (is_array2d_v<Array>) {
            auto ret = zeros_like(a);
            auto [rows,cols] = matrix_size(a);
            for (size_t i=0; i<rows; i++)
                for (size_t j=0; j<cols; j++)
                    at(ret,i,j) = fabs(at(a,i,j));
            return ret;
        }
        else if constexpr (is_array1d_v<Array>) {
            auto ret = zeros_like(a);
            auto n = vector_size(a);
            for (size_t i=0; i<n; i++)
                at(ret,i) = fabs(at(a,i));
            return ret;
        }
        /* dispatch if Array is arithmetic type */
        else {
            auto ret = std::fabs(a);
            return ret;
        }
    } // constexpr auto fabs(const Array& a)
}

#endif // NMTOOLS_ARRAY_UTILITY_FABS_HPP