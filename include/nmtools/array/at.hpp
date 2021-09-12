#ifndef NMTOOLS_ARRAY_AT_HPP
#define NMTOOLS_ARRAY_AT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"

/* TODO: should we include array and std::array specialization here? */
#include <array>
#include <tuple>
#include <type_traits>

namespace nmtools
{

    /** @addtogroup utility
     * @ingroup array
     * Collections of utility functions for array-like objects
     * @{
     */

    // NOTE: forward declare here since definition at shape.hpp
    // includes this file.
    // this implies the usage of "at" which compile-time branch chooses to call "len"
    // must also include shape.hpp
    template <typename array_t>
    constexpr auto len(const array_t& array);

    template <auto i, typename array_t>
    constexpr decltype(auto) at(const array_t& a)
    {
        // TODO: provide wrapper function nmtools::get, instead of directly use std
        using std::get;
        using index_type = decltype(i);

        static_assert(
            meta::has_square_bracket_v<const array_t&,index_type>
            || meta::has_bracket_v<const array_t&,index_type>
            || meta::has_template_get_v<const array_t&,i>
            , "unsupported at"
        );

        if constexpr (meta::has_template_get_v<const array_t&,i>) {
            return get<i>(a);
        } else if constexpr (meta::has_square_bracket_v<const array_t&,index_type>) {
            return a[i];
        } else if constexpr (meta::has_bracket_v<const array_t&,index_type>) {
            return a(i);
        } else {
            /* compile errror */
            static_assert(meta::has_bracket_v<const array_t&,index_type>);
        }
    } // at

    template <auto i, typename array_t>
    constexpr decltype(auto) at(array_t& a)
    {
        // TODO: provide wrapper function nmtools::get, instead of directly use std
        using std::get;
        using index_type = decltype(i);

        static_assert(
            meta::has_square_bracket_v<array_t&,index_type>
            || meta::has_bracket_v<array_t&,index_type>
            || meta::has_template_get_v<array_t&,i>
            , "unsupported at"
        );

        if constexpr (meta::has_template_get_v<array_t&,i>) {
            return get<i>(a);   
        } else if constexpr (meta::has_square_bracket_v<array_t&,index_type>) {
            return a[i];
        } else if constexpr (meta::has_bracket_v<array_t&,index_type>) {
            return a(i);
        } else {
            /* compile errror */
            static_assert(meta::has_bracket_v<array_t&,index_type>);
        }
    } // at

    using last_type = meta::remove_cvref_t<decltype(Last)>;

    /**
     * @brief access element at i-th index.
     * Dispatch one of the following expression whenever possible (ordered by priority):
     * (1) a.at(i);
     * (2) a[i];
     * (3) a(i);
     * 
     * @tparam array_t 
     * @tparam index_type 
     * @param a 
     * @param i 
     * @return constexpr decltype(auto) 
     */
    template <typename array_t, typename index_type>
    constexpr decltype(auto) at(const array_t& a, index_type i)
    {
        static_assert(
            meta::has_at_v<const array_t&,index_type>
            || meta::has_square_bracket_v<const array_t&,index_type>
            || meta::has_bracket_v<const array_t&,index_type>
            || meta::is_integral_constant_v<index_type>
            || std::is_same_v<index_type,last_type>
            , "unsupported type array_t for at"
        );

        // TODO (wrap std metafunctions): wrap as meta::is_same_v
        if constexpr (std::is_same_v<meta::remove_cvref_t<index_type>,last_type>) {
            const auto N = len(a);
            const auto index = N - 1;
            return at(a,index);
        } else if constexpr (meta::is_constant_index_v<index_type>) {
            // assume constant index has static member value
            constexpr auto index = index_type::value;
            if constexpr (index < 0) {
                const auto N = len(a) + index;
                return at(a,meta::make_unsigned_t<decltype(N)>{N});
            } else {
                return at<index>(a);
            }
        // TODO (wrap std metafunctions): wrap as meta::is_signed_v
        } else if constexpr (std::is_signed_v<index_type>) {
            // NOTE: make index to be unsigned to avoid infinite recursion
            // TODO(wrap std metafunctions): consider to wrap std::make_unsigned_t to meta::make_unsigned_t
            using index_t = std::make_unsigned_t<index_type>;
            if (i < 0) {
                const auto N = len(a);
                // N should be usigned at this point so no infinite recursion,
                // but len may not be returning unsigned hence makes index to be
                // unsigned so cast anyway
                const auto index = N + i; // i < 0
                return at(a,static_cast<index_t>(index));
            } else {
                return at(a,static_cast<index_t>(i));
            }
        } else if constexpr (meta::has_at_v<const array_t&,index_type>) {
            return a.at(i);
        } else if constexpr (meta::has_square_bracket_v<const array_t&,index_type>) {
            return a[i];
        } else if constexpr (meta::has_bracket_v<const array_t&,index_type>) {
            return a(i);
        } else {
            /* compile errror */
            static_assert( meta::has_bracket_v<const array_t&,index_type> );
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
     * @tparam index_type 
     * @param a 
     * @param i 
     * @return constexpr decltype(auto) 
     */
    template <typename array_t, typename index_type>
    constexpr decltype(auto) at(array_t& a, index_type i)
    {
        static_assert(
            meta::has_at_v<array_t&,index_type>
            || meta::has_square_bracket_v<array_t&,index_type>
            || meta::has_bracket_v<array_t&,index_type>
            || meta::is_integral_constant_v<index_type>
            || std::is_same_v<index_type,last_type>
            , "unsupported type array_t for at"
        );

        // TODO (wrap std metafunctions): wrap as meta::is_same_v
        if constexpr (std::is_same_v<meta::remove_cvref_t<index_type>,last_type>) {
            const auto N = len(a);
            const auto index = N - 1;
            return at(a,index);
        } else if constexpr (meta::is_constant_index_v<index_type>) {
            // assume constant index has static member value
            constexpr auto index = index_type::value;
            if constexpr (index < 0) {
                const auto N = len(a) + index;
                return at(a,meta::make_unsigned_t<decltype(N)>{N});
            } else {
                return at<index>(a);
            }
        // TODO (wrap std metafunctions): wrap as meta::is_signed_v
        } else if constexpr (std::is_signed_v<index_type>) {
            // TODO(wrap std metafunctions): consider to wrap std::make_unsigned_t to meta::make_unsigned_t
            using index_t = std::make_unsigned_t<index_type>;
            if (i < 0) {
                const auto N = len(a);
                const auto index = N + i; // i < 0
                return at(a,static_cast<index_t>(index));
            } else {
                return at(a,static_cast<index_t>(i));
            }
        } else if constexpr (meta::has_at_v<array_t&,index_type>) {
            return a.at(i);
        } else if constexpr (meta::has_square_bracket_v<array_t&,index_type>) {
            return a[i];
        } else if constexpr (meta::has_bracket_v<array_t&,index_type>) {
            return a(i);
        } else {
            /* compile errror */
            static_assert(meta::has_bracket_v<array_t&,index_type>);
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
     * @tparam index_type 
     * @param a 
     * @param i 
     * @param j 
     * @return constexpr decltype(auto) 
     */
    template <typename array_t, typename index_type, typename...index_types>
    constexpr decltype(auto) at(const array_t& a, index_type i, index_types...indices)
    {
        if constexpr (meta::has_atnd_v<const array_t&,index_type,index_types...>) {
            return a.at(i,indices...);
        } else if constexpr (meta::has_bracketnd_v<const array_t&,index_type,index_types...>) {
            return a.operator[](i,indices...);
        } else if constexpr (meta::has_funcnd_v<const array_t&,index_type,index_types...>) {
            return a(i,indices...);
        } else {
            return at(at(a,i),indices...);
        }
    } // at(a,...)

    template <auto i, auto j, typename array_t>
    constexpr decltype(auto) at(const array_t& a)
    {
        // TODO: provide wrapper function nmtools::get, instead of directly use std
        using std::get;
        // TODO (wrap std metafunctions): wrap as meta::common_type_t
        using index_type = std::common_type_t<decltype(i),decltype(j)>;
        constexpr auto shape = meta::fixed_matrix_size_v<array_t>;
        constexpr auto rows = get<0>(shape);
        constexpr auto cols = get<1>(shape);
        static_assert(
            meta::is_fixed_size_matrix_v<array_t>
            && (i<rows && j<cols)
        );
        if constexpr (meta::has_square_bracket2d_v<const array_t&,index_type>) {
            return a[{i,j}];
        } else if constexpr (meta::has_bracket2d_v<const array_t&,index_type>) {
            return a(i,j);
        } else {
            return at<j>(at<i>(a));
        }
    } // constexpr decltype(auto) at(const array_t& a, index_type i, index_type j)

    /**
     * @brief access element at (i,j) index.
     * Dispatch the following expression whenever possible (ordered by priority):
     * (1) a.at(i,j);
     * (2) a[i,j];
     * (3) a(i,j);
     * (4) at(at(a,i),j);
     * 
     * @tparam array_t 
     * @tparam index_type 
     * @param a 
     * @param i 
     * @param j 
     * @return constexpr decltype(auto) 
     */
    template <typename array_t, typename index_type, typename...index_types>
    constexpr decltype(auto) at(array_t& a, index_type i, index_types...indices)
    {
        if constexpr (meta::has_atnd_v<array_t&,index_type,index_types...>) {
            return a.at(i,indices...);
        } else if constexpr (meta::has_bracketnd_v<array_t&,index_type,index_types...>) {
            return a.operator[](i,indices...);
        } else if constexpr (meta::has_funcnd_v<array_t&,index_type,index_types...>) {
            return a(i,indices...);
        } else {
            return at(at(a,i),indices...);
        }
    } // at(a,...)

    /** @} */ // end group utility
} // namespace nmtools

#include <utility>

namespace nmtools
{
    namespace detail
    {
        /**
         * @brief actual implementation of apply_at
         * 
         * @tparam array_t array type
         * @tparam type_list packed indices type
         * @tparam Is compile-time index sequence
         * @param array array to be accessed
         * @param indices packed indices to access array
         * @return constexpr decltype(auto) 
         */
        template <typename array_t, typename type_list, size_t...Is>
        constexpr decltype(auto) apply_at_impl(array_t&& array, const type_list& indices, std::index_sequence<Is...>)
        {
            return nmtools::at(std::forward<array_t>(array), std::get<Is>(indices)...);
        } // apply_at_impl
    } //  namespace detail

    /**
     * @brief given indices packed as tuple, unpacks and call at
     * 
     * @tparam array_t 
     * @tparam type_list template template parameter, e.g. std::tuple
     * @tparam size_types template parameter to type_list
     * @param array array to be accessed
     * @param indices packed indices to access array
     * @return constexpr decltype(auto) 
     */
    template <typename array_t, typename indices_t>
    constexpr decltype(auto) apply_at(array_t&& array, const indices_t& indices)
    {
        if constexpr (meta::has_tuple_size_v<indices_t>) {
            // TODO (wrap std metafunctions): wrap as meta::len_v
            // TODO (wrap std metafunctions): wrap as meta::make_index_sequence
            constexpr auto N = std::tuple_size_v<indices_t>;
            using sequence_t = std::make_index_sequence<N>;
            return detail::apply_at_impl(std::forward<array_t>(array),indices,sequence_t{});
        }
        else return at(std::forward<array_t>(array), indices);
    } // apply_at
} // namespace nmtools

#endif // NMTOOLS_ARRAY_AT_HPP