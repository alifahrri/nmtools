#ifndef NMTOOLS_ARRAY_UTILITY_IDENTITY_HPP
#define NMTOOLS_ARRAY_UTILITY_IDENTITY_HPP

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
     * @brief make identity matrix
     * 
     * @tparam Array matrix-like
     * @param a square matrix
     * @return constexpr auto identity matrix
     */
    template <typename Array>
    constexpr auto identity(const Array& a)
    {
        using meta::is_array2d_v;

        static_assert(
            is_array2d_v<Array>,
            "only support 2D array"
        );

        /* remove cv-ref to make sure we get non const */
        using element_t = meta::get_matrix_value_type_t<Array>;

        auto ret = zeros_like(a);
        auto [n,m] = matrix_size(a);
        assert (m==n);

        for (size_t i=0; i<m; i++)
            at(ret,i,i) = static_cast<element_t>(1);
        return ret;
    } // constexpr auto identity(const Array& a)
}

#endif // NMTOOLS_ARRAY_UTILITY_IDENTITY_HPP