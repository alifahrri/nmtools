#ifndef NMTOOLS_ARRAY_FIXED_HPP
#define NMTOOLS_ARRAY_FIXED_HPP

#include <array>

/**
 * @defgroup array 
 * collections of array functions and structs.
 * 
 */

#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp" // fixed_matrix_size etc.

namespace nmtools::array {

    /**
     * @addtogroup Fixed Fixed Array
     * @ingroup array
     * @{
     */

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
     * @brief sample implementation of n-dimensional array,
     * trying to mimic numpy ndarray layout @cite NumPy_ndarray_layout
     * 
     * @tparam T element type of fixed_ndarray
     * @tparam Shape1 the size of 1st axis of fixed_ndarray
     * @tparam ShapeN the sizes of the rest axes of fixed_ndarray
     */
    template <typename T, size_t Shape1, size_t...ShapeN>
    struct fixed_ndarray
    {
        // godbolt : https://godbolt.org/z/xP31vz
        /**
         * @brief return the number of dimension
         * 
         * @return constexpr auto 
         */
        static constexpr auto dim()
        {
            return sizeof...(ShapeN) + 1;
        }
        static inline constexpr auto dim_ = dim();

        /**
         * @brief return the shape information
         * 
         * @return constexpr auto 
         */
        static constexpr auto shape()
        {
            return std::array<size_t,dim_>{Shape1,ShapeN...};
        }
        static inline constexpr auto shape_ = shape();

        /**
         * @brief return the number of elements
         * 
         * @return constexpr auto 
         */
        static constexpr auto numel()
        {
            size_t numel_ = 1;
            for (auto s : shape_)
                numel_ *= s;
            return numel_;
        }
        static inline constexpr auto numel_ = numel();

        /**
         * @brief return the strides information
         * 
         * @return constexpr auto 
         */
        static constexpr auto strides()
        {
            auto stride = std::array<size_t,dim()>{};
            for (size_t i=0; i<dim(); i++)
                stride[i] = detail::stride(shape_,i);
            return stride;
        }
        static inline constexpr auto strides_ = strides();

        using data_type = std::array<T,numel_>;
        using value_type = T;
        using size_type = size_t;
        using reference = value_type&;
        using const_reference = const value_type&;

        data_type data;

        /**
         * @brief mutable access to element
         * 
         * @tparam size 
         * @param n 1st index of element to be accessed
         * @param ns the rest of indices of element to be accessed
         * @return constexpr reference 
         */
        template <typename...size>
        constexpr reference operator()(size_type n, size...ns)
        {
            static_assert(sizeof...(ns)==sizeof...(ShapeN),
                "unsupported number of index"
            );
            using common_size_t = std::common_type_t<size_type,size...>;
            auto indices = std::array<common_size_t,sizeof...(ns)+1>{n,static_cast<common_size_t>(ns)...};
            auto offset = detail::compute_offset(strides_, indices);
            return data[offset];
        } // operator()

        /**
         * @brief immutable access to element
         * 
         * @tparam size 
         * @param n 1st index of element to be accessed
         * @param ns the rest of indices of element to be accessed
         * @return constexpr const_reference 
         */
        template <typename...size>
        constexpr const_reference operator()(size_type n, size...ns) const
        {
            static_assert(sizeof...(ns)==sizeof...(ShapeN),
                "unsupported number of index"
            );
            auto indices = std::array<size_type,sizeof...(ns)+1>{n,ns...};
            auto offset = detail::compute_offset(strides_, indices);
            return data[offset];
        } // operator()
    }; // struct fixed_ndarray
    
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
     * @brief specialization of dynamic_vector size for fixed_vector.
     * 
     * @tparam T 
     * @tparam N 
     * @param v 
     * @return auto 
     * @note since some functions in "nmtools/array/utility.hpp" depends on vector_size and vector_size
     * is also definded in that file, this overload should be defined before including the file to make
     * overload visible
     * @todo fix include
     */
    template <typename T, size_t N>
    constexpr auto vector_size(const array::fixed_vector<T,N>& v)
    {
        return v.size();
    } // constexpr auto vector_size

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

    /**
     * @brief return the shape of fixed_ndarray, which is known at compile-time
     * 
     * @tparam T element type of fixed_ndarray
     * @tparam Shape1 the size of element at 1st axis
     * @tparam ShapeN the sizes of the element for the rest of axes
     * @param a ndarray
     * @return constexpr auto 
     */
    template <typename T, size_t Shape1, size_t...ShapeN>
    constexpr auto array_shape(const array::fixed_ndarray<T,Shape1,ShapeN...>& a)
    {
        return a.shape();
    } // array_shape

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

} // namespace nmtools

#include "nmtools/traits.hpp"

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

    /**
     * @brief specialization of is_ndarray traits for fixed_ndarray
     * 
     * @tparam T element type of ndarray
     * @tparam Shape1 size of first axis
     * @tparam ShapeN sizes of the rest axis
     */
    template <typename T, size_t Shape1, size_t...ShapeN>
    struct is_ndarray<array::fixed_ndarray<T,Shape1,ShapeN...>> : true_type {};

    /**
     * @brief specialization fo is_fixed_ndarray traits for fixed_ndarray
     * 
     * @tparam T element type of ndarray
     * @tparam Shape1 size of first axis
     * @tparam ShapeN sizes of the rest axis
     */
    template <typename T, size_t Shape1, size_t...ShapeN>
    struct is_fixed_ndarray<array::fixed_ndarray<T,Shape1,ShapeN...>> : true_type {};

    /** @} */ // end group traits
} // namespace nmtooclls::traits

#include "nmtools/meta.hpp"

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
}

#endif // NMTOOLS_ARRAY_FIXED_HPP