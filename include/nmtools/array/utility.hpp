#ifndef NMTOOLS_ARRAY_UTILITY_HPP
#define NMTOOLS_ARRAY_UTILITY_HPP

#include "nmtools/traits.hpp"

/* TODO: should we include array and std::array specialization here? */
#include <array>
#include <tuple>
#include <type_traits>

namespace nmtools {

    using std::size;

    /**
     * @brief access element at i-th index.
     * Dispatch one of the following expression whenever possible (ordered by priority):
     * (1) a.at(i);
     * (2) a[i];
     * (3) a(i);
     * 
     * @tparam Array 
     * @tparam size_type 
     * @param a 
     * @param i 
     * @return constexpr auto& 
     */
    template <typename Array, typename size_type>
    constexpr auto& at(const Array& a, size_type i)
    {
        /* TODO: this fn is returning reference,
            find out how to also support return by value
         */
        using namespace traits;

        static_assert(
            has_at_v<const Array&,size_type>
            || has_square_bracket_v<const Array&,size_type>
            || has_bracket_v<const Array&,size_type>
            /* TODO : meaningful error message here */
        );

        if constexpr (has_at_v<const Array&,size_type>)
            return a.at(i);
        else if constexpr (has_square_bracket_v<const Array&,size_type>)
            return a[i];
        else if constexpr (has_bracket_v<const Array&,size_type>)
            return a(i);
        else {
            /* compile errror */
            static_assert(has_bracket_v<const Array&,size_type>);
        }
    }

    /**
     * @brief access element at i-th index.
     * Dispatch one of the following expression whenever possible (ordered by priority):
     * (1) a.at(i);
     * (2) a[i];
     * (3) a(i);
     * 
     * @tparam Array 
     * @tparam size_type 
     * @param a 
     * @param i 
     * @return constexpr auto& 
     */
    template <typename Array, typename size_type>
    constexpr auto& at(Array& a, size_type i)
    {
        using namespace traits;
        static_assert(
            has_at_v<Array&,size_type>
            || has_square_bracket_v<Array&,size_type>
            || has_bracket_v<Array&,size_type>
            /* TODO : meaningful error message here */
        );

        if constexpr (has_at_v<Array&,size_type>)
            return a.at(i);
        else if constexpr (has_square_bracket_v<Array&,size_type>)
            return a[i];
        else if constexpr (has_bracket_v<Array&,size_type>)
            return a(i);
        else {
            /* compile errror */
            static_assert(has_bracket_v<Array&,size_type>);
        }
    }

    /**
     * @brief access element at (i,j) index.
     * Dispatch the following expression whenever possible (ordered by priority):
     * (1) a.at(i,j);
     * (2) a[i,j];
     * (3) a(i,j);
     * (4) at(at(a,i),j);
     * 
     * @tparam Array 
     * @tparam size_type 
     * @param a 
     * @param i 
     * @param j 
     * @return constexpr auto& 
     */
    template <typename Array, typename size_type>
    constexpr auto& at(const Array& a, size_type i, size_type j)
    {
        /* TODO: this fn is returning reference,
            find out how to also support return by value
         */
        using namespace traits;
        if constexpr (has_at2d_v<const Array&,size_type>)
            return a.at(i,j);
        else if constexpr (has_square_bracket2d_v<const Array&,size_type>)
            return a[i,j];
        else if constexpr (has_bracket2d_v<const Array&,size_type>)
            return a(i,j);
        else {
            return at(at(a,i),j);
        }
    } // constexpr auto& at(const Array& a, size_type i, size_type j)

    /**
     * @brief access element at (i,j) index.
     * Dispatch the following expression whenever possible (ordered by priority):
     * (1) a.at(i,j);
     * (2) a[i,j];
     * (3) a(i,j);
     * (4) at(at(a,i),j);
     * 
     * @tparam Array 
     * @tparam size_type 
     * @param a 
     * @param i 
     * @param j 
     * @return constexpr auto& 
     */
    template <typename Array, typename size_type>
    constexpr auto& at(Array& a, size_type i, size_type j)
    {
        using namespace traits;
        if constexpr (has_at2d_v<Array&,size_type>)
            return a.at(i,j);
        else if constexpr (has_square_bracket2d_v<Array&,size_type>)
            return a[i,j];
        else if constexpr (has_bracket2d_v<Array&,size_type>)
            return a(i,j);
        else {
            return at(at(a,i),j);
        }
    } // constexpr auto& at(Array& a, size_type i, size_type j)

    /**
     * @brief get fixed-matrix's size at compile time.
     * well-formed specialization should have `value` and `value_type`.
     * 
     * @tparam T 
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct fixed_matrix_size {};

    /**
     * @brief specializaton of fixed_matrix_size for nested array
     * 
     * @tparam T 
     * @tparam n 
     * @tparam m 
     */
    template <typename T, size_t Rows, size_t Cols>
    struct fixed_matrix_size<std::array<std::array<T,Cols>,Rows>> 
    {
        static inline constexpr auto value = std::make_pair(Rows,Cols);
        using value_type = decltype(value); // std::pair
    };

    /**
     * @brief helper variable template to get fixed-matrix's size
     * 
     * @tparam M fixed-matrix
     */
    template <typename M>
    inline constexpr auto fixed_matrix_size_v = fixed_matrix_size<M>::value;

    /**
     * @brief get fixed-vector's (math vector, not container) size at compile time
     * 
     * @tparam V 
     * @tparam typename=void 
     */
    template <typename V, typename=void>
    struct fixed_vector_size {};

    /**
     * @brief specializaton of fixed_vector_size for std::array
     * 
     * @tparam T 
     * @tparam N 
     */
    template <typename T, size_t N>
    struct fixed_vector_size<std::array<T,N>> : std::tuple_size<std::array<T,N>> {};

    /**
     * @brief helper variable template for fixed_vector_size
     * 
     * @tparam V 
     */
    template <typename V>
    inline constexpr auto fixed_vector_size_v = fixed_vector_size<V>::value;

    /**
     * @brief generic function to get size of dynamic-matrix, assuming nested vector.
     * May be specialized for custom dynamic-matrix type.
     * 
     * @tparam Matrix matrix-like
     * @param M matrix to check
     * @return std::pair<size_t,size_t> row-col pair
     */
    template <typename Matrix>
    constexpr auto matrix_size(const Matrix& M)
    {
        static_assert(
            traits::is_array2d_v<Matrix>
            /* TODO: meaningful error message */
        );
        /* TODO: check all size for each rows. 
        Nested vector container may have different size at axis 0 */
        return std::make_pair(size(M), size(at(M,0)));
    } // std::pair<size_t,size_t> matrix_size(const Matrix& M)

    /**
     * @brief generic function to get size of dynamic-vector (as in math vector, not container).
     * May be specialized for custom dynamic-matrix type.
     * 
     * @tparam Vector vector-like
     * @param v vector to check
     * @return size_t 
     */
    template <typename Vector>
    constexpr size_t vector_size(const Vector& v)
    {
        static_assert(
            traits::is_array1d_v<Vector>
            /* TODO: meaningful error message */
        );

        return size(v);
    } // size_t matrix_size(const Vector& v)

} // namespace nmtools

/* extend traits for fixed_size_matrix & fixed_size_vector */
namespace nmtools::traits {
    
    /**
     * @brief traits to check if type T is fixed-size matrix
     * 
     * @tparam T type to check
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct is_fixed_size_matrix : std::false_type {};

    /**
     * @brief specialization of is_fixed_size_matrix for true case.
     * Enabled when fixed_matrix_size<T> is well-formed and has value_type member type.
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct is_fixed_size_matrix<T,
        enable_if_t<has_value_type_v<fixed_matrix_size<T>>>
    > : std::true_type {};

    /**
     * @brief helper variable template for is_fixed_size_matrix
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool is_fixed_size_matrix_v = is_fixed_size_matrix<T>::value;

    /**
     * @brief trait to check if type T is fixed-size vector (as in math vector, not container ones).
     * 
     * @tparam T type to check
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct is_fixed_size_vector : std::false_type {};

    /**
     * @brief specialization of is_fixed_size_vector fo true case.
     * Enabled when fixed_vector_size is well-formed and has value_type member type.
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct is_fixed_size_vector<T,
        enable_if_t<has_value_type_v<fixed_vector_size<T>>>
    > : std::true_type {};

    /**
     * @brief helper variable template for is_fixed_size_vector.
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool is_fixed_size_vector_v = is_fixed_size_vector<T>::value;
} // namespace nmtools::traits

#endif // NMTOOLS_ARRAY_UTILITY_HPP