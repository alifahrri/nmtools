#ifndef NMTOOLS_ARRAY_INDEX_BROADCAST_SHAPE_HPP
#define NMTOOLS_ARRAY_INDEX_BROADCAST_SHAPE_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/index/make_array.hpp"
#include "nmtools/array/index/max.hpp"
#include "nmtools/array/index/sum.hpp"
#include "nmtools/array/index/where.hpp"

#include <optional>

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type of broadcast_shape
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     */
    struct broadcast_shape_t {};

    /**
     * @brief broadcast two array shape together
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     * @param ashape 
     * @param bshape 
     * @return constexpr auto 
     */
    template <typename ashape_t, typename bshape_t>
    constexpr auto broadcast_shape(const ashape_t& ashape, const bshape_t& bshape)
    {
        using return_t = meta::resolve_optype_t<broadcast_shape_t,ashape_t,bshape_t>;
        using element_t = meta::get_element_type_t<return_t>;

        auto res = return_t{};
        bool success = true;

        auto adim = len(ashape);
        auto bdim = len(bshape);
        auto rdim = adim > bdim ? adim : bdim;
        if constexpr (meta::is_resizeable_v<return_t>)
            res.resize(rdim);
        
        auto broadcast_shape_impl = [&](auto i){
            using idx_t = std::make_signed_t<element_t>;
            // compute index to fill from behind
            idx_t si = rdim - i - 1;
            idx_t ai = adim - i - 1;
            idx_t bi = bdim - i - 1;
            if ((ai>=0) && (bi>=0)) {
                auto a = tuple_at(ashape,ai);
                auto b = tuple_at(bshape,bi);
                success = (a==b) || (a==1) || (b==1);
                at(res,si) = a > b ? a : b;
            }
            else if (bi<0) {
                auto a = tuple_at(ashape,ai);
                at(res,si) = a;
            }
            else if (ai<0) {
                auto b = tuple_at(bshape,bi);
                at(res,si) = b;
            }
            else {} // not valid
        };

        for (int i=0; i<size(res); i++) {
            broadcast_shape_impl(i);
            if (!success) break;
        }

        return std::tuple{success, res};
    } // broadcast_shape

    template <typename ashape_t, typename bshape_t, typename cshape_t, typename...other_shapes_t>
    constexpr auto broadcast_shape(const ashape_t& ashape, const bshape_t& bshape, const cshape_t& cshape, const other_shapes_t&...other_shapes)
    {
        // TODO: use optional
        auto [success_,shape_] = broadcast_shape(ashape,bshape);
        auto [success, shape]  = broadcast_shape(shape_,cshape,other_shapes...);
        return std::tuple{success && success_, shape};
    } // broadcast_shape

} // namespace nmtools::index

namespace nmtools::meta
{
    /**
     * @brief return resizeable array
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     */
    template <typename ashape_t, typename bshape_t>
    struct resolve_optype <
        void, index::broadcast_shape_t, ashape_t, bshape_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (
                is_dynamic_index_array_v<ashape_t> && is_dynamic_index_array_v<bshape_t>
            ) // both are dynamic resizeable
                return as_value<ashape_t>{};
            else if constexpr (
                is_dynamic_index_array_v<ashape_t> && is_hybrid_ndarray_v<bshape_t>
            ) // a is dynamic resizeable
                return as_value<ashape_t>{};
            else if constexpr (
                is_hybrid_ndarray_v<ashape_t> && is_dynamic_index_array_v<bshape_t>
            ) // b is dynamic resizeable
                return as_value<bshape_t>{};
            else if constexpr (
                is_hybrid_ndarray_v<ashape_t> && is_hybrid_ndarray_v<bshape_t>
            ) /* both is hybrid */ {
                constexpr auto amax = hybrid_ndarray_max_size_v<ashape_t>;
                constexpr auto bmax = hybrid_ndarray_max_size_v<bshape_t>;
                constexpr auto rmax = amax > bmax ? amax : bmax;
                using new_type = resize_hybrid_ndarray_max_size_t<ashape_t,rmax>;
                return as_value<new_type>{};
            }
            else if constexpr (
                is_hybrid_ndarray_v<ashape_t> && is_fixed_index_array_v<bshape_t>
            ) /* a is hybrid & b is fixed, prefer a */ {
                constexpr auto amax  = hybrid_ndarray_max_size_v<ashape_t>;
                constexpr auto bsize = fixed_index_array_size_v<bshape_t>;
                constexpr auto rmax = amax > bsize ? amax : bsize;
                using new_type = resize_hybrid_ndarray_max_size_t<ashape_t,rmax>;
                return as_value<new_type>{};
            }
            else if constexpr (
                is_fixed_index_array_v<ashape_t> && is_hybrid_ndarray_v<bshape_t>
            ) /* a is fixed & b is hybrid, prefer b */ {
                constexpr auto asize = fixed_index_array_size_v<ashape_t>;
                constexpr auto bmax  = hybrid_ndarray_max_size_v<bshape_t>;
                constexpr auto rmax  = asize > bmax ? asize : bmax;
                using new_type = resize_hybrid_ndarray_max_size_t<bshape_t,rmax>;
                return as_value<new_type>{};
            }
            else if constexpr (
                is_fixed_index_array_v<ashape_t> && is_dynamic_index_array_v<bshape_t>
            ) /* prefer dynamic */
                return as_value<bshape_t>{};
            else if constexpr (
                is_dynamic_index_array_v<ashape_t> && is_fixed_index_array_v<bshape_t>
            ) /* prefer dynamic */
                return as_value<ashape_t>{};
            else if constexpr (
                is_fixed_index_array_v<ashape_t> && is_fixed_index_array_v<bshape_t>
            ) /* both are fixed */ {
                constexpr auto asize = fixed_index_array_size_v<ashape_t>;
                constexpr auto bsize = fixed_index_array_size_v<bshape_t>;
                constexpr auto rsize = asize > bsize ? asize : bsize;
                using new_type = transform_bounded_array_t<tuple_to_array_t<ashape_t>>;
                using type = resize_fixed_index_array_t<new_type,rsize>;
                return as_value<type>{};
            }
            else return as_value<void>{};
        }();

        using type = type_t<meta::remove_cvref_t<decltype(vtype)>>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_BROADCAST_SHAPE_HPP