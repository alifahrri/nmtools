#ifndef NMTOOLS_ARRAY_FIXED_HPP
#define NMTOOLS_ARRAY_FIXED_HPP

#include "nmtools/array/utility.hpp"
#include "nmtools/meta.hpp"
#include <array>

namespace nmtools::array {

    /**
     * @brief some implementation details for array impl
     * 
     */
    namespace detail
    {
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
         * @brief create array of reference from a,
         * 
         * @tparam T value_type of a
         * @tparam N size of a
         * @tparam I index sequence for fold-expression
         * @param a array to take reference of
         * @param offset starting index, e.g. a[I+offset]...
         * @return auto array of reference
         */
        template <typename T, size_t N, size_t ...I>
        constexpr auto make_array_ref(std::array<T,N> &a, std::integer_sequence<size_t, I...>, size_t offset=0)
        {
            using array_ref_t = array_ref<T,sizeof...(I)>;
            return array_ref_t{a[I+offset]...};
        }

        /**
         * @brief create array of reference from a,
         * 
         * @tparam T value_type of a
         * @tparam N size of a
         * @tparam I index sequence for fold-expression
         * @param a array to take reference of
         * @param offset starting index, e.g. a[I+offset]...
         * @return auto array of reference
         */
        template <typename T, size_t N, size_t ...I>
        constexpr auto make_array_ref(const std::array<T,N> &a, std::integer_sequence<size_t, I...>, size_t offset=0)
        {
            using array_ref_t = array_ref<const T,sizeof...(I)>;
            return array_ref_t{a[I+offset]...};
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
        constexpr auto make_array_ref(std::array<T,N> &a, size_constant<new_size>, size_t offset=0)
        {
            return make_array_ref(a, std::make_index_sequence<new_size>{}, offset);
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
            return make_array_ref(a, std::make_index_sequence<new_size>{}, offset);
        }

        /**
         * @brief create array of refrerence from a with same size as a, starting from offset. 
         * 
         * @tparam T value_type of a
         * @tparam N size of a
         * @param a array to take reference of
         * @param offset starting index, e.g. a[I+offset]...
         * @return auto array of reference
         */
        template <typename T, size_t N>
        constexpr auto make_array_ref(std::array<T,N> &a, size_t offset=0)
        {
            return make_array_ref(a, std::make_index_sequence<N>{}, offset);
        }

        /**
         * @brief create array of refrerence from a with same size as a, starting from offset. 
         * 
         * @tparam T value_type of a
         * @tparam N size of a
         * @param a array to take reference of
         * @param offset starting index, e.g. a[I+offset]...
         * @return auto array of reference
         */
        template <typename T, size_t N>
        constexpr auto make_array_ref(const std::array<T,N> &a, size_t offset=0)
        {
            return make_array_ref(a, std::make_index_sequence<N>{}, offset);
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
        using data_type = std::array<T,N>;
        using value_type = T;
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
    };

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
    };
    
    
} // namespace nmtools::array

namespace nmtools
{
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
} // namespace nmtools

namespace nmtools::traits
{
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

} // namespace nmtooclls::traits

namespace nmtools::meta
{
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
}

#endif // NMTOOLS_ARRAY_FIXED_HPP