#ifndef NMTOOLS_ARRAY_FIXED_HPP
#define NMTOOLS_ARRAY_FIXED_HPP

#include "nmtools/array/utility.hpp"
#include "nmtools/meta.hpp"
#include <array>

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
     * @brief some implementation details for array impl
     * 
     */
    namespace detail
    {
        using ::nmtools::detail::make_array;

        /**
         * @brief helper alias template to make array of reference
         * 
         * @tparam T 
         * @tparam N 
         */
        template <typename T, size_t N>
        using array_ref = std::array<std::reference_wrapper<T>,N>;

        /**
         * @brief helper alias template for make_array_ref
         * 
         * @tparam N 
         */
        template <size_t N>
        using size_constant = std::integral_constant<size_t,N>;

        /**
         * @brief create array of reference from a.
         * With new_size starting from offset.
         * 
         * @tparam T value_type of a
         * @tparam N size of a
         * @tparam new_size new size of returning array ref
         * @param a array to take reference of
         * @param offset starting index, e.g. a[I+offset]...
         * @return auto array of reference
         */
        template <typename T, size_t N, size_t new_size>
        constexpr auto make_array_ref(std::array<T,N> &a, size_constant<new_size>, size_t offset=0)
        {
            using array_t = array_ref<T,N>;
            return make_array<array_t>(a, std::make_index_sequence<new_size>{}, offset);
        }

        /**
         * @brief create array of reference from a.
         * With new_size starting from offset.
         * 
         * @tparam T value_type of a
         * @tparam N size of a
         * @tparam new_size new size of returning array ref
         * @param a array to take reference of
         * @param offset starting index, e.g. a[I+offset]...
         * @return auto array of reference
         */
        template <typename T, size_t N, size_t new_size>
        constexpr auto make_array_ref(const std::array<T,N> &a, size_constant<new_size>, size_t offset=0)
        {
            using array_t = array_ref<const T,N>;
            return make_array(a, std::make_index_sequence<new_size>{}, offset);
        }
    } // namespace detail
    

    /**
     * @brief naive implementation of fixed-size vector (as in math vector, not container).
     * 
     * @tparam T value_type
     * @tparam N number of element
     */
    template <typename T, size_t N>
    struct fixed_vector
    {
        /**
         * @brief underlying storage type of fixed_vector
         * 
         */
        using data_type = std::array<T,N>;
        /**
         * @brief elemen type of fixed_vector
         * 
         */
        using value_type = T;
        /**
         * @brief size type of fixed_vector
         * 
         */
        using size_type = size_t;
        using reference = value_type&;
        using const_reference = const value_type&;

        /**
         * @brief underlying storage
         * 
         */
        data_type data;

        /**
         * @brief access element at i-th index
         * 
         * @param i 
         * @return constexpr reference 
         */
        constexpr reference operator()(size_type i)
        {
            return data[i];
        }

        /**
         * @brief access element at i-th index
         * 
         * @param i 
         * @return constexpr const_reference 
         */
        constexpr const_reference operator()(size_type i) const
        {
            return data[i];
        }

        /**
         * @brief return the size of vector (number of elements)
         * 
         * @return constexpr size_type 
         */
        constexpr size_type size() const noexcept
        {
            return data.size();
        }
    }; // struct fixed_vector

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
        }

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
        }

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
        }

        /**
         * @brief access row
         * 
         * @param row row index
         * @return constexpr auto array of reference
         */
        constexpr auto operator()(size_type row)
        {
            return detail::make_array_ref(data,detail::size_constant<Cols>{},row*Cols);
        }

        /**
         * @brief access row
         * 
         * @param row row index
         * @return constexpr auto array of reference
         */
        constexpr auto operator()(size_type row) const
        {
            return detail::make_array_ref(data,detail::size_constant<Cols>{},row*Cols);
        }

        /**
         * @brief return the number of rows
         * 
         * @return constexpr size_type 
         */
        constexpr size_type size() const noexcept
        {
            return Rows;
        }

        /**
         * @brief return the number of rows
         * 
         * @return constexpr shape_type 
         */
        constexpr shape_type shape() const noexcept
        {
            return std::make_pair(Rows,Cols);
        }
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

    /**
     * @brief make fixed_vector can be used with range-based for loop
     * 
     * @tparam T value_type of fixed_vector, deduced automatically
     * @tparam N size of fixed_vector, deduced automatically
     * @param v 
     * @return constexpr auto 
     */
    template <typename T, size_t N>
    constexpr auto begin(fixed_vector<T,N>& v)
    {
        return v.data.begin();
    } // constexpr auto begin

    template <typename T, size_t N>
    constexpr auto begin(const fixed_vector<T,N>& v)
    {
        return v.data.begin();
    } // constexpr auto begin

    /**
     * @brief make fixed_vector can be used with range-based for loop
     * 
     * @tparam T value_type of fixed_vector, deduced automatically
     * @tparam N size of fixed_vector, deduced automatically
     * @param v 
     * @return constexpr auto 
     */
    template <typename T, size_t N>
    constexpr auto end(fixed_vector<T,N>& v)
    {
        return v.data.end();
    } // constexpr auto end

    template <typename T, size_t N>
    constexpr auto end(const fixed_vector<T,N>& v)
    {
        return v.data.end();
    } // constexpr auto end

    /** @} */ // end group fixed array
} // namespace nmtools::array

