#ifndef NMTOOLS_ARRAY_INDEX_TUPLE_AT_HPP
#define NMTOOLS_ARRAY_INDEX_TUPLE_AT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"

#include <type_traits>
#include <cstddef> // size_t
#include <utility> // integer_sequence
#include <array>
#include <tuple>

namespace nmtools::index
{
    /**
     * @brief access tuple with runtime value
     *
     * Also works with std::array or std::vector.
     * 
     * @tparam vector_t 
     * @tparam idx_t 
     * @param vec 
     * @param idx 
     * @return constexpr auto 
     * @todo remove, use at with static index
     */
    template <typename vector_t, typename idx_t>
    constexpr auto tuple_at(const vector_t& vec, idx_t idx)
    {
        using value_t = meta::get_element_or_common_type_t<vector_t>;
        static_assert( std::is_arithmetic_v<value_t> || meta::is_index_v<value_t>
            , "unsupported tuple_at, element_type / common_type is not arithmentic"
        );
        auto value = value_t{};

        // @note to check to N since n may be > i
        // @note integral constant is cast-able to its value_type (int,size_t,...)
        if constexpr (meta::has_tuple_size_v<vector_t>)
            meta::template_for<std::tuple_size_v<vector_t>>([&](auto j){
                if (idx==j) value = static_cast<value_t>(at(vec,j));
            });
        else value = at(vec,idx);
        return value;
    } // tuple_at

    /**
     * @brief Get the size of 1d array, including tuple
     * 
     * @tparam vector_t 
     * @param vec 
     * @return constexpr auto 
     * @todo remove, use len instead
     */
    template <typename vector_t>
    constexpr auto tuple_size(const vector_t& vec)
    {
        if constexpr (meta::has_tuple_size_v<vector_t>)
            return std::tuple_size_v<vector_t>;
        else return vector_size(vec);
    } // size
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_TUPLE_AT_HPP