#ifndef NMTOOLS_ARRAY_MATRIX_FIXED_HPP
#define NMTOOLS_ARRAY_MATRIX_FIXED_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp" // meta::fixed_matrix_size etc.
#include "nmtools/array/ndarray/fixed.hpp"

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
        using data_type = meta::make_nested_raw_array_t<T,Rows,Cols>;
        using value_type = T;
        using size_type = size_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using shape_type = std::array<size_t,2>;

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
            return data[row][col];
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
            return data[row][col];
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
            static_assert ((row < Rows) && (col < Cols), "out of bound access to fixed_matrix");
            return data[row][col];
        } // operator()<size_type,size_type>()

        /**
         * @brief access row
         * 
         * @param row row index
         * @return constexpr auto array of reference
         */
        // @todo fix make_array_ref
        // constexpr auto operator()(size_type row)
        // {
        //     return detail::make_array_ref(data,detail::size_constant<Cols>{},row*Cols);
        // } // operator()(size_type)

        /**
         * @brief access row
         * 
         * @param row row index
         * @return constexpr auto array of reference
         */
        // @todo fix make_array_ref
        // constexpr auto operator()(size_type row) const
        // {
        //     return detail::make_array_ref(data,detail::size_constant<Cols>{},row*Cols);
        // } // operator()(size_type)

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
            return {Rows,Cols};
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

    template <typename T, size_t Rows, size_t Cols>
    fixed_matrix(T (&&)[Rows][Cols]) -> fixed_matrix<T,Rows,Cols>;
    
    /**
     * @brief helper traits to check if given type is array::fixed_matrix,
     * not to be confused with nmtools::meta::is_fixed_matrix which is
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

    /* TODO: consider to move to meta */
    /**
     * @brief specialization of fixed_matrix for meta::fixed_matrix_size array traits.
     * 
     * @tparam T 
     * @tparam Rows 
     * @tparam Cols 
     */
    template <typename T, size_t Rows, size_t Cols>
    struct meta::fixed_matrix_size<array::fixed_matrix<T,Rows,Cols>>
    {
        using matrix_type = array::fixed_matrix<T,Rows,Cols>;
        using shape_type  = typename matrix_type::shape_type;
        static inline constexpr auto value = shape_type{Rows,Cols};
        using value_type = decltype(value);
    };

    /**
     * @brief specialization of fixed_matrix for meta::fixed_ndarray_shape array traits.
     * 
     * @tparam T element type of fixed_matrix
     * @tparam Rows number of rows of fixed_matrix
     * @tparam Cols number of cols of fixed_matrix
     */
    template <typename T, size_t Rows, size_t Cols>
    struct meta::fixed_ndarray_shape<array::fixed_matrix<T,Rows,Cols>>
        : meta::fixed_matrix_size<array::fixed_matrix<T,Rows,Cols>>
    {};

    /**
     * @brief specialize replace_element_tyep for array::fixed_matrix
     * 
     * @tparam T 
     * @tparam U 
     * @tparam Rows 
     * @tparam Cols 
     */
    template <typename T, typename U, size_t Rows, size_t Cols>
    struct meta::replace_element_type<array::fixed_matrix<T,Rows,Cols>,U,std::enable_if_t<std::is_arithmetic_v<U>>>
    {
        using type = array::fixed_matrix<U,Rows,Cols>;
    };

} // namespace nmtools

#include "nmtools/traits.hpp"

namespace nmtools::meta
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
     */
    template <typename T, size_t Rows, size_t Cols>
    template <typename matrix_t>
    constexpr auto fixed_matrix<T,Rows,Cols>::operator=(const matrix_t& rhs)
    {
        static_assert(
            meta::is_array2d_v<matrix_t>,
            "fixed_matrix only support assignment from array2d for now"
        );

        auto clone_impl = [](auto& self, const auto& rhs, auto rows, auto cols) {
            for (size_t i=0; i<rows; i++)
                for (size_t j=0; j<cols; j++)
                    at(self,i,j) = at(rhs,i,j);
        };

        if constexpr (meta::is_fixed_size_matrix_v<matrix_t>) {
            constexpr auto size_ = meta::fixed_matrix_size_v<matrix_t>;
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