#ifndef NMTOOLS_ARRAY_MATRIX_FIXED_HPP
#define NMTOOLS_ARRAY_MATRIX_FIXED_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp" // fixed_matrix_size etc.

#include <array>
#include <tuple>

/**
 * @defgroup array 
 * collections of array functions and structs.
 * 
 */

namespace nmtools::array {

    /**
     * @addtogroup Fixed Fixed Array
     * @ingroup array
     * @{
     */

    /**
     * @brief naive implementation of fixed size matrix.
     * 
     * @tparam T value type
     * @tparam Rows number of rows
     * @tparam Cols number of columns
     */
    template <typename T, size_t Rows, size_t Cols>
    struct fixed_matrix
    {
        using data_type = std::array<T,Rows*Cols>;
        using value_type = T;
        using size_type = size_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using shape_type = std::pair<size_t,size_t>;

        /**
         * @brief underlying data
         * 
         */
        data_type data;

        /**
         * @brief access element at (row,col)-th index
         * 
         * @param row row index
         * @param col column index
         * @return constexpr reference 
         */
        constexpr reference operator()(size_type row, size_type col)
        {
            return data[row*Cols+col];
        } // operator()(size_type,size_type)

        /**
         * @brief access element at (row,col)-th index
         * 
         * @param row row index
         * @param col column index
         * @return constexpr const_reference 
         */
        constexpr const_reference operator()(size_type row, size_type col) const
        {
            return data[row*Cols+col];
        } // operator()(size_type,size_type)

        /**
         * @brief 
         * 
         * @tparam row 
         * @tparam col 
         * @return constexpr const_reference 
         */
        template <size_type row, size_type col>
        constexpr const_reference operator()() const
        {
            return data[row*Cols+col];
        } // operator()<size_type,size_type>()

        /**
         * @brief access row
         * 
         * @param row row index
         * @return constexpr auto array of reference
         */
        constexpr auto operator()(size_type row)
        {
            return detail::make_array_ref(data,detail::size_constant<Cols>{},row*Cols);
        } // operator()(size_type)

        /**
         * @brief access row
         * 
         * @param row row index
         * @return constexpr auto array of reference
         */
        constexpr auto operator()(size_type row) const
        {
            return detail::make_array_ref(data,detail::size_constant<Cols>{},row*Cols);
        } // operator()(size_type)

        /**
         * @brief return the number of rows
         * 
         * @return constexpr size_type 
         */
        constexpr size_type size() const noexcept
        {
            return Rows;
        } // size()

        /**
         * @brief return the number of rows
         * 
         * @return constexpr shape_type 
         */
        constexpr shape_type shape() const noexcept
        {
            return std::make_pair(Rows,Cols);
        } // shape()

        template <typename matrix_t>
        constexpr auto operator=(const matrix_t& rhs);

        /**
         * @brief provides assignment operator from nested std::array
         * 
         * @param rhs nested std array to be copied
         * @return constexpr decltype(auto) 
         */
        constexpr decltype(auto) operator=(meta::make_nested_raw_array_t<T,Rows,Cols>&& rhs)
        {
            using nested_t = meta::make_nested_raw_array_t<T,Rows,Cols>;
            return this->template operator=<nested_t>(std::forward<nested_t>(rhs));
        } // operator=
    }; // struct fixed_matrix
    
    /**
     * @brief helper traits to check if given type is array::fixed_matrix,
     * not to be confused with nmtools::traits::is_fixed_matrix which is
     * more generic in concept not to differentiate
     * specific type (array::fixed_matrix in this case).
     * 
     * @tparam T type to check
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct is_fixed_matrix : std::false_type {};

    /**
     * @brief true case for nmtools::array::is_fixed_matrix
     * 
     * @tparam T value type of nmtools::array::fixed_matrix, deduced automatically
     * @tparam Rows number of row of nmtools::array::fixed_matrix, deduced automatically
     * @tparam Cols number of column of nmtools::array::fixed_matrix, deduced automatically
     */
    template <typename T, size_t Rows, size_t Cols>
    struct is_fixed_matrix<fixed_matrix<T,Rows,Cols>,void> : std::true_type {};

