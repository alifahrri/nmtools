#ifndef NMTOOLS_ARRAY_VECTOR_FIXED_HPP
#define NMTOOLS_ARRAY_VECTOR_FIXED_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp" // meta::fixed_matrix_size etc.
#include "nmtools/array/utility/at.hpp"

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
        using data_type = T[N];
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
            return N;
        }

        template <typename array_t, typename=std::enable_if_t<meta::is_array1d_v<array_t>>>
        decltype(auto) operator=(const array_t& array)
        {
            if constexpr (meta::is_fixed_size_vector_v<array_t>)
                static_assert (meta::fixed_vector_size_v<array_t> == N, "size mismatch for operator= for fixed_vector");
            else assert ( vector_size(array) == N
                // , "size mismatch for operator= for fixed_vector"
            );
            for (size_t i=0; i<N; i++)
                data[i] = at(array, i);
            return *this;
        } // operator=
    }; // struct fixed_vector

    template <typename T, size_t N>
    fixed_vector(T(&&a)[N]) -> fixed_vector<T,N>;

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
        return v.data;
    } // constexpr auto begin

    template <typename T, size_t N>
    constexpr auto begin(const fixed_vector<T,N>& v)
    {
        return v.data;
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
        return v.data + N;
    } // constexpr auto end

    template <typename T, size_t N>
    constexpr auto end(const fixed_vector<T,N>& v)
    {
        return v.data + N;
    } // constexpr auto end

    template <typename T, size_t N>
    constexpr auto size(const fixed_vector<T,N>& v)
    {
        return N;
    } // size

    template <typename T, typename=void>
    struct is_fixed_vector : std::false_type {};

    template <typename T, size_t N>
    struct is_fixed_vector<fixed_vector<T,N>> : std::true_type {};

    template <typename T>
    inline constexpr auto is_fixed_vector_v = is_fixed_vector<T>::value;

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

    /** @} */ // end group utility

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
     * @brief specialization of fixed_vector for meta::fixed_vector_size array traits.
     * 
     * @tparam T 
     * @tparam N 
     */
    template <typename T, size_t N>
    struct meta::fixed_vector_size<array::fixed_vector<T,N>>
        : std::integral_constant<size_t,N> {};

    /**
     * @brief specialization of fixed_vector for meta::fixed_ndarray_shape array traits.
     * 
     * @tparam T element type of fixed_vector
     * @tparam N number of elements of fixed_vector
     */
    template <typename T, size_t N>
    struct meta::fixed_ndarray_shape<array::fixed_vector<T,N>>
    {
        static inline constexpr auto value = std::make_tuple(N);
        using value_type = decltype(value);
    };

    /**
     * @brief specialize replace_element_type for array::fixed_vector
     * 
     * @tparam T 
     * @tparam U 
     * @tparam N 
     */
    template <typename T, typename U, size_t N>
    struct meta::replace_element_type<array::fixed_vector<T,N>,U,std::enable_if_t<std::is_arithmetic_v<U>>>
    {
        using type = array::fixed_vector<U,N>;
    };

} // namespace nmtools

namespace nmtools::meta
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

    /** @} */ // end group traits
} // namespace nmtooclls::traits

namespace nmtools::meta
{
    /**
     * @ingroup meta
     * @{
     */

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
     * @brief fixed_vector is fixed index array if T is index.
     * 
     * @tparam T 
     * @tparam N 
     */
    template <typename T, size_t N>
    struct is_fixed_index_array< array::fixed_vector<T,N>
        , std::enable_if_t<is_index_v<T>>
    > : std::true_type {};

    template <typename T, size_t N>
    struct fixed_index_array_size< array::fixed_vector<T,N>
        , std::enable_if_t<is_index_v<T>>
    >
    {
        static constexpr auto value = N;
        using type = remove_cvref_t<decltype(value)>;
    };

    /** @} */ // end group meta
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VECTOR_FIXED_HPP