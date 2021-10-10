#ifndef NMTOOLS_ARRAY_INDEX_OUTER_HPP
#define NMTOOLS_ARRAY_INDEX_OUTER_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"

#include <tuple>

namespace nmtools::index
{
    struct shape_outer_t {};

    // TODO: cleanup index functions, handling constant index array
    template <typename ashape_t, typename bshape_t>
    constexpr auto shape_outer(const ashape_t& ashape, const bshape_t& bshape)
    {
        using return_t = meta::resolve_optype_t<shape_outer_t,ashape_t,bshape_t>;
        auto res = return_t {};

        auto adim = len(ashape);
        auto bdim = len(bshape);
        if constexpr (meta::is_resizeable_v<return_t>) {
            auto dim  = adim + bdim;
            res.resize(dim);
        }
        
        for (size_t i=0; i<adim; i++)
            at(res,i) = at(ashape,i);
        for (size_t i=0; i<bdim; i++)
            at(res,i+adim) = at(bshape,i);
        
        return res;
    } // shape_outer

    template <typename indices_t, typename ashape_t, typename bshape_t>
    constexpr auto outer(const indices_t& indices, const ashape_t& ashape, const bshape_t& bshape)
    {
        auto aidx = meta::tuple_to_array_t<meta::transform_bounded_array_t<ashape_t>> {};
        auto bidx = meta::tuple_to_array_t<meta::transform_bounded_array_t<bshape_t>> {};

        auto adim = len(ashape);
        auto bdim = len(bshape);

        if constexpr (meta::is_resizeable_v<ashape_t>)
            aidx.resize(adim);
        if constexpr (meta::is_resizeable_v<bshape_t>)
            bidx.resize(bdim);
        
        for (size_t i=0; i<adim; i++)
            at(aidx,i) = at(indices,i);
        for (size_t i=0; i<bdim; i++)
            at(bidx,i) = at(indices,i+adim);
        
        return std::tuple{aidx,bidx};
    }
} // namespace nmtools::index

namespace nmtools::meta
{
    // TODO: cleanup index metafunctions, handling constant index array
    template <typename ashape_t, typename bshape_t>
    struct resolve_optype<
        void, index::shape_outer_t, ashape_t, bshape_t
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
                constexpr auto rmax = amax + bmax;
                using new_type = resize_hybrid_ndarray_max_size_t<ashape_t,rmax>;
                return as_value<new_type>{};
            }
            else if constexpr (
                is_hybrid_ndarray_v<ashape_t> && is_fixed_index_array_v<bshape_t>
            ) /* a is hybrid & b is fixed, prefer a */ {
                constexpr auto amax  = hybrid_ndarray_max_size_v<ashape_t>;
                constexpr auto bsize = fixed_index_array_size_v<bshape_t>;
                constexpr auto rmax = amax + bsize;
                using new_type = resize_hybrid_ndarray_max_size_t<ashape_t,rmax>;
                return as_value<new_type>{};
            }
            else if constexpr (
                is_fixed_index_array_v<ashape_t> && is_hybrid_ndarray_v<bshape_t>
            ) /* a is fixed & b is hybrid, prefer b */ {
                constexpr auto asize = fixed_index_array_size_v<ashape_t>;
                constexpr auto bmax  = hybrid_ndarray_max_size_v<bshape_t>;
                constexpr auto rmax  = asize + bmax;
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
                constexpr auto rsize = asize + bsize;
                using new_type = transform_bounded_array_t<tuple_to_array_t<ashape_t>>;
                using type = resize_fixed_index_array_t<new_type,rsize>;
                return as_value<type>{};
            }
            else return as_value<void>{};
        }();

        using type = type_t<meta::remove_cvref_t<decltype(vtype)>>;
    }; // shape_outer_t
}

#endif // NMTOOLS_ARRAY_INDEX_OUTER_HPP