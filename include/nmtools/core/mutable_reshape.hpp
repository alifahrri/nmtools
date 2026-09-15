#ifndef NMTOOLS_ARRAY_VIEW_MUTABLE_RESHAPE_HPP
#define NMTOOLS_ARRAY_VIEW_MUTABLE_RESHAPE_HPP

#include "nmtools/core/mutable_indexing.hpp"
#include "nmtools/core/reshape.hpp"

namespace nmtools::view
{
    template <typename array_t, typename dst_shape_t>
    constexpr auto mutable_reshape(array_t& array, const dst_shape_t& dst_shape)
    {
        auto src_shape = [&](){
            if constexpr (is_pointer_v<array_t>) {
                return shape<true>(*array);
            } else {
                return shape<true>(array);
            }
        }();
        auto src_size  = [&](){
            if constexpr (is_pointer_v<array_t>) {
                return size<true>(*array);
            } else {
                return size<true>(array);
            }
        }();
        auto indexer = reshaper(src_shape,dst_shape,src_size);
        return mutable_indexing(array,indexer);
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_MUTABLE_RESHAPE_HPP