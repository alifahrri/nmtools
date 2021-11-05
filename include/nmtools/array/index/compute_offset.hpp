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
        auto m = len(indices);
        auto n = len(strides);
        // TODO: use optional instead
        // TODO: static_assert whenever possible
        assert (m==n
            // , "unsupported compute_offset, mismatched shape for indices and strides"
        );
        if constexpr (meta::is_fixed_index_array_v<indices_t> || meta::is_fixed_index_array_v<strides_t>)
        {
            constexpr auto n = [&](){
                if constexpr (meta::is_fixed_index_array_v<indices_t>)
                    return meta::len_v<meta::remove_cvref_t<decltype(indices)>>;
                else return meta::len_v<meta::remove_cvref_t<decltype(strides)>>;
            }();
            meta::template_for<n>([&](auto index){
                offset += at(strides,index) * at(indices,index);
            });
        }
        else
            for (size_t i=0; i<m; i++)
                offset += at(strides,i)*at(indices,i);
        return offset;
    } // compute_offset
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_COMPUTE_OFFSET_HPP