    /** @} */ // end group fixed array
} // namespace nmtools::array

namespace nmtools
{
    /**
     * @ingroup utility
     * 
     */

    /**
     * @brief specialization of dynamic_matrix size for fixed_vector.
     * 
     * @tparam T 
     * @tparam Rows 
     * @tparam Cols 
     * @param m 
     * @return auto 
     * @note since some functions in "nmtools/array/utility.hpp" depends on matrix_size and matrix_size
     * is also definded in that file, this overload should be defined before including the file to make
     * overload visible
     * @todo fix include
     */
    template <typename T, size_t Rows, size_t Cols>
    constexpr auto matrix_size(const array::fixed_matrix<T,Rows,Cols>& m)
    {
        return m.shape();
    } // constexpr auto matrix_size

    /** @} */ // end group utility

    /**
     * @brief 
     * 
     * @tparam T 
     * @tparam Rows 
     * @tparam Cols 
     * @param M 
     * @param r 
     * @return constexpr auto 
     * @todo dont specialize, use generic + metafunction instead
     */
    template <typename T, size_t Rows, size_t Cols>
    constexpr auto row(const array::fixed_matrix<T,Rows,Cols>& M, size_t r)
    {
        using array_t = std::array<T,Cols>;
        using indices_t = std::make_index_sequence<Cols>;
        return array::detail::make_array<array_t>(M.data, indices_t{}, r*Cols);
    } // constexpr auto row

    /* TODO: consider to move to meta */
    /**
     * @brief specialization of fixed_matrix for fixed_matrix_size array traits.
     * 
     * @tparam T 
     * @tparam Rows 
     * @tparam Cols 
     */
    template <typename T, size_t Rows, size_t Cols>
    struct fixed_matrix_size<array::fixed_matrix<T,Rows,Cols>>
    {
        static inline constexpr auto value = std::make_pair(Rows,Cols);
        using value_type = decltype(value);
    };

    /**
     * @brief specialization of fixed_matrix for fixed_array_shape array traits.
     * 
     * @tparam T element type of fixed_matrix
     * @tparam Rows number of rows of fixed_matrix
     * @tparam Cols number of cols of fixed_matrix
     */
    template <typename T, size_t Rows, size_t Cols>
    struct fixed_array_shape<array::fixed_matrix<T,Rows,Cols>>
        : fixed_matrix_size<array::fixed_matrix<T,Rows,Cols>>
    {};

} // namespace nmtools

#include "nmtools/traits.hpp"

namespace nmtools::traits
{
    /**
     * @ingroup traits
     * @{
     */

    /**
     * @brief specialization of array traits for fixed_matrix
     * 
     * @tparam T 
     * @tparam Rows 
     * @tparam Cols 
     */
    template <typename T, size_t Rows, size_t Cols>
    struct is_array2d<array::fixed_matrix<T,Rows,Cols>> : true_type {};

    /** @} */ // end group traits
} // namespace nmtooclls::traits

#include "nmtools/meta.hpp"
#include "nmtools/array/vector/fixed.hpp"

namespace nmtools::meta
{
    /**
     * @ingroup meta
     * @{
     */
    
    /**
     * @brief specialization of metafunction make_outer_matrix,
     * which create matrix type for outer product,
     * for custom fixed-size vector type array::fixed_vector.
     * 
     * @tparam T value_type of lhs vector, deduced automatically.
     * @tparam U value_type of rhs vector, deduced automatically.
     * @tparam M element size of lhs vector, deduced automatically.
     * @tparam N element size of rhs vector, deduced automatically.
     */
    template <typename T, typename U, size_t M, size_t N>
    struct make_outer_matrix<array::fixed_vector<T,M>,array::fixed_vector<U,N>>
    {
        using common_t = std::common_type_t<T,U>;
        using type = array::fixed_matrix<common_t,M,N>;
    };

    /**
     * @brief specialization of metafunction make_zeros_matrix
     * for custom fixed-size matrix array::fixed_matrix.
     * 
     * @tparam T value_type of original fixed-size matrix with fixed compile time shape, deduced automatically
     * @tparam Rows new desired row size
     * @tparam Cols new desired column size
     * @tparam oM old row size of original fixed-size matrix type, deduced automatically
     * @tparam oN old col size of original fixed-size matrix type, deduced automatically
     */
    template <typename T, size_t Rows, size_t Cols, size_t oM, size_t oN>
    struct make_zeros_matrix<array::fixed_matrix<T,oM,oN>,Rows,Cols>
    {
        using type = array::fixed_matrix<T,Rows,Cols>;
    };

    /**
     * @brief specialization of metafunction get_column_type,
     * which determinde the resulting type for column op.
     * 
     * @tparam T T value_type of original fixed-size matrix with fixed compile time shape, deduced automatically
     * @tparam M Rows row size of array::fixed_matrix, deduced automatically
     * @tparam N Cols column size of array::fixed_matrix, deduced automatically
     * @see nmtools::column
     * @see nmtools::blas::row_sum
     */
    template <typename T, size_t Rows, size_t Cols>
    struct get_column_type<array::fixed_matrix<T,Rows,Cols>>
    {
        using type = array::fixed_vector<T,Cols>;
    }; // struct get_column_type

    /**
     * @brief specialization of metafunction get_row_type for array::fixed_matrix type,
     * which determine the resulting type for col_sum op.
     * 
     * @tparam T value_type of array::fixed_matrix, automatically deduced
     * @tparam Rows row size of array::fixed_matrix, deduced automatically
     * @tparam Cols column size of array::fixed_matrix, deduced automatically
     */
    template <typename T, size_t Rows, size_t Cols>
    struct get_row_type<array::fixed_matrix<T,Rows,Cols>>
    {
        using type = array::fixed_vector<T,Rows>;
    }; // struct get_column_type

    /**
     * @brief specializatoin of metafunction resize_fixed_matrix for array::fixed_matrix type,
     * which create new type with new size at compile-time.
     * 
     * @tparam T element type of array::fixed_matrix
     * @tparam M number of row of original array::fixed_matrix type
     * @tparam N number of column of original array::fixed_matrix type
     * @tparam Rows new desired row for new type
     * @tparam Cols new desired column for new type
     */
    template <typename T, auto M, auto N, auto Rows, auto Cols>
    struct resize_fixed_matrix<array::fixed_matrix<T,M,N>,Rows,Cols>
    {
        using type = array::fixed_matrix<T,Rows,Cols>;
    };

    /** @} */ // end group meta
} // namespace nmtools::meta

#include "nmtools/array/utility/clone.hpp" // clone_impl

namespace nmtools::array
{
    
    /**
     * @brief assignment operator for fixed_matrix from generic matrix type
     * 
     * @tparam T element type of fixed_matrix
     * @tparam Rows compile-time rows of fixed_matrix
     * @tparam Cols compile-time cols of fixed_matrix
     * @tparam matrix_t type of matrix to be cloned
     * @param rhs matrix to be cloned
     * @return constexpr auto 
     * @see nmtools::matrix_size
     * @see nmtools::detail::clone_impl
     */
    template <typename T, size_t Rows, size_t Cols>
    template <typename matrix_t>
    constexpr auto fixed_matrix<T,Rows,Cols>::operator=(const matrix_t& rhs)
    {
        static_assert(
            traits::is_array2d_v<matrix_t>,
            "fixed_matrix only support assignment from array2d for now"
        );

        using ::nmtools::detail::clone_impl;

        if constexpr (traits::is_fixed_size_matrix_v<matrix_t>) {
            constexpr auto size_ = fixed_matrix_size_v<matrix_t>;
            constexpr auto rows  = std::get<0>(size_);
            constexpr auto cols  = std::get<1>(size_);

            static_assert( (rows==Rows) && (cols==Cols),
                "mismatched type for fixed_matrix assignment"
            );
            clone_impl(*this,rhs,rows,cols);
        }
        else {
            auto [rows, cols] = matrix_size(rhs);
            assert( (rows==Rows) && (cols==Cols)
                // , "mismatched type for fixed_matrix assignment"
            );
            clone_impl(*this,rhs,rows,cols);
        }
        return *this;
    } // operator=

} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_MATRIX_FIXED_HPP