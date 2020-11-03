#ifndef NMTOOLS_ARRAY_UTILITY_TRANSPOSE_HPP
#define NMTOOLS_ARRAY_UTILITY_TRANSPOSE_HPP

/* common tag for preconditions, e.g. size assertion */
#include "nmtools/utility/tag.hpp"
/* common array (as in matrix/vector) utility */
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/zeros.hpp"
#include "nmtools/array/shape.hpp"

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include <type_traits>
#include <cmath>
#include <cassert>

namespace nmtools
{
    /**
     * @brief compute matrix transpose
     * 
     * @tparam Array matrix-like
     * @param a matrix to be transposed
     * @return constexpr auto 
     */
    template <typename Array>
    constexpr auto transpose(const Array& a)
    {
        static_assert(
            meta::is_array2d_v<Array>,
            "transpose only support 2D array for now"
        );

        using meta::get_container_value_type_t;
        using meta::has_tuple_size_v;

        using std::get;
        using meta::remove_cvref_t;
        using meta::transform_bounded_array_t;
        using return_t = transform_bounded_array_t<remove_cvref_t<Array>>;

        constexpr auto is_fixed_size = meta::is_fixed_size_matrix_v<return_t>;

        /* common loop implementation for both fixed and dynamic */
        auto transpose_impl = [](auto &transposed, const auto& a, auto rows, auto cols) {
            for (int i=0; i<cols; i++)
                for (int j=0; j<rows; j++)
                    at(transposed,i,j) = at(a,j,i);
        };

        if constexpr (is_fixed_size) {
            /* TODO: find-out if reading shape as constexpr here is beneficial */
            // rejected by clang:
            // constexpr auto shape = matrix_size(a);
            constexpr auto shape = fixed_matrix_size_v<Array>;
            constexpr auto rows = get<0>(shape);
            constexpr auto cols = get<1>(shape);
            /* make zeros with transposed size */
            auto transposed = zeros<return_t,cols,rows>();
            transpose_impl(transposed,a,rows,cols);
            return transposed;
        }
        else {
            auto [rows,cols] = matrix_size(a);
            /* make zeros with transposed size */
            auto transposed = zeros<return_t>(cols,rows);
            transpose_impl(transposed,a,rows,cols);
            return transposed;
        }
    } // constexpr auto transpose(const Array& a)
}

#endif // NMTOOLS_ARRAY_UTILITY_TRANSPOSE_HPP