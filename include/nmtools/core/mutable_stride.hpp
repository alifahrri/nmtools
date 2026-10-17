#ifndef NMTOOLS_ARRAY_VIEW_MUTABLE_STRIDE_HPP
#define NMTOOLS_ARRAY_VIEW_MUTABLE_STRIDE_HPP

#include "nmtools/core/mutable_indexing.hpp"
#include "nmtools/core/stride.hpp"

namespace nmtools::view
{
    template <typename array_t, typename shape_t, typename striding_t>
    constexpr auto mutable_stride(array_t& array, const shape_t& shape, const striding_t& striding)
    {
        auto src_shape = [&](){
            if constexpr (is_pointer_v<array_t>) {
                return nmtools::shape<true>(*array);
            } else {
                return nmtools::shape<true>(array);
            }
        }();
        auto indexer = strider(src_shape,shape,striding,none_t{});
        return mutable_indexing(array,indexer);
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_MUTABLE_STRIDE_HPP
