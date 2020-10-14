#ifndef NMTOOLS_ARRAY_DYNAMIC_HPP
#define NMTOOLS_ARRAY_DYNAMIC_HPP

#include "nmtools/array/detail.hpp"
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
     * @brief sample implementation of resizeable vector
     * 
     * @tparam T elemen type of dynamic vector
     * @tparam storage_type=std::vector template template parameter which will be used to store actual data
     */
    template <typename T, template <typename> typename storage_type=std::vector>
    struct dynamic_vector
    {
        using data_type = storage_type<T>;
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

    /**
     * @brief sample implementation of dynamic n-dimensional array,
     * trying to mimic numpy ndarray layout @cite NumPy_ndarray_layout
     * 
     * @tparam T element type of nd-array
     * @tparam storage_type template template parameter to store data
     */
    template <typename T, template <typename> typename storage_type=std::vector>
    struct dynamic_ndarray
    {
        using data_type = storage_type<T>;
        using value_type = T;
        using size_type = size_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using shape_type = std::vector<size_t>;
        using stride_type = std::vector<size_t>;

        /**
         * @brief construct dynamic_ndarray given shape
         * 
         * @param shape desired shape of dynamic_ndarray
         */
        explicit dynamic_ndarray(std::vector<size_type> shape)
            : shape_(shape)
        {
            strides_ = strides();
            numel_   = numel();
            data.resize(numel_);
        }

        /**
         * @brief construct dynamic_ndarray from 1D initializer_list
         * 
         * @param initializer 
         */
        explicit dynamic_ndarray(std::initializer_list<value_type> initializer)
        {
            shape_   = shape_type({initializer.size()});
            strides_ = strides();
            numel_   = numel();
            data.resize(numel_);
            size_t i = 0;
            // TODO: find best way to copy
            for (auto v : initializer)
                data[i++] = v;
        }

        /**
         * @brief construct dynamic_ndarray from 1D intializer_list with specified shape
         * 
         * @param initializer 
         * @param shape desired shape
         */
        explicit dynamic_ndarray(std::initializer_list<value_type> initializer, std::vector<size_type> shape)
        {
            shape_ = shape;
            strides_ = strides();
            numel_ = numel();
            data.resize(numel_);
            size_t i = 0;
            assert (initializer.size() == numel_);
            // TODO: find best way to copy
            for (auto v : initializer)
                data[i++] = v;
        }

        /**
         * @brief construct dynamic_ndarray from nested initializer list
         * 
         * @param initializer 
         */
        explicit dynamic_ndarray(std::initializer_list<std::initializer_list<value_type>> initializer)
        {
            shape_   = shape_type({initializer.size(), (initializer.size()?initializer.begin()->size() : 0)});
            strides_ = strides();
            numel_   = numel();
            data.resize(numel_);
            size_t i = 0;
            for (const auto &v : initializer)
                for (const auto &e : v)
                    data[i++] = e;
        }

        // ambiguous call
        // TODO: fix
        // explicit dynamic_ndarray(std::initializer_list<std::initializer_list<std::initializer_list<value_type>>> initializer)
        // {
        //     auto i = initializer.size();
        //     auto j = (initializer.size() ? initializer.begin()->size() : 0);
        //     auto k = (j > 0 ? initializer.begin()->begin()->size() : 0);
        //     shape_ = shape_type({i,j,k});
        //     strides_ = strides();
        //     numel_ = numel();
        //     data.resize(numel_);
        //     size_t idx = 0;
        //     for (auto&& c : initializer)
        //         for (auto&& m : c)
        //             for (auto&& n : m)
        //                 data[idx++] = n;
        // }

        data_type data;
        shape_type shape_;
        stride_type strides_;
        size_type numel_;

        /**
         * @brief return the number of dimension
         * 
         * @return constexpr auto 
         */
        constexpr auto dim() const
        {
            return shape_.size();
        } // dim

        /**
         * @brief return the shape information
         * 
         * @return constexpr auto 
         */
        constexpr auto shape() const
        {
            return shape_;
        } // shape

        /**
         * @brief return the number of elements
         * 
         * @return constexpr auto 
         */
        constexpr auto numel() const
        {
            size_t numel_ = 1;
            for (auto s : shape_)
                numel_ *= s;
            return numel_;
        } // numel

        /**
         * @brief return the strides information
         * 
         * @return constexpr auto 
         */
        constexpr auto strides() const
        {
            auto stride = std::vector<size_t>{};
            stride.resize(dim());
            for (size_t i=0; i<dim(); i++)
                stride[i] = detail::stride(shape_,i);
            return stride;
        } // strides

        /**
         * @brief mutable access to element
         * 
         * @tparam size 
         * @param n 1st index of element to be accessed
         * @param ns the rest of indices of element to be accessed
         * @return constexpr reference 
         * @todo explore more on error handling to make assertion more customizable
         */
        template <typename ...size_types>
        constexpr reference operator()(size_type n, size_types...ns)
        {
            using common_size_t = std::common_type_t<size_type,size_types...>;
            auto indices = std::array<common_size_t,sizeof...(ns)+1>{
                n, static_cast<common_size_t>(ns)...
            };
            assert (dim()==indices.size());
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
         * @todo explore more on error handling to make assertion more customizable
         */
        template <typename ...size_types>
        constexpr const_reference operator()(size_type n, size_types...ns) const
        {
            using common_size_t = std::common_type_t<size_type,size_types...>;
            auto indices = std::array<common_size_t,sizeof...(ns)+1>{
                n, static_cast<common_size_t>(ns)...
            };
            assert (dim()==indices.size());
            auto offset = detail::compute_offset(strides_, indices);
            return data[offset];
        } // operator()

    }; // struct dynamic_ndarray

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

    /**
     * @brief make dynamic_vector can be used with range-based for loop
     * 
     * @tparam T value_type of dynamic_vector, deduced automatically
     * @param v 
     * @return constexpr auto 
     */
    template <typename T>
    constexpr auto begin(dynamic_vector<T>& v)
    {
        return v.data.begin();
    } // constexpr auto begin

    template <typename T>
    constexpr auto begin(const dynamic_vector<T>& v)
    {
        return v.data.begin();
    } // constexpr auto begin

    /**
     * @brief make dynamic_vector can be used with range-based for loop
     * 
     * @tparam T value_type of dynamic_vector, deduced automatically
     * @param v 
     * @return constexpr auto 
     */
    template <typename T>
    constexpr auto end(dynamic_vector<T>& v)
    {
        return v.data.end();
    } // constexpr auto end

    template <typename T>
    constexpr auto end(const dynamic_vector<T>& v)
    {
        return v.data.end();
    } // constexpr auto end

    /** @} */ // end group dynamic
    
} // namespace nmtools::array

namespace nmtools
{
    template <typename T>
    auto row(const array::dynamic_matrix<T>& M, size_t r)
    {
        using return_t = std::vector<T>;
        auto [rows, cols] = M.shape();
        auto ret = return_t(cols);
        for (size_t i=0; i<cols; i++)
            ret[i] = M(r,i);
        return ret;
    }

    /**
     * @brief specialization of vector_size for dynamic_vector
     * 
     * @tparam T element type of dynamic_vector, deduced via template argument deduction
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
     * @tparam T element type of dynamic_matrix, deduced via template argument deduction
     * @param m matrix which size is to be checked
     * @return auto 
     */
    template <typename T>
    auto matrix_size(const array::dynamic_matrix<T>& m)
    {
        return m.shape();
    }

    /**
     * @brief return the shape of dynamic_ndarray
     * 
     * @tparam T element type of dynamic_ndarray, deduced via template argument deduction
     * @param a 
     * @return auto 
     */
    template <typename T>
    auto array_shape(const array::dynamic_ndarray<T>& a)
    {
        return a.shape();
    } // array_shape

    /**
     * @brief return the dimensionality of dynamic_ndarray
     * 
     * @tparam T element type of dynamic_ndarray, deduced via template argument deduction
     * @param a array in which its dim is to be read
     * @return auto 
     */
    template <typename T>
    auto array_dim(const array::dynamic_ndarray<T>& a)
    {
        return a.dim();
    } // array_dim

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
    auto zeros_like(const array::dynamic_vector<T>& v)
    {
        auto ret = array::dynamic_vector<T>(v.size()); 
        return ret;
    }

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

namespace nmtools::traits
{
    /**
     * @ingroup meta
     * 
     */

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

    /**
     * @brief specialization of is_ndarray trait for dynamic_ndarray
     * 
     * @tparam T element type of dynamic_ndarray
     */
    template <typename T>
    struct is_ndarray<array::dynamic_ndarray<T>> : true_type {};

    /**
     * @brief specialization of is_dynamic_ndarray trait for dynamic_ndarray
     * 
     * @tparam T element type of dynamic_ndarray
     */
    template <typename T>
    struct is_dynamic_ndarray<array::dynamic_ndarray<T>> : true_type {};

    /** @} */ // end group traits
    
} // namespace nmtools::traits

#include "nmtools/meta.hpp"
// include fixed array for metafunction specialization
// note: fixed array also include array/utility,
// include here so that dynamic vector_size and matrix_size visible
#include "nmtools/array/fixed.hpp"

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
     * @brief specialization of metafunction get_ndarray_value_type,
     * which tells the value/element type of dynamic_ndarray
     * 
     * @tparam T element type of dynamic_ndarrray, deduced automatically
     */
    template <typename T>
    struct get_ndarray_value_type<array::dynamic_ndarray<T>>
    {
        using type = T;
    };
    /** @} */ // end group meta
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_DYNAMIC_HPP