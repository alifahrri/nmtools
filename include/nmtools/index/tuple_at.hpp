#ifndef NMTOOLS_ARRAY_INDEX_TUPLE_AT_HPP
#define NMTOOLS_ARRAY_INDEX_TUPLE_AT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::index
{
    // TODO: remove
    /**
     * @brief access tuple with runtime value
     *
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
        using value_t = get_element_or_common_type_t<vector_t>;
        static_assert( is_num_v<value_t> || is_index_v<value_t>
            , "unsupported tuple_at, element_type / common_type is not arithmentic"
        );
        auto value = value_t{};

        // @note to check to N since n may be > i
        // @note integral constant is cast-able to its value_type (int,size_t,...)
        if constexpr (has_tuple_size_v<vector_t> && !is_constant_index_v<idx_t>) {
            // simply unroll and assign if match with idx (runtime value)
            constexpr auto N = len_v<vector_t>;
            template_for<N>([&](auto j){
                if (idx==static_cast<idx_t>(j))
                    value = static_cast<value_t>(at(vec,j));
            });
        }
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
        if constexpr (has_tuple_size_v<vector_t>)
            return len_v<vector_t>;
        else return len(vec);
    } // size
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_TUPLE_AT_HPP