#ifndef NMTOOLS_ARRAY_UTILITY_COLUMN_HPP
#define NMTOOLS_ARRAY_UTILITY_COLUMN_HPP

#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/shape.hpp"

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
     * @brief 
     * 
     */
    namespace detail {
        /**

         * @brief 
         * 
         * @param col 
         * @param M 
         * @param c 
         * @param rows 
         * @return constexpr auto 
         */
        constexpr auto column_impl(auto &col, const auto& M, size_t c, size_t rows)
        {
            for (size_t i=0; i<rows; i++)
                at(col,i) = at(M,i,c);
        } // constexpr auto column_impl
    } // namespace detail

    /**
     * @brief 
     * 
     * @tparam T 
     * @param c 
     * @return constexpr auto 
     */
    template <typename T>
    constexpr auto column(const T& M, size_t c)
    {
        static_assert(
            traits::is_array2d_v<T>
            /* TODO: helpful error message here */
        );
        using detail::column_impl;
        using column_t = meta::get_column_type_t<T>;
        static_assert(
            !std::is_same_v<column_t,void>,
            "unsupported column type, may be specialization "
            "of nmtools::meta::get_column_type needed (?)"
        );
        constexpr auto is_fixed_size = traits::is_fixed_size_vector_v<column_t>;
        constexpr auto is_resizeable = traits::is_resizeable_v<column_t>;
        if constexpr (is_fixed_size) {
            // NOTE: move instantiation here to make error message less verbose
            auto col = column_t{};
            constexpr auto rows = vector_size(col);
            column_impl(col,M,c,rows);
            return col;
        }
        else if constexpr (is_resizeable) {
            // NOTE: move instantiation here to make error message less verbose
            auto col = column_t{};
            auto [rows,cols] = matrix_size(M);
            col.resize(rows);
            column_impl(col,M,c,rows);
            return col;
        }
        else {
            static_assert(is_fixed_size || is_resizeable);
        }
    } // constexpr auto column

    /** @} */ // end group utility
} // namespace nmtools

#endif // NMTOOLS_ARRAY_UTILITY_COLUMN_HPP