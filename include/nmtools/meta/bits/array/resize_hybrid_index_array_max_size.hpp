#ifndef NMTOOLS_META_BITS_ARRAY_RESIZE_HYBRID_INDEX_ARRAY_MAX_SIZE_HPP
#define NMTOOLS_META_BITS_ARRAY_RESIZE_HYBRID_INDEX_ARRAY_MAX_SIZE_HPP

namespace nmtools::meta
{
    template <typename T, auto N, typename=void>
    struct resize_hybrid_index_array_max_size
    {
        // TODO: use specific type to represent error
        using type = void;
    }; // resize_hybrid_ndarray_max_size

    template <typename T, auto N>
    using resize_hybrid_index_array_max_size_t = type_t<resize_hybrid_index_array_max_size<T,N>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_RESIZE_HYBRID_INDEX_ARRAY_MAX_SIZE_HPP