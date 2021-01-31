#ifndef NMTOOLS_ARRAY_INDEX_SHAPE_TILE_HPP
#define NMTOOLS_ARRAY_INDEX_SHAPE_TILE_HPP

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
        for (int i=0; i<size(ret); i++)
            shape_tile_impl(i);

        return ret;
    } // shape_tile
} // namespace nmtools::index

namespace nmtools::meta
{
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
        template <typename T>
        struct is_resizeable_not_hybrid
            : logical_and<is_resizeable<T>,std::negation<is_hybrid_ndarray<T>>> {};

        using type_list = std::tuple<shape_t,reps_t>;
        static constexpr auto selection_kind = [](){
            if constexpr (apply_logical_or_v<is_resizeable_not_hybrid,type_list>)
                return select_resizeable_kind_t {};
            else if constexpr (apply_logical_or_v<is_hybrid_ndarray,type_list>)
                return select_hybrid_kind_t {};
            else return select_fixed_kind_t {};
        }();
        using selection_kind_t = remove_cvref_t<decltype(selection_kind)>;
        // shape type must be integral
        using selection_t = select_array1d_t<
            size_policy_max_t, selection_kind_t, std::is_integral
        >;
        // final type
        using type = resolve_optype_t<
            selection_t, shape_t, reps_t
        >;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_SHAPE_TILE_HPP