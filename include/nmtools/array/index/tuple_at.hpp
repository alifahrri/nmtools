#ifndef NMTOOLS_ARRAY_INDEX_TUPLE_AT_HPP
#define NMTOOLS_ARRAY_INDEX_TUPLE_AT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"

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
     */
    template <typename vector_t, typename idx_t>
    constexpr auto tuple_at(const vector_t& vec, idx_t idx)
    {
        // std::array type has value_type
        using element_t = meta::get_element_type_t<vector_t>;
        using common_t  = std::conditional_t<
            std::is_void_v<element_t>,
            meta::apply_t<std::common_type,vector_t>,
            element_t
        >;
        static_assert( std::is_arithmetic_v<common_t>
            , "unsupported tuple_at"
        );
        auto value = common_t{};

        if constexpr (meta::has_at_v<vector_t,idx_t>)
            value = at(vec,idx);
        // @note to check to N since n may be > i
        // @note integral constant is cast-able to its value_type (int,size_t,...)
        else
            meta::template_for<std::tuple_size_v<vector_t>>([&](auto j){
                if (idx==j) value = static_cast<common_t>(at(vec,j));
            });
        return value;
    } // tuple_at

    template <typename vector_t>
    constexpr auto tuple_size(const vector_t& vec)
    {
        if constexpr (meta::has_tuple_size_v<vector_t>)
            return std::tuple_size_v<vector_t>;
        else return vec.size();
    } // size
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_TUPLE_AT_HPP