#ifndef NMTOOLS_ARRAY_INDEX_COMPUTE_OFFSET_HPP
#define NMTOOLS_ARRAY_INDEX_COMPUTE_OFFSET_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"

#include <type_traits>
#include <cstddef> // size_t
#include <utility> // integer_sequence
#include <array>
#include <tuple>

namespace nmtools::index
{
    /**
     * @brief compute offset from given indices and computed strides
     * 
     * Indices to offset (flat index).
     * 
     * @param indices container of indices
     * @param strides container of strides
     * @return constexpr auto 
     */
    template <typename indices_t, typename strides_t>
    constexpr auto compute_offset(const indices_t& indices, const strides_t& strides)
    {
        constexpr auto indices_is_fixed = meta::has_tuple_size_v<indices_t> || meta::has_tuple_size_v<indices_t>;
        constexpr auto strides_is_fixed = meta::has_tuple_size_v<strides_t> || meta::has_tuple_size_v<strides_t>;
        size_t offset = 0;
        auto m = tuple_size(indices);
        auto n = tuple_size(strides);
        // @todo static_assert whenever possible
        assert (m==n
            // , "unsupported compute_offset, mismatched shape for indices and strides"
        );
        if constexpr (indices_is_fixed || strides_is_fixed)
        {
            constexpr auto n = [&](){
                if constexpr (indices_is_fixed)
                    return std::tuple_size_v<meta::remove_cvref_t<decltype(indices)>>;
                else return std::tuple_size_v<meta::remove_cvref_t<decltype(strides)>>;
            }();
            meta::template_for<n>([&](auto index){
                offset += tuple_at(strides,index) * tuple_at(indices,index);
            });
        }
        else
            for (size_t i=0; i<m; i++)
                offset += at(strides,i)*at(indices,i);
        return offset;
    } // compute_offset
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_COMPUTE_OFFSET_HPP