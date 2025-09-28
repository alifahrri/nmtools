#ifndef NMTOOLS_ARRAY_MUTABLE_TILING_WINDOW_HPP
#define NMTOOLS_ARRAY_MUTABLE_TILING_WINDOW_HPP

#include "nmtools/meta.hpp"
#include "nmtools/core/mutable_indexing.hpp"
#include "nmtools/array/tiling_window.hpp"

namespace nmtools::view
{
    template <typename array_t
        , typename tile_shape_t
        , typename axis_t=none_t>
    constexpr auto mutable_tiling_window(array_t& array
        , const tile_shape_t& tile_shape
        , const axis_t& axis=axis_t{})
    {
        auto src_shape = shape<true>(array);
        auto indexer   = tiling_window_indexer(src_shape,tile_shape,axis);
        return mutable_indexing(array,indexer);
    }
}

#endif // NMTOOLS_ARRAY_MUTABLE_TILING_WINDOW_HPP