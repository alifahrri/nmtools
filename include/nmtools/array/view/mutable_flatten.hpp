#ifndef NMTOOLS_ARRAY_VIEW_MUTABLE_FLATTEN_HPP
#define NMTOOLS_ARRAY_VIEW_MUTABLE_FLATTEN_HPP

#include "nmtools/array/view/mutable_reshape.hpp"

namespace nmtools::view
{
    template <typename array_t>
    constexpr auto mutable_flatten(array_t& array)
    {
        auto f = [](auto& array){
            auto src_size = size<true>(array);
            constexpr auto SRC_SIZE = meta::to_value_v<decltype(src_size)>;
            if constexpr (!meta::is_fail_v<decltype(SRC_SIZE)>) {
                auto new_shape = nmtools_tuple{src_size};
                return mutable_reshape(array,new_shape);
            } else {
                auto new_shape = nmtools_array{src_size};
                return mutable_reshape(array,new_shape);
            }
        };
        return lift_mutable_indexing(f,array);
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_MUTABLE_FLATTEN_HPP