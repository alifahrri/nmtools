#ifndef NMTOOLS_ARRAY_INDEX_COMPUTE_INDICES_HPP
#define NMTOOLS_ARRAY_INDEX_COMPUTE_INDICES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/index/compute_strides.hpp"

#include <type_traits>
#include <cstddef> // size_t
#include <utility> // integer_sequence
#include <array>
#include <tuple>

namespace nmtools::index
{
    /**
     * @brief inverse operation of compute_offset
     * 
     * @param offset flat indices to be mapped
     * @param shape desired shape
     * @param strides computed strides, should be computed from shape
     * @return constexpr auto 
     */
    template <typename offset_t, typename shape_t, typename strides_t>
    constexpr auto compute_indices(const offset_t& offset, const shape_t& shape, const strides_t& strides)
    {
        constexpr auto shape_is_tuple_or_pair = meta::is_specialization_v<shape_t,std::tuple> || meta::is_specialization_v<shape_t,std::pair>;
        constexpr auto strides_is_tuple_or_pair = meta::is_specialization_v<strides_t,std::tuple> || meta::is_specialization_v<strides_t,std::pair>;
        auto indices = shape;
        if constexpr (shape_is_tuple_or_pair && strides_is_tuple_or_pair)
        {
            constexpr auto n = std::tuple_size_v<shape_t>;
            constexpr auto m = std::tuple_size_v<strides_t>;
            static_assert (m==n
                , "unsupported compute_indices, mismatched shape for shape and strides"
            );
            meta::template_for<n>([&](auto index){
                constexpr auto i = decltype(index)::value;
                std::get<i>(indices) = (offset / std::get<i>(strides)) % std::get<i>(shape);
            });
        }
        else
            for (size_t i=0; i<tuple_size(shape); i++)
                at(indices,i) = (offset / at(strides,i)) % at(shape,i);
        return indices;
    } // compute indices

    /**
     * @brief inverse operation of compute_offset
     * 
     * Offset (flat index) to indices.
     * 
     * @param offset flat indices to be mapped
     * @param shape desired shape
     * @return constexpr auto 
     */
    template <typename offset_t, typename shape_t>
    constexpr auto compute_indices(const offset_t& offset, const shape_t& shape)
    {
        auto strides = compute_strides(shape);
        return compute_indices(offset, shape, strides);
    } // compute_indices
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_COMPUTE_INDICES_HPP