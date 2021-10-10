#ifndef NMTOOLS_ARRAY_INDEX_TILE_HPP
#define NMTOOLS_ARRAY_INDEX_TILE_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"

#include <algorithm>
#include <cstdlib>

namespace nmtools::index
{
    struct tile_t {};

    /**
     * @brief Transform indices from tile view to original array shape
     * 
     * @tparam shape_t 
     * @tparam reps_t 
     * @tparam indices_t 
     * @param shape shape of original array
     * @param reps number of repetitions for each axis
     * @param indices indices from tile view
     * @return constexpr auto 
     */
    template <typename shape_t, typename reps_t, typename indices_t>
    constexpr auto tile(const shape_t& shape, const reps_t&, const indices_t& indices)
    {
        using return_t = meta::resolve_optype_t<tile_t,shape_t,reps_t,indices_t>;

        auto ret = return_t {};

        // len(indices) == max(len(shape),len(reps))
        auto m = len(shape);
        auto n = len(indices);
        // clang (android & emscripten) complains about ambiguous call
        auto s = std::max(m,n);

        if constexpr (meta::is_resizeable_v<return_t>)
            ret.resize(size(shape));
        
        // use int since ai/bi may be negative
        for (int i=0; i<(int)s; i++) {
            int ai = m - i - 1;
            int bi = n - i - 1;
            if (ai >= 0) {
                auto idx = at(indices,bi);
                auto s = tuple_at(shape,ai);
                at(ret,ai) = idx % s;
            }
            else break;
        }
        
        return ret;
    } // tile
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error {
        struct INDEX_TILE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    /**
     * @brief resolve return type for index::tile op
     * 
     * @tparam shape_t 
     * @tparam reps_t 
     * @tparam indices_t 
     */
    template <typename shape_t, typename reps_t, typename indices_t>
    struct resolve_optype <
        void, index::tile_t, shape_t, reps_t, indices_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_constant_index_array_v<shape_t>) {
                return as_value_v<error::INDEX_TILE_UNSUPPORTED>;
            } else if constexpr (is_fixed_index_array_v<shape_t>) {
                return as_value_v<transform_bounded_array_t<shape_t>>;
            } else if constexpr (is_index_array_v<shape_t>) {
                return as_value_v<shape_t>;
            } else {
                return as_value_v<error::INDEX_TILE_UNSUPPORTED>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_TILE_HPP