#ifndef NMTOOLS_ARRAY_UTILITY_AT_HPP
#define NMTOOLS_ARRAY_UTILITY_AT_HPP

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

    template <auto i, typename array_t>
    constexpr decltype(auto) at(const array_t& a)
    {
        /* TODO: this fn is returning reference,
            find out how to also support return by value
         */
        using namespace meta;
        using size_type = decltype(i);

        static_assert(
            has_square_bracket_v<const array_t&,size_type>
            || has_bracket_v<const array_t&,size_type>
            || has_template_get_v<const array_t&,i>
            , "unsupported at"
        );

        if constexpr (has_template_get_v<const array_t&,i>)
            return get<i>(a);
        // fallback
        else if constexpr (has_square_bracket_v<const array_t&,size_type>)
            return a[i];
        else if constexpr (has_bracket_v<const array_t&,size_type>)
            return a(i);
        else {
            /* compile errror */
            static_assert(has_bracket_v<const array_t&,size_type>);
        }
    } // at

    template <auto i, typename array_t>
    constexpr decltype(auto) at(array_t& a)
    {
        /* TODO: this fn is returning reference,
            find out how to also support return by value
         */
        using namespace meta;
        using size_type = decltype(i);

        static_assert(
            has_square_bracket_v<array_t&,size_type>
            || has_bracket_v<array_t&,size_type>
            || has_template_get_v<array_t&,i>
            , "unsupported at"
        );

        if constexpr (has_template_get_v<array_t&,i>)
            return get<i>(a);
        // fallback
        else if constexpr (has_square_bracket_v<array_t&,size_type>)
            return a[i];
        else if constexpr (has_bracket_v<array_t&,size_type>)
            return a(i);
        else {
            /* compile errror */
            static_assert(has_bracket_v<array_t&,size_type>);
        }
    } // at

    /**
     * @brief access element at i-th index.
     * Dispatch one of the following expression whenever possible (ordered by priority):
     * (1) a.at(i);
     * (2) a[i];
     * (3) a(i);
     * 
     * @tparam array_t 
     * @tparam size_type 
     * @param a 
     * @param i 
     * @return constexpr decltype(auto) 
     */
    template <typename array_t, typename size_type>
    constexpr decltype(auto) at(const array_t& a, size_type i)
    {
        /* TODO: this fn is returning reference,
            find out how to also support return by value
         */
        using namespace meta;

        static_assert(
            has_at_v<const array_t&,size_type>
            || has_square_bracket_v<const array_t&,size_type>
            || has_bracket_v<const array_t&,size_type>
            || is_integral_constant_v<size_type>
            , "unsupported type array_t for at"
        );

        if constexpr (has_at_v<const array_t&,size_type>)
            return a.at(i);
        else if constexpr (has_square_bracket_v<const array_t&,size_type>)
            return a[i];
        else if constexpr (has_bracket_v<const array_t&,size_type>)
            return a(i);
        else if constexpr (is_integral_constant_v<size_type>)
            return at<size_type::value>(a);
        else {
            /* compile errror */
            static_assert(has_bracket_v<const array_t&,size_type>);
        }
    } // at

    /**
     * @brief access element at i-th index.
     * Dispatch one of the following expression whenever possible (ordered by priority):
     * (1) a.at(i);
     * (2) a[i];
     * (3) a(i);
     * 
     * @tparam array_t 
     * @tparam size_type 
     * @param a 
     * @param i 
     * @return constexpr decltype(auto) 
     */
    template <typename array_t, typename size_type>
    constexpr decltype(auto) at(array_t& a, size_type i)
    {
        using namespace meta;
        static_assert(
            has_at_v<array_t&,size_type>
            || has_square_bracket_v<array_t&,size_type>
            || has_bracket_v<array_t&,size_type>
            || is_integral_constant_v<size_type>
            , "unsupported type array_t for at"
        );

        if constexpr (has_at_v<array_t&,size_type>)
            return a.at(i);
        else if constexpr (has_square_bracket_v<array_t&,size_type>)
            return a[i];
        else if constexpr (has_bracket_v<array_t&,size_type>)
            return a(i);
        else if constexpr (is_integral_constant_v<size_type>)
            return at<size_type::value>(a);
        else {
            /* compile errror */
            static_assert(has_bracket_v<array_t&,size_type>);
        }
    } // constexpr decltype(auto) at

    /**
     * @brief access element at (i,j) index.
     * Dispatch the following expression whenever possible (ordered by priority):
     * (1) a.at(i,j);
     * (2) a[i,j];
     * (3) a(i,j);
     * (4) at(at(a,i),j);
     * 
     * @tparam array_t 
     * @tparam size_type 
     * @param a 
     * @param i 
     * @param j 
     * @return constexpr decltype(auto) 
     */
    template <typename array_t, typename size_type, typename...size_types>
    constexpr decltype(auto) at(const array_t& a, size_type i, size_types...indices)
    {
        if constexpr (meta::has_atnd_v<const array_t&,size_type,size_types...>)
            return a.at(i,indices...);
        else if constexpr (meta::has_bracketnd_v<const array_t&,size_type,size_types...>)
            return a.operator[](i,indices...);
        else if constexpr (meta::has_funcnd_v<const array_t&,size_type,size_types...>)
            return a(i,indices...);
        else
            return at(at(a,i),indices...);
    } // at(a,...)

    template <auto i, auto j, typename array_t>
    constexpr decltype(auto) at(const array_t& a)
    {
        /* TODO: this fn is returning reference,
            find out how to also support return by value
         */
        using namespace meta;
        using size_type = std::common_type_t<decltype(i),decltype(j)>;
        constexpr auto shape = meta::fixed_matrix_size_v<array_t>;
        constexpr auto rows = get<0>(shape);
        constexpr auto cols = get<1>(shape);
        static_assert(
            is_fixed_size_matrix_v<array_t>
            && (i<rows && j<cols)
        );
        if constexpr (has_square_bracket2d_v<const array_t&,size_type>)
            return a[i,j];
        else if constexpr (has_bracket2d_v<const array_t&,size_type>)
            return a(i,j);
        else {
            return at<j>(at<i>(a));
        }
    } // constexpr decltype(auto) at(const array_t& a, size_type i, size_type j)

    /**
     * @brief access element at (i,j) index.
     * Dispatch the following expression whenever possible (ordered by priority):
     * (1) a.at(i,j);
     * (2) a[i,j];
     * (3) a(i,j);
     * (4) at(at(a,i),j);
     * 
     * @tparam array_t 
     * @tparam size_type 
     * @param a 
     * @param i 
     * @param j 
     * @return constexpr decltype(auto) 
     */
    template <typename array_t, typename size_type, typename...size_types>
    constexpr decltype(auto) at(array_t& a, size_type i, size_types...indices)
    {
        if constexpr (meta::has_atnd_v<array_t&,size_type,size_types...>)
            return a.at(i,indices...);
        else if constexpr (meta::has_bracketnd_v<array_t&,size_type,size_types...>)
            return a.operator[](i,indices...);
        else if constexpr (meta::has_funcnd_v<array_t&,size_type,size_types...>)
            return a(i,indices...);
        else
            return at(at(a,i),indices...);
    } // at(a,...)

    /** @} */ // end group utility
} // namespace nmtools

#endif // NMTOOLS_ARRAY_UTILITY_AT_HPP