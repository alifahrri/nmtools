#ifndef NMTOOLS_ARRAY_INDEX_OUTER_HPP
#define NMTOOLS_ARRAY_INDEX_OUTER_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/ndarray.hpp"

namespace nmtools::index
{
    struct shape_outer_t {};

    // TODO: cleanup index functions, handling constant index array
    template <typename ashape_t, typename bshape_t>
    constexpr auto shape_outer(const ashape_t& ashape, const bshape_t& bshape)
    {
        using return_t = meta::resolve_optype_t<shape_outer_t,ashape_t,bshape_t>;
        auto res = return_t {};

        if constexpr (!meta::is_constant_index_array_v<return_t>) {
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
        }
        
        return res;
    } // shape_outer

    template <typename indices_t, typename ashape_t, typename bshape_t>
    constexpr auto outer(const indices_t& indices, const ashape_t& ashape, const bshape_t& bshape)
    {
        using aidx_t = meta::tuple_to_array_t<meta::transform_bounded_array_t<ashape_t>>;
        using bidx_t = meta::tuple_to_array_t<meta::transform_bounded_array_t<bshape_t>>;
        auto aidx = aidx_t {};
        auto bidx = bidx_t {};

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
        
        using return_t = meta::make_tuple_type_t<aidx_t,bidx_t>;
        return return_t{aidx,bidx};
    }
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_OUTER_UNSUPPORTED : detail::fail_t {};
    }
    // TODO: cleanup index metafunctions, handling constant index array
    template <typename ashape_t, typename bshape_t>
    struct resolve_optype<
        void, index::shape_outer_t, ashape_t, bshape_t
    >
    {
        static constexpr auto vtype = [](){
            // TODO: fix is index array to include boost type
            #if 0
            if constexpr (!is_index_array_v<ashape_t> || !is_index_array_v<bshape_t>) {
                return as_value_v<error::SHAPE_OUTER_UNSUPPORTED<ashape_t,bshape_t>>;
            } else
            #endif
            if constexpr (is_constant_index_array_v<ashape_t> && is_constant_index_array_v<bshape_t>) {
                constexpr auto result = index::shape_outer(to_value_v<ashape_t>,to_value_v<bshape_t>);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)-1>([&](auto init, auto index){
                    using init_type = type_t<decltype(init)>;
                    return as_value_v<append_type_t<init_type,ct<at(result,index+1)>>>;
                }, as_value_v<nmtools_tuple<ct<at(result,0)>>>);
            } else if constexpr (is_fixed_index_array_v<ashape_t> && is_fixed_index_array_v<bshape_t>) {
                constexpr auto N = len_v<ashape_t> + len_v<bshape_t>;
                using type = nmtools_array<get_element_type_t<ashape_t>,N>;
                return as_value_v<type>;
            } else if constexpr (is_hybrid_index_array_v<ashape_t> && is_hybrid_index_array_v<bshape_t>) {
                constexpr auto N = bounded_size_v<ashape_t> + bounded_size_v<bshape_t>;
                using type = array::static_vector<get_element_type_t<ashape_t>,N>;
                return as_value_v<type>;
            } else if constexpr (
                is_dynamic_index_array_v<ashape_t> && is_dynamic_index_array_v<bshape_t>
            ) // both are dynamic resizeable
                return as_value<ashape_t>{};
            else if constexpr (
                is_dynamic_index_array_v<ashape_t> && is_bounded_size_v<bshape_t>
            ) // a is dynamic resizeable
                return as_value<ashape_t>{};
            else if constexpr (
                is_bounded_size_v<ashape_t> && is_dynamic_index_array_v<bshape_t>
            ) // b is dynamic resizeable
                return as_value<bshape_t>{};
            else if constexpr (
                is_bounded_size_v<ashape_t> && is_bounded_size_v<bshape_t>
            ) /* both is hybrid */ {
                constexpr auto amax = bounded_size_v<ashape_t>;
                constexpr auto bmax = bounded_size_v<bshape_t>;
                constexpr auto rmax = amax + bmax;
                using index_t = make_unsigned_t<get_element_or_common_type_t<ashape_t>>;
                using new_type = array::static_vector<index_t,rmax>;
                return as_value<new_type>{};
            }
            else if constexpr (
                is_bounded_size_v<ashape_t> && is_fixed_index_array_v<bshape_t>
            ) /* a is hybrid & b is fixed, prefer a */ {
                constexpr auto amax  = bounded_size_v<ashape_t>;
                constexpr auto bsize = len_v<bshape_t>;
                constexpr auto rmax = amax + bsize;
                using index_t = make_unsigned_t<get_element_or_common_type_t<ashape_t>>;
                using new_type = array::static_vector<index_t,rmax>;
                return as_value<new_type>{};
            }
            else if constexpr (
                is_fixed_index_array_v<ashape_t> && is_bounded_size_v<bshape_t>
            ) /* a is fixed & b is hybrid, prefer b */ {
                constexpr auto asize = len_v<ashape_t>;
                constexpr auto bmax  = hybrid_ndarray_max_size_v<bshape_t>;
                constexpr auto rmax  = asize + bmax;
                using index_t = make_unsigned_t<get_element_or_common_type_t<ashape_t>>;
                using new_type = array::static_vector<index_t,rmax>;
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
                constexpr auto asize = len_v<ashape_t>;
                constexpr auto bsize = len_v<bshape_t>;
                constexpr auto rsize = asize + bsize;
                using new_type = transform_bounded_array_t<tuple_to_array_t<ashape_t>>;
                using type = resize_fixed_index_array_t<new_type,rsize>;
                return as_value<type>{};
            }
            else {
                return as_value<error::SHAPE_OUTER_UNSUPPORTED<ashape_t,bshape_t>>{};
            }
        }();

        using type = type_t<meta::remove_cvref_t<decltype(vtype)>>;
    }; // shape_outer_t
}

#endif // NMTOOLS_ARRAY_INDEX_OUTER_HPP