namespace nmtools
{
    /**
     * @ingroup utility
     * 
     */

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

    /**
     * @brief extract I-th elemen of fixed_vector a.
     * 
     * @tparam I element index
     * @tparam T value_type of fixed_vector, automatically deduced
     * @tparam N number of elements of fixed_vector, automatically deduced
     * @param a array to be extracted
     * @return constexpr auto 
     */
    template <std::size_t I, typename T, size_t N>
    constexpr auto get(array::fixed_vector<T,N>& a) noexcept
    {
        return std::get<I>(a.data);
    }

    /**
     * @brief extract I-th elemen of fixed_vector a.
     * 
     * @tparam I element index
     * @tparam T value_type of fixed_vector, automatically deduced
     * @tparam N number of elements of fixed_vector, automatically deduced
     * @param a array to be extracted
     * @return constexpr auto  
     */
    template <std::size_t I, typename T, size_t N>
    constexpr auto get(const array::fixed_vector<T,N>& a) noexcept
    {
        return std::get<I>(a.data);
    }

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

    /* TODO: consider to move to meta */
    /**
     * @brief specialization of fixed_vector for fixed_vector_size array traits.
     * 
     * @tparam T 
     * @tparam N 
     */
    template <typename T, size_t N>
    struct fixed_vector_size<array::fixed_vector<T,N>>
        : std::tuple_size<typename array::fixed_vector<T,N>::data_type> {};
    
    /**
     * @brief specialization of dynamic_vector size for fixed_vector.
     * 
     * @tparam T 
     * @tparam N 
     * @param v 
     * @return auto 
     */
    template <typename T, size_t N>
    constexpr auto vector_size(const array::fixed_vector<T,N>& v)
    {
        return v.size();
    }

    /**
     * @brief specialization of dynamic_matrix size for fixed_vector.
     * 
     * @tparam T 
     * @tparam Rows 
     * @tparam Cols 
     * @param m 
     * @return auto 
     */
    template <typename T, size_t Rows, size_t Cols>
    constexpr auto matrix_size(const array::fixed_matrix<T,Rows,Cols>& m)
    {
        return m.shape();
    }

    /** @} */ // end group utility
} // namespace nmtools

namespace nmtools::traits
{
    /**
     * @ingroup traits
     * @{
     */

    /**
     * @brief specialize array traits for fixed_vector
     * 
     * @tparam T 
     * @tparam N 
     */
    template <typename T, size_t N>
    struct is_array1d<array::fixed_vector<T,N>> : true_type {};

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

namespace nmtools::meta
{
    /**
     * @ingroup meta
     * @{
     */

    /**
     * @brief specialization of metafunction make_zeros_vector
     * for custom fixed-size vector array::fixed_vector.
     * 
     * @tparam T value_type of original fixed-size vector with fixed compile time size, deduced automatically
     * @tparam M old size of fixed_vector, deduced automatically
     * @tparam N new desired size
     */
    template <typename T, size_t M, size_t N>
    struct make_zeros_vector<array::fixed_vector<T,M>,N>
    {
        using type = array::fixed_vector<T,N>;
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
     * @brief specialization of metafunction resize_fixed_vector,
     * which determine the new type given new size.
     * 
     * @tparam T value_type of fixed_vector, which to be resized, automatically deduced
     * @tparam N current size of fixed_vector, automatically deduced
     * @tparam new_size desired new size
     */
    template <typename T, size_t N, size_t new_size>
    struct resize_fixed_vector<array::fixed_vector<T,N>,new_size>
    {
        using type = array::fixed_vector<T,new_size>;
    }; // struct resize_fixed_vector

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

    /** @} */ // end group meta
}

#endif // NMTOOLS_ARRAY_FIXED_HPP