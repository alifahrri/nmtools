#ifndef NMTOOLS_ARRAY_VECTOR_FIXED_HPP
#define NMTOOLS_ARRAY_VECTOR_FIXED_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp" // meta::fixed_matrix_size etc.

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
        : std::tuple_size<typename array::fixed_vector<T,N>::data_type> {};

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

} // namespace nmtools

#include "nmtools/traits.hpp"

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

    /** @} */ // end group meta
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VECTOR_FIXED_HPP