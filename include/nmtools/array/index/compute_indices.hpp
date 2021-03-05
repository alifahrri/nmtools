#ifndef NMTOOLS_ARRAY_INDEX_COMPUTE_INDICES_HPP
#define NMTOOLS_ARRAY_INDEX_COMPUTE_INDICES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
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
     * @brief specific tag to resolve op type of compute_indices
     * 
     */
    struct compute_indices_t {};

    namespace impl
    {
        template <typename indices_t, typename offset_t, typename shape_t, typename strides_t>
        constexpr auto compute_indices(indices_t& indices, const offset_t& offset, const shape_t& shape, const strides_t& strides)
        {
            constexpr auto shape_has_tuple_size = meta::has_tuple_size_v<shape_t>;
            constexpr auto strides_has_tuple_size = meta::has_tuple_size_v<strides_t>;

            if constexpr (shape_has_tuple_size && strides_has_tuple_size)
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
                for (size_t i=0; i<len(shape); i++)
                    at(indices,i) = (offset / at(strides,i)) % at(shape,i);
        } // compute_indices
    } // namespace impl

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

        using return_t = meta::resolve_optype_t<compute_indices_t,offset_t,shape_t,strides_t>;
        auto indices = return_t{};
        if constexpr (meta::is_resizeable_v<return_t>)
            indices.resize(size(shape));

        impl::compute_indices(indices, offset, shape, strides);

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

namespace nmtools::meta
{
    template <typename offset_t, typename shape_t, typename strides_t>
    struct resolve_optype< void, index::compute_indices_t, offset_t, shape_t, strides_t >
    {
        using type = transform_bounded_array_t<tuple_to_array_t<shape_t>>;
    }; // resolve_optype

    template <typename offset_t, typename shape_t>
    struct resolve_optype< void, index::compute_indices_t, offset_t, shape_t >
    {
        using type = transform_bounded_array_t<tuple_to_array_t<shape_t>>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_COMPUTE_INDICES_HPP