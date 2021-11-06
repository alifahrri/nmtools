#ifndef NMTOOLS_META_BITS_ARRAY_HYBRID_NDARRAY_MAX_SIZE_HPP
#define NMTOOLS_META_BITS_ARRAY_HYBRID_NDARRAY_MAX_SIZE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct hybrid_ndarray_max_size
    {
        static constexpr auto value = detail::fail_t{};
        using type = detail::fail_t;
    }; // hybrid_ndarray_max_size

    template <typename T>
    inline constexpr auto hybrid_ndarray_max_size_v = hybrid_ndarray_max_size<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_HYBRID_NDARRAY_MAX_SIZE_HPP