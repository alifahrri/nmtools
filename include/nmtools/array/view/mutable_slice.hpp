#ifndef NMTOOLS_ARRAY_VIEW_MUTABLE_SLICE_HPP
#define NMTOOLS_ARRAY_VIEW_MUTABLE_SLICE_HPP

#include "nmtools/array/view/mutable_indexing.hpp"
#include "nmtools/array/view/slice.hpp"

namespace nmtools::view
{
    template <typename array_t, typename slices_t>
    constexpr auto apply_mutable_slice(array_t& array, const slices_t& slices)
    {
        auto src_shape = shape<true>(array);
        auto src_size  = size<true>(array);
        auto indexer   = slicer(src_shape,slices,src_size);
        return mutable_indexing(array,indexer);
    }

    template <typename array_t, typename...slices_t>
    constexpr auto mutable_slice(array_t& array, slices_t...slices)
    {
        auto slices_pack = nmtools_tuple{slices...};
        return apply_mutable_slice(array,slices_pack);
    }
}

#endif // NMTOOLS_ARRAY_VIEW_MUTABLE_SLICE_HPP