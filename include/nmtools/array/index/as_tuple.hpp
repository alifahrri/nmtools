#ifndef NMTOOLS_ARRAY_INDEX_AS_TUPLE_HPP
#define NMTOOLS_ARRAY_INDEX_AS_TUPLE_HPP

#include <type_traits>
#include <cstddef> // size_t
#include <utility> // integer_sequence
#include <array>
#include <tuple>

#include "nmtools/meta.hpp"

namespace nmtools::index
{
    /**
     * @addtogroup index
     * @{
     */

    /**
     * @brief create tuple from array
     * 
     * @tparam array_t array type, `std::get<Is>(array)` must be well-formed
     * @tparam Is index sequence
     * @param array array to be converted
     * @return constexpr decltype(auto) 
     */
    template <typename array_t, size_t...Is>
    constexpr decltype(auto) as_tuple(const array_t& array, std::index_sequence<Is...>)
    {
        return std::tuple{std::get<Is>(array)...};
    } // as_tuple

    /**
     * @brief create tuple from array
     * 
     * @tparam array_t tempate template parameter for corresponding array
     * @tparam T value type of the array
     * @tparam N size of the array
     * @param array array to be converted
     * @return constexpr auto 
     */
    template <template <typename,size_t> typename array_t, typename T, size_t N>
    constexpr auto as_tuple(const array_t<T,N>& array)
    {
        using indices_t = std::make_index_sequence<N>;
        return as_tuple(array,indices_t{});
    } // as_tuple
    
    /** @} */ // end group index
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_AS_TUPLE_HPP