#ifndef NMTOOLS_ARRAY_VIEW_FLATTEN_HPP
#define NMTOOLS_ARRAY_VIEW_FLATTEN_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/array/view/reshape.hpp"

namespace nmtools::view
{
    template <typename array_t>
    constexpr auto flatten(const array_t& array)
    {
        auto f = [](const auto& array){
            auto src_size = size<true>(array);
            constexpr auto SRC_SIZE = meta::to_value_v<decltype(src_size)>;
            if constexpr (!meta::is_fail_v<decltype(SRC_SIZE)>) {
                auto new_shape = nmtools_tuple{src_size};
                return view::reshape(array,new_shape);
            } else {
                auto new_shape = nmtools_array{src_size};
                return view::reshape(array,new_shape);
            }
        };
        return lift_indexing(f,array);
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_FLATTEN_HPP