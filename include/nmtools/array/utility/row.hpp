#ifndef NMTOOLS_ARRAY_UTILITY_ROW_HPP
#define NMTOOLS_ARRAY_UTILITY_ROW_HPP

#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index.hpp"
#include "nmtools/array/view/slice.hpp"

#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/clone.hpp"
#include "nmtools/constants.hpp"

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
     * @brief tag to resolve row op type
     * 
     */
    struct row_t {};

    /**
     * @brief resolve row op return type for raw array
     * 
     * @tparam T arithmetic type
     * @tparam Rows number of rows
     * @tparam Cols number of cols
     */
    template <typename T, size_t Rows, size_t Cols>
    struct meta::resolve_optype<std::enable_if_t<std::is_arithmetic_v<T>>,row_t,T[Rows][Cols]>
    {
        using type = std::array<T,Cols>;
    }; // resolve_optype

    /**
     * @brief resolve row op return type for raw array and not fixed-size matrix
     * 
     * @tparam T 
     */
    template <typename T>
    struct meta::resolve_optype<
        std::enable_if_t<(meta::nested_array_dim_v<T> == 2) && !meta::is_fixed_size_matrix_v<T> >,
        row_t, T
    >
    {
        using type = remove_nested_array_dim_t<T,1>;
    }; // resolve_optype

    /**
     * @brief resolve row op return type for std array
     * 
     * @tparam T artihmetic type
     * @tparam Rows 
     * @tparam Cols 
     */
    template <typename T, size_t Rows, size_t Cols>
    struct meta::resolve_optype<std::enable_if_t<std::is_arithmetic_v<T>>,row_t,std::array<std::array<T,Cols>,Rows>>
    {
        using type = std::array<T,Cols>;
    }; // resolve_optype

    /**
     * @brief given marix M, get its r-th row.
     * 
     * @tparam Matrix matrix-like
     * @param M matrix in which its row to be taken.
     * @param r row.
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto row(const array_t& M, size_t r)
    {
        static_assert(
            meta::is_array2d_v<array_t>
            /* TODO: helpful error message here */
        );
        using return_t = meta::resolve_optype_t<row_t,array_t>;
        static_assert( !std::is_void_v<return_t>
            , "unsupported row, cant resolve return type may be specialization of resolv_optype for row_t required"
        );
        using detail::clone_impl;

        auto [rows,cols] = shape(M);
        auto axis0 = std::tuple{r,r+1};
        auto axis1 = std::tuple{0,None};
        auto row_ref     = view::slice(M,axis0,axis1);
        // @todo static_assert whenever possible
        {
            auto [rows,cols_] = shape(row_ref);
            assert ( (rows==1) && (cols==cols_)
                // , unexpected error
            );
        }
        auto row_flat = view::flatten(row_ref);

        auto ret         = return_t{};
        // @todo use resize fn
        if constexpr (meta::is_resizeable_v<return_t>)
            ret.resize(cols);
        clone_impl(ret,row_flat,cols);
        return ret;
    } // constexpr auto row(const Matrix, size_type r)

    /** @} */ // end group utility
} // namespace nmtools

#endif // NMTOOLS_ARRAY_UTILITY_ROW_HPP