#ifndef NMTOOLS_META_BITS_ARRAY_HYBRID_INDEX_ARRAY_MAX_SIZE_HPP
#define NMTOOLS_META_BITS_ARRAY_HYBRID_INDEX_ARRAY_MAX_SIZE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief Get the number of maximum size of hybrid index array
     * 
     * Note that this meta fn is intended to return maximum size of index/shape array,
     * hence effectively return the maximum "dimension" of array.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct hybrid_index_array_max_size
    {
        static constexpr auto value = detail::fail_t{};
        using type = detail::fail_t;
    }; // hybrid_index_array_max_size

    template <typename T>
    inline constexpr auto hybrid_index_array_max_size_v = hybrid_index_array_max_size<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_HYBRID_INDEX_ARRAY_MAX_SIZE_HPP