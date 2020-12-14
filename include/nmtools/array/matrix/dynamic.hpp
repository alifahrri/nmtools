#ifndef NMTOOLS_ARRAY_MATRIX_DYNAMIC_HPP
#define NMTOOLS_ARRAY_MATRIX_DYNAMIC_HPP

#include "nmtools/array/detail.hpp"
#include "nmtools/meta.hpp"
#include <cassert>
#include <vector>
#include <initializer_list>

namespace nmtools::array
{
    using std::initializer_list;

    /**
     * @addtogroup Dynamic Dynamic Array
     * @ingroup array
     * @{
     */

    /**
     * @brief sample implementation of dynamic matrix with flat storage
     * 
     * @tparam T element type of dynamic matrix
     * @tparam storage_type=std::vector template template parameter to store actual data
     */
    template <typename T, template <typename> typename storage_type=std::vector>
    struct dynamic_matrix
    {
        using data_type = storage_type<T>;
        using value_type = T;
        using size_type = size_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using shape_type = std::pair<size_t,size_t>;

        explicit dynamic_matrix(size_type rows, size_type cols)
            : _rows(rows), _cols(cols)
        {
            data.resize(_rows*_cols);
        }

        dynamic_matrix(initializer_list<initializer_list<T>> initializer)
            : _rows(initializer.size()), _cols(initializer.size() ? initializer.begin()->size() : 0)
        {
            data.resize(_rows*_cols);
            size_t i=0;
            /* flatten 2d initializer to 1d */
            for (const auto &v : initializer)
                for (const auto &e : v)
                    data[i++] = e;
        }

        /**
         * @brief underlying data
         * 
         */
        data_type data;
        
        /**
         * @brief 
         * 
         */
        size_type _cols;

        /**
         * @brief 
         * 
         */
        size_type _rows;

        /**
         * @brief access element at (row,col)-th index
         * 
         * @param row row index
         * @param col column index
         * @return constexpr reference 
         */
        constexpr reference operator()(size_type row, size_type col)
        {
            return data[row*_cols+col];
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
            return data[row*_cols+col];
        }

        /**
         * @brief return the number of rows
         * 
         * @return constexpr size_type 
         * @todo remove
         */
        constexpr size_type size() const noexcept
        {
            return _rows;
        }

        /**
         * @brief return the number of rows
         * 
         * @return constexpr shape_type 
         */
        constexpr shape_type shape() const noexcept
        {
            return std::make_pair(_rows,_cols);
        }

        /**
         * @brief resize vector to contain count elements.
         * 
         * @param rows new row size
         * @param cols new column size
         */
        void resize(size_type rows, size_type cols)
        {
            _rows = rows;
            _cols = cols;
            data.resize(rows*cols);
        }

        template <typename matrix_t>
        constexpr auto operator=(const matrix_t& rhs);

        /**
         * @brief provides assignment operator from nested std::array
         * 
         * @param rhs nested std array to be copied
         * @return constexpr decltype(auto) 
         */
        template <size_t Rows, size_t Cols>
        constexpr decltype(auto) operator=(meta::make_nested_raw_array_t<T,Rows,Cols>&& rhs)
        {
            using nested_t = meta::make_nested_raw_array_t<T,Rows,Cols>;
            return this->template operator=<nested_t>(std::forward<nested_t>(rhs));
        } // operator=
    };

    /**
     * @brief helper traits to check if given type T is dynamic_matrix
     * 
     * @tparam T 
     * @tparam typename=void 
     * @see nmtools::testing::cast
     */
    template <typename T, typename=void>
    struct is_dynamic_matrix : std::false_type {};

    /**
     * @brief specialization of is_dynamic_matrix in which given type is actually dynamic_matrix
     * 
     * @tparam T element type of dynamic_matrix
     * @see nmtools::testing::cast
     */
    template <typename T>
    struct is_dynamic_matrix<dynamic_matrix<T>> : std::true_type {};

    /** @} */ // end group dynamic

} // namespace nmtools::array

namespace nmtools
{
    /**
     * @brief specialization of matrix_size for dynamic_matrix
     * 
     * @tparam T element type of dynamic_matrix, deduced via template argument deduction
     * @param m matrix which size is to be checked
     * @return auto 
     */
    template <typename T>
    auto matrix_size(const array::dynamic_matrix<T>& m)
    {
        return m.shape();
    }

} // namespace nmtools

namespace nmtools::blas
{
    /**
     * @ingroup blas
     * 
     */

    /**
     * @brief overloaded version of zeros_like for array::dynamic_vector
     * 
     * @tparam T element type of dynamic_vector
     * @param v reference vector
     * @return auto 
     */
    template <typename T>
    auto zeros_like(const array::dynamic_matrix<T>& m)
    {
        auto [rows, cols] = m.shape();
        auto ret = array::dynamic_matrix<T>(rows,cols); 
        return ret;
    }

    /** @} */ // end group blas
}

#include "nmtools/traits.hpp"

namespace nmtools::meta
{
    /**
     * @ingroup meta
     * 
     */

    /**
     * @brief specialization of is_array1d traits for dynamic_matrix which is false
     * 
     * @tparam T element type of dynamic_matrix, automatically deduced
     */
    template <typename T>
    struct is_array1d<array::dynamic_matrix<T>> : false_type {};

    /**
     * @brief specialization of is_array2d traits for dynamic_matrix which is true
     * 
     * @tparam T element type of dynamic_matrix, automatically deduced
     */
    template <typename T>
    struct is_array2d<array::dynamic_matrix<T>> : true_type {};

    /**
     * @brief specialiation of is_resizeable trait for dynamic_matrix which is true
     * 
     * @tparam T element type of dynamic_matrix, automatically deduced
     */
    template <typename T>
    struct is_resizeable<array::dynamic_matrix<T>> : true_type {};

    /** @} */ // end group traits
    
} // namespace nmtools::meta

#include "nmtools/meta.hpp"
// include fixed array for metafunction specialization
// note: fixed array also include array/utility,
// include here so that dynamic vector_size and matrix_size visible
#include "nmtools/array/matrix/fixed.hpp"
#include "nmtools/array/vector/dynamic.hpp"
#include "nmtools/array/utility/row.hpp" // clone_impl

namespace nmtools
{
    template <typename T>
    struct meta::resolve_optype<void,row_t,array::dynamic_matrix<T>>
    {
        using type = array::dynamic_vector<T>;
    }; // resolve_optype
} // namespace nmtools

namespace nmtools::meta
{
    /**
     * @ingroup meta
     * 
     */

    /**
     * @brief specialization for metafunction make_outer_matrix,
     * which tells matrix type for outer product,
     * for custom vector type array::dynamic_vector to 
     * give array::dynamic_matrix as resulting type.
     * 
     * @tparam T value_type of lhs vector, automatically deduced.
     * @tparam U value_type of rhs vector, automatically deduced.
     * @see nmtools::blas::outer
     */
    template <typename T, typename U>
    struct make_outer_matrix<array::dynamic_vector<T>,array::dynamic_vector<U>>
    {
        using common_t = std::common_type_t<T,U>;
        using type = array::dynamic_matrix<common_t>;
    };

    /**
     * @brief specialization of metafunction make_outer_matrix,
     * which tells matrix type for outer product, 
     * for array::fixed_vector and array::dynamic_vector,
     * resulting in array::dynamic_matrix type.
     * 
     * @tparam T element type of dynamic_vector
     * @tparam U element type of fixed_vector
     * @tparam N number of element of fixed_vector
     * @see nmtools::blas::outer
     */
    template <typename T, typename U, size_t N>
    struct make_outer_matrix<array::fixed_vector<U,N>,array::dynamic_vector<T>>
    {
        using common_t = std::common_type_t<T,U>;
        using type = array::dynamic_matrix<common_t>;
    };

    /**
     * @brief specialization of metafunction make_outer_matrix,
     * which tells matrix type for outer product, 
     * for array::dynamic_vector and array::fixed_vector,
     * resulting in array::dynamic_matrix type.
     * 
     * @tparam T element type of dynamic_vector
     * @tparam U element type of fixed_vector
     * @tparam N number of element of fixed_vector
     * @see nmtools::blas::outer
     */
    template <typename T, typename U, size_t N>
    struct make_outer_matrix<array::dynamic_vector<T>,array::fixed_vector<U,N>>
    {
        using common_t = std::common_type_t<T,U>;
        using type = array::dynamic_matrix<common_t>;
    };

    /**
     * @brief specialization of metafunction get_column_type,
     * which tells vector type for column function,
     * for array::dynamic_matrix, resulting in array::dynamic_vector type.
     * 
     * @tparam T 
     * @see nmtools::column
     * @see ntmools::row
     */
    template <typename T>
    struct get_column_type<array::dynamic_matrix<T>>
    {
        using type = array::dynamic_vector<T>;
    };

    /**
     * @brief specialization of metafunction get_row_type,
     * which tells vector type for row function,
     * for array::dynamic_matrix, resulting in array::dynamic_vector type.
     * 
     * @tparam T 
     * @see nmtools::column
     * @see ntmools::row
     */
    template <typename T>
    struct get_row_type<array::dynamic_matrix<T>>
    {
        using type = array::dynamic_vector<T>;
    };

    /**
     * @brief specialization of fixed_dim metafunction for dynamic_vector.
     *
     * Tells the compiler that dynamic_vector has fixed-dimension of 2.
     * 
     * @tparam T element type of dynamic_matrix, automatically deduced
     * @tparam storage_type, template-template parameter corresponding to the storage type of dynamic_matrix, automatically deduced
     */
    template <typename T, template <typename> typename storage_type>
    struct fixed_dim<array::dynamic_matrix<T,storage_type>>
    {
        static constexpr auto value = 2;
        using value_type = decltype(value);
    }; // fixed_dim

    /**
     * @brief specialize replace_element_type for array::dynamic_matrix type
     * 
     * @tparam T 
     * @tparam storage_type 
     * @tparam U 
     */
    template <typename T, template <typename> typename storage_type, typename U>
    struct replace_element_type<array::dynamic_matrix<T,storage_type>,U,std::enable_if_t<std::is_arithmetic_v<U>>>
    {
        using type = array::dynamic_matrix<U,storage_type>;
    };

    /** @} */ // end group meta
} // namespace nmtools::meta

#include "nmtools/array/utility/clone.hpp" // clone_impl

namespace nmtools::array
{
    
    /**
     * @brief assignment operator for dynamic_matrix from generic matrix type
     * 
     * @tparam T element type of dynamic_matrix
     * @tparam Rows compile-time rows of dynamic_matrix
     * @tparam Cols compile-time cols of dynamic_matrix
     * @tparam matrix_t type of matrix to be cloned
     * @param rhs matrix to be cloned
     * @return constexpr auto 
     * @see nmtools::matrix_size
     * @see nmtools::detail::clone_impl
     */
    template <typename T, template <typename> typename storage_type>
    template <typename matrix_t>
    constexpr auto dynamic_matrix<T,storage_type>::operator=(const matrix_t& rhs)
    {
        static_assert(
            meta::is_array2d_v<matrix_t>,
            "dynamic_matrix only support assignment from array2d for now"
        );

        using ::nmtools::detail::clone_impl;

        auto [rows, cols] = matrix_size(rhs);
        assert( (rows==_rows) && (cols==_cols)
            // , "mismatched type for dynamic_matrix assignment"
        );
        clone_impl(*this,rhs,rows,cols);

        return *this;
    } // operator=

} // namespace nmtools::array


#endif // NMTOOLS_ARRAY_MATRIX_DYNAMIC_HPP