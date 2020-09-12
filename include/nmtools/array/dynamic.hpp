#ifndef NMTOOLS_ARRAY_DYNAMIC_HPP
#define NMTOOLS_ARRAY_DYNAMIC_HPP

#include "nmtools/array/utility.hpp"
#include "nmtools/meta.hpp"
/* include fixed array for metafunction specialization */
#include "nmtools/array/fixed.hpp"
#include <vector>
#include <initializer_list>

namespace nmtools::array
{
    using std::initializer_list;

    template <typename T>
    struct dynamic_vector
    {
        using data_type = std::vector<T>;
        using value_type = T;
        using size_type = size_t;
        using reference = value_type&;
        using const_reference = const value_type&;

        explicit dynamic_vector(size_type n)
        {
            data.resize(n);
        }

        dynamic_vector(initializer_list<value_type> initializer)
        {
            data.resize(initializer.size());
            size_t i=0;
            for (auto v : initializer)
                data[i++] = v;
        }

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

        /**
         * @brief resize vector to contain count elements.
         * 
         * @param count 
         */
        void resize(size_type count)
        {
            data.resize(count);
        }
    };

    template <typename T>
    struct dynamic_matrix
    {
        using data_type = std::vector<T>;
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
    };
    
} // namespace nmtools::array

namespace nmtools
{
    /**
     * @brief specialization of vector_size for dynamic_vector
     * 
     * @tparam T element type of dynamic_vector, automatically deduced
     * @param v vector which size is to be checked
     * @return auto 
     */
    template <typename T>
    auto vector_size(const array::dynamic_vector<T>& v)
    {
        return v.size();
    }

    /**
     * @brief specialization of matrix_size for dynamic_matrix
     * 
     * @tparam T element type of dynamic_matrix, automatically deduced
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
    template <typename T>
    auto zeros_like(const array::dynamic_vector<T>& v)
    {
        auto ret = array::dynamic_vector<T>(v.size()); 
        return ret;
    }

    template <typename T>
    auto zeros_like(const array::dynamic_matrix<T>& m)
    {
        auto [rows, cols] = m.shape();
        auto ret = array::dynamic_matrix<T>(rows,cols); 
        return ret;
    }
}

namespace nmtools::traits
{
    /**
     * @brief specialization of is_array1d traits for dynamic_vector which is true
     * 
     * @tparam T element type of dynamic_vector, automatically deduced
     */
    template <typename T>
    struct is_array1d<array::dynamic_vector<T>> : true_type {};

    /**
     * @brief specialization of is_array2d traits for dynamic_vector which is false
     * 
     * @tparam T element type of dynamic_vector, automatically deduced
     */
    template <typename T>
    struct is_array2d<array::dynamic_vector<T>> : false_type {};

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
     * @brief specialization of is_resizeable trait for dynamic_vector which is true
     * 
     * @tparam T element type of dynamic_vector, automatically deduced
     */
    template <typename T>
    struct is_resizeable<array::dynamic_vector<T>> : true_type {};

    /**
     * @brief specialiation of is_resizeable trait for dynamic_matrix which is true
     * 
     * @tparam T element type of dynamic_matrix, automatically deduced
     */
    template <typename T>
    struct is_resizeable<array::dynamic_matrix<T>> : true_type {};
    
} // namespace nmtools::traits

namespace nmtools::meta
{
    /**
     * @brief specialization for metafunction make_outer_matrix,
     * which tells matrix type for outer product,
     * for custom vector type array::dynamic_vector to 
     * give array::dynamic_matrix as resulting type.
     * 
     * @tparam T value_type of lhs vector, automatically deduced.
     * @tparam U value_type of rhs vector, automatically deduced.
     */
    template <typename T, typename U>
    struct make_outer_matrix<array::dynamic_vector<T>,array::dynamic_vector<U>>
    {
        using common_t = std::common_type_t<T,U>;
        using type = array::dynamic_matrix<common_t>;
    };

    /**
     * @brief 
     * 
     * @tparam T 
     * @tparam U 
     * @tparam N 
     */
    template <typename T, typename U, size_t N>
    struct make_outer_matrix<array::dynamic_vector<T>,array::fixed_vector<U,N>>
    {
        using common_t = std::common_type_t<T,U>;
        using type = array::dynamic_matrix<common_t>;
    };

    /**
     * @brief 
     * 
     * @tparam T 
     * @tparam U 
     * @tparam N 
     */
    template <typename T, typename U, size_t N>
    struct make_outer_matrix<array::fixed_vector<U,N>,array::dynamic_vector<T>>
    {
        using common_t = std::common_type_t<T,U>;
        using type = array::dynamic_matrix<common_t>;
    };
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_DYNAMIC_HPP