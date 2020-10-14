#ifndef NMTOOLS_ARRAY_UTILITY_AT_HPP
#define NMTOOLS_ARRAY_UTILITY_AT_HPP

#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

/* TODO: should we include array and std::array specialization here? */
#include <array>
#include <tuple>
#include <type_traits>

namespace nmtools {

    /** @addtogroup utility
     * @ingroup array
     * Collections of utility functions for array-like objects
     * @{
     */

    using std::size;
    using std::get;

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
            || has_bracket_v<const Array&,size_type>,
            "unsupported type Array for at"
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

    template <auto i, typename Array>
    constexpr auto& at(const Array& a)
    {
        /* TODO: this fn is returning reference,
            find out how to also support return by value
         */
        using namespace traits;
        using size_type = decltype(i);

        static_assert(
            has_square_bracket_v<const Array&,size_type>
            || has_bracket_v<const Array&,size_type>
            /* TODO : meaningful error message here */
        );
        static_assert(
            is_fixed_size_vector_v<Array>
            && (i<fixed_vector_size_v<Array>)
        );

        if constexpr (has_square_bracket_v<const Array&,size_type>)
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
    } // constexpr auto& at

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
    template <typename Array, typename size_type, typename...size_types>
    constexpr auto& at(const Array& a, size_type i, size_types...indices)
    {
        if constexpr (traits::has_atnd_v<const Array&,size_type,size_types...>)
            return a.at(i,indices...);
        else if constexpr (traits::has_bracketnd_v<const Array&,size_type,size_types...>)
            return a.operator[](i,indices...);
        else if constexpr (traits::has_funcnd_v<const Array&,size_type,size_types...>)
            return a(i,indices...);
        else
            return at(at(a,i),indices...);
    } // at(a,...)

    template <auto i, auto j, typename Array>
    constexpr auto& at(const Array& a)
    {
        /* TODO: this fn is returning reference,
            find out how to also support return by value
         */
        using namespace traits;
        using size_type = std::common_type_t<decltype(i),decltype(j)>;
        constexpr auto shape = fixed_matrix_size_v<Array>;
        constexpr auto rows = get<0>(shape);
        constexpr auto cols = get<1>(shape);
        static_assert(
            is_fixed_size_matrix_v<Array>
            && (i<rows && j<cols)
        );
        if constexpr (has_square_bracket2d_v<const Array&,size_type>)
            return a[i,j];
        else if constexpr (has_bracket2d_v<const Array&,size_type>)
            return a(i,j);
        else {
            return at<j>(at<i>(a));
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
    template <typename Array, typename size_type, typename...size_types>
    constexpr auto& at(Array& a, size_type i, size_types...indices)
    {
        if constexpr (traits::has_atnd_v<Array&,size_type,size_types...>)
            return a.at(i,indices...);
        else if constexpr (traits::has_bracketnd_v<Array&,size_type,size_types...>)
            return a.operator[](i,indices...);
        else if constexpr (traits::has_funcnd_v<Array&,size_type,size_types...>)
            return a(i,indices...);
        else
            return at(at(a,i),indices...);
    } // at(a,...)

    /** @} */ // end group utility
} // namespace nmtools

#endif // NMTOOLS_ARRAY_UTILITY_AT_HPP