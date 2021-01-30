#ifndef NMTOOLS_ARRAY_INDEX_REPEAT_HPP
#define NMTOOLS_ARRAY_INDEX_REPEAT_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/argfilter.hpp"
#include "nmtools/array/index/cumsum.hpp"

#include <type_traits>

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve returnt type of repeat op
     * 
     */
    struct repeat_t {};

    /**
     * @brief transform indices from repeated view to indices for origin shape
     * 
     * @tparam shape_t 
     * @tparam indices_t 
     * @tparam repeats_t 
     * @tparam axis_t 
     * @param shape original shape
     * @param indices indices from repeat view
     * @param repeats
     * @param axis 
     * @return constexpr auto 
     */
    template <typename shape_t, typename indices_t, typename repeats_t, typename axis_t>
    constexpr auto repeat(const shape_t& shape, const indices_t& indices, const repeats_t& repeats, axis_t axis)
    {
        using return_t = meta::resolve_optype_t<repeat_t,shape_t,indices_t,repeats_t,axis_t>;
        auto ret = return_t {};

        if constexpr (is_none_v<axis_t>) {
            auto i = [&](){
                if constexpr (std::is_integral_v<indices_t>)
                    return indices / repeats;
                else {
                    static_assert (std::tuple_size_v<indices_t> == 1
                        , "unsupported index::repeat"
                    );
                    return std::get<0>(indices) / repeats;
                }
            }();
            ret = compute_indices(i,shape);
        }
        else {
            auto n = vector_size(indices);
            if constexpr (meta::is_resizeable_v<return_t>)
                ret.resize(n);
            for (size_t i=0; i<n; i++) {
                auto idx = at(indices,i);
                if constexpr (std::is_integral_v<repeats_t>)
                    at(ret,i) = (i==axis ? idx / repeats : idx);
                else {
                    auto csum = cumsum(repeats);
                    if (i==axis) {
                        // note: len(repeats) == shape[axis]
                        // simply find arg of repeats such that idx >= accumulate(repeats)[args]
                        auto f = [&](auto a){
                            return idx<a;
                        };
                        auto arg = argfilter(f, csum);
                        at(ret,i) = at(arg,0); // take first
                    }
                    else at(ret,i) = idx;
                }
            } // for
        }

        return ret;
    } // repeat
} // namespace nmtools::index

namespace nmtools::meta
{
    /**
     * @brief resolve return type for repeat op
     * 
     * @tparam shape_t 
     * @tparam indices_t 
     * @tparam repeats_t 
     */
    template <typename shape_t, typename indices_t, typename repeats_t>
    struct resolve_optype<
        void, index::repeat_t, shape_t, indices_t, repeats_t, none_t
    >
    {
        using type = std::conditional_t<
            std::is_integral_v<repeats_t> && (has_tuple_size_v<indices_t> || std::is_integral_v<indices_t>),
            resolve_optype_t<index::compute_indices_t,indices_t,shape_t>, void
        >;
    }; // resolve_optype

    template <typename shape_t, typename indices_t, typename repeats_t, typename axis_t>
    struct resolve_optype<
        void, index::repeat_t, shape_t, indices_t, repeats_t, axis_t
    >
    {
        using type = transform_bounded_array_t<tuple_to_array_t<indices_t>>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_REPEAT_HPP