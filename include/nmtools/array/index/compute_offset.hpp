#ifndef NMTOOLS_ARRAY_INDEX_COMPUTE_OFFSET_HPP
#define NMTOOLS_ARRAY_INDEX_COMPUTE_OFFSET_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/assert.hpp"

namespace nmtools::index
{
    // TODO: cleanup index functions
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
        size_t offset = 0;
        [[maybe_unused]] auto m = len(indices);
        [[maybe_unused]] auto n = len(strides);
        constexpr auto N = meta::len_v<indices_t>;
        constexpr auto M = meta::len_v<strides_t>;
        if constexpr ((N > 0) && (M > 0)) {
            meta::template_for<N>([&](auto index){
                offset += static_cast<size_t>(at(strides,index)) * static_cast<size_t>(at(indices,index));
            });
        } else {
            for (size_t i=0; i<m; i++) {
                offset += static_cast<size_t>(at(strides,i)) * static_cast<size_t>(at(indices,i));
            }
        }
        return offset;
    } // compute_offset
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_COMPUTE_OFFSET_HPP