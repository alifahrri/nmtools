#ifndef NMTOOLS_ARRAY_INDEX_SHAPE_TILE_HPP
#define NMTOOLS_ARRAY_INDEX_SHAPE_TILE_HPP

// TODO: move to index/tile.hpp

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/index/tuple_at.hpp"

#include <algorithm> // max

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type of shape_tile op
     * 
     */
    struct shape_tile_t {};

    /**
     * @brief comput the resulting shape for tile view
     * 
     * @tparam shape_t 
     * @tparam reps_t 
     * @param shape the shape of input array
     * @param reps number of repetitions foe each axis
     * @return constexpr auto 
     */
    template <typename shape_t, typename reps_t>
    constexpr auto shape_tile(const shape_t& shape, const reps_t& reps)
    {
        using return_t = meta::resolve_optype_t<shape_tile_t,shape_t,reps_t>;
        auto ret = return_t {};

        auto m = tuple_size(shape);
        auto n = tuple_size(reps);
        auto s = std::max(m,n);

        if constexpr (meta::is_resizeable_v<return_t>)
            ret.resize(s);

        auto shape_tile_impl = [&](auto i){
            using idx_t = std::make_signed_t<decltype(m-i-1)>;
            idx_t ai = m - i - 1;
            idx_t bi = n - i - 1;
            idx_t si = s - i - 1;
            if (ai < 0)
                at(ret,si) = tuple_at(reps,bi);
            else if (bi < 0)
                at(ret,si) = tuple_at(shape,ai);
            else {
                auto a = tuple_at(shape,ai);
                auto b = tuple_at(reps,bi);
                at(ret,si) = a * b;
            }
        }; // shape_tile_impl

        // TODO: consider to unroll when possible

        for (size_t i=0; i<(size_t)len(ret); i++)
            shape_tile_impl(i);

        return ret;
    } // shape_tile
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        struct SHAPE_TILE_ERROR : detail::fail_t {};
    } // namespace error
    
    /**
     * @brief resolve return type for index::shape_tile op
     * 
     * @tparam shape_t 
     * @tparam reps_t 
     */
    template <typename shape_t, typename reps_t>
    struct resolve_optype <
        void, index::shape_tile_t, shape_t, reps_t
    >
    {
        static constexpr auto value = [](){
            if constexpr (is_dynamic_index_array_v<shape_t> && is_dynamic_index_array_v<reps_t>) {
                return as_value_v<shape_t>;
            } else if constexpr (is_hybrid_index_array_v<shape_t> && is_hybrid_index_array_v<reps_t>) {
                constexpr auto shape_max = hybrid_index_array_max_size_v<shape_t>;
                constexpr auto reps_max  = hybrid_index_array_max_size_v<reps_t>;
                constexpr auto max_size  = shape_max > reps_max ? shape_max : reps_max;
                using type = resize_hybrid_index_array_max_size_t<shape_t,max_size>;
                return as_value_v<type>;
            } else if constexpr (is_fixed_index_array_v<shape_t> && is_fixed_index_array_v<reps_t>) {
                constexpr auto shape_size = fixed_index_array_size_v<shape_t>;
                constexpr auto reps_size  = fixed_index_array_size_v<reps_t>;
                constexpr auto size = shape_size > reps_size ? shape_size : reps_size;
                using type = resize_fixed_index_array_t<shape_t,size>;
                return as_value_v<type>;
            } else if constexpr (is_dynamic_index_array_v<shape_t>) {
                return as_value_v<shape_t>;
            } else if constexpr (is_dynamic_index_array_v<reps_t>) {
                return as_value_v<reps_t>;
            } else if constexpr (is_hybrid_index_array_v<shape_t>) {
                // always select max
                constexpr auto shape_max = hybrid_ndarray_max_size_v<shape_t>;
                constexpr auto reps_size = fixed_index_array_size_v<reps_t>;
                constexpr auto max = shape_max > reps_size ? shape_max : reps_size;
                using type = resize_hybrid_index_array_max_size_t<shape_t,max>;
                return as_value_v<type>;
            } else if constexpr (is_hybrid_index_array_v<reps_t>) {
                constexpr auto shape_size = fixed_index_array_size_v<shape_t>;
                constexpr auto reps_max   = hybrid_ndarray_max_size_v<reps_t>;
                constexpr auto max = shape_size > reps_max ? shape_size : reps_max;
                using type = resize_hybrid_index_array_max_size_t<reps_t,max>;
                return as_value_v<type>;
            } else {
                return as_value_v<error::SHAPE_TILE_ERROR>;
            }
        }();
        using type = type_t<decltype(value)>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_SHAPE_TILE_HPP