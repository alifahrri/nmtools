/**
 * @file apply_at.hpp
 * @author Fahri Ali Rahman (ali.rahman.fahri@gmail.com)
 * @brief Contains definition of apply_at
 * @version 0.1
 * @date 2020-11-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef NMTOOLS_ARRAY_UTILITY_APPLY_AT_HPP
#define NMTOOLS_ARRAY_UTILITY_APPLY_AT_HPP

#include "nmtools/array/utility/at.hpp"

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
        static_assert (meta::has_tuple_size_v<indices_t> || meta::has_atnd_v<array_t,indices_t>
            , "unsupported indices for apply_at, expects tuple_size_v<indices_t> or array.at(indices) is well-formed"
        );
        if constexpr (meta::has_tuple_size_v<indices_t>) {
            constexpr auto N = std::tuple_size_v<indices_t>;
            using sequence_t = std::make_index_sequence<N>;
            return detail::apply_at_impl(std::forward<array_t>(array),indices,sequence_t{});
        }
        // else return at(array, indices);
        else return array.at(indices);
    } // apply_at
} // namespace nmtools

#endif // NMTOOLS_ARRAY_UTILITY_APPLY_AT_HPP