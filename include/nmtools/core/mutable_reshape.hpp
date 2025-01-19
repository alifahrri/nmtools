#ifndef NMTOOLS_ARRAY_VIEW_MUTABLE_RESHAPE_HPP
#define NMTOOLS_ARRAY_VIEW_MUTABLE_RESHAPE_HPP

#include "nmtools/core/mutable_indexing.hpp"
#include "nmtools/core/reshape.hpp"

namespace nmtools::view
{
    template <typename array_t, typename dst_shape_t>
    constexpr auto mutable_reshape(array_t& array, const dst_shape_t& dst_shape)
    {
        auto src_shape = shape<true>(array);
        auto src_size  = size<true>(array);
        auto indexer   = reshaper(src_shape,dst_shape,src_size);
        return mutable_indexing(array,indexer);
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_MUTABLE_RESHAPE_HPP