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
        using element_t = meta::remove_cvref_t<meta::get_element_or_common_type_t<return_t>>;

        auto res = return_t{};
        bool success = true;

        if constexpr (meta::is_constant_index_array_v<return_t>) {
            // do nothing, already computed at compile-time
            // the type holds broadcasted shape
        }
        // for none return type (both ashape and bshape is scalar)
        // simply bypass this
        else if constexpr (!is_none_v<ashape_t> && !is_none_v<bshape_t>) {
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
                    // TODO: do not use tuple_at
                    auto a = tuple_at(ashape,ai);
                    auto b = tuple_at(bshape,bi);
                    using common_t = meta::promote_index_t<decltype(a),decltype(b)>;
                    success = ((common_t)a==(common_t)b) || (a==1) || (b==1);
                    at(res,si) = (common_t)a > (common_t)b ? a : b;
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

            for (size_t i=0; i<(size_t)len(res); i++) {
                broadcast_shape_impl(i);
                if (!success) break;
            }
        }
        else if constexpr (is_none_v<ashape_t> && !is_none_v<bshape_t>) {
            // one of the shape is none (from shape of num type):
            // just copy the other shape, bshape in this case
            auto bdim = len(bshape);
            if constexpr (meta::is_resizeable_v<return_t>)
                res.resize(bdim);
            for (size_t i=0; i<bdim; i++)
                at(res,i) = at(bshape,i);
        }
        else if constexpr (is_none_v<bshape_t> && !is_none_v<ashape_t>) {
            // similar to above case, but ashape is index array instead of bshape
            auto adim = len(ashape);
            if constexpr (meta::is_resizeable_v<return_t>)
                res.resize(adim);
            for (size_t i=0; i<adim; i++)
                at(res,i) = at(ashape,i);
        } else {
            // do nothing
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
    namespace error
    {
        // error type for in-compatible shapes
        struct BROADCAST_SHAPE_ERROR : detail::fail_t {};
        // error type for unsupported ashape_t bshape_t
        struct BROADCAST_SHAPE_UNSUPPORTED : detail::fail_t {};
    }

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
            // both ashape and bshape values are known at compile-time
            // then compute at compile-time
            if constexpr (is_constant_index_array_v<ashape_t> && is_constant_index_array_v<bshape_t>) {
                constexpr auto ashape = to_value_v<ashape_t>;
                constexpr auto bshape = to_value_v<bshape_t>;
                constexpr auto broadcasted = index::broadcast_shape(ashape,bshape);
                constexpr auto success = at(broadcasted,meta::ct_v<0>);
                if constexpr (success) {
                    // convert back from value to type
                    constexpr auto shape = at(broadcasted,meta::ct_v<1>);
                    constexpr auto s0 = at(shape,0);
                    return template_reduce<::nmtools::len(shape)-1>([&](auto init, auto index){
                        // init should be as_value<sometype>
                        using init_t = type_t<decltype(init)>;
                        constexpr auto s_i1 = at(shape,index+1);
                        using type = append_type_t<init_t,meta::ct<s_i1>>;
                        return as_value_v<type>;
                    }, meta::as_value_v<std::tuple<ct<s0>>>);
                } else {
                    return as_value_v<error::BROADCAST_SHAPE_ERROR>;
                }
            } else if constexpr (is_none_v<ashape_t> && is_constant_index_array_v<bshape_t>) {
                // broadcasting with none retain shape, just select the shape
                return as_value_v<bshape_t>;
            } else if constexpr (is_constant_index_array_v<ashape_t> && is_none_v<bshape_t>) {
                return as_value_v<ashape_t>;
            }
            // none shape indicates scalar type
            else if constexpr (is_none_v<ashape_t> && is_none_v<bshape_t>) {
                // broadcasting none and none should result none
                return as_value_v<none_t>;
            // return either b or a which is not None
            } else if constexpr (is_none_v<ashape_t>) {
                using ret_t = tuple_to_array_t<
                    transform_bounded_array_t<bshape_t>
                >;
                return as_value_v<ret_t>;
            }
            else if constexpr (is_none_v<bshape_t>) {
                using ret_t = tuple_to_array_t<
                    transform_bounded_array_t<ashape_t>
                >;
                return as_value_v<ret_t>;
            }
            else if constexpr (
                is_dynamic_index_array_v<ashape_t> && is_dynamic_index_array_v<bshape_t>
            ) // both are dynamic resizeable
                return as_value_v<ashape_t>;
            else if constexpr (
                is_dynamic_index_array_v<ashape_t> && is_hybrid_ndarray_v<bshape_t>
            ) // a is dynamic resizeable
                return as_value_v<ashape_t>;
            else if constexpr (
                is_hybrid_ndarray_v<ashape_t> && is_dynamic_index_array_v<bshape_t>
            ) // b is dynamic resizeable
                return as_value_v<bshape_t>;
            else if constexpr (
                is_hybrid_ndarray_v<ashape_t> && is_hybrid_ndarray_v<bshape_t>
            ) /* both is hybrid */ {
                constexpr auto amax = hybrid_ndarray_max_size_v<ashape_t>;
                constexpr auto bmax = hybrid_ndarray_max_size_v<bshape_t>;
                constexpr auto rmax = amax > bmax ? amax : bmax;
                using new_type = resize_hybrid_ndarray_max_size_t<ashape_t,rmax>;
                return as_value_v<new_type>;
            }
            else if constexpr (
                is_hybrid_ndarray_v<ashape_t> && is_fixed_index_array_v<bshape_t>
            ) /* a is hybrid & b is fixed, prefer a */ {
                constexpr auto amax  = hybrid_ndarray_max_size_v<ashape_t>;
                constexpr auto bsize = fixed_index_array_size_v<bshape_t>;
                constexpr auto rmax = amax > bsize ? amax : bsize;
                using new_type = resize_hybrid_ndarray_max_size_t<ashape_t,rmax>;
                return as_value_v<new_type>;
            }
            else if constexpr (
                is_fixed_index_array_v<ashape_t> && is_hybrid_ndarray_v<bshape_t>
            ) /* a is fixed & b is hybrid, prefer b */ {
                constexpr auto asize = fixed_index_array_size_v<ashape_t>;
                constexpr auto bmax  = hybrid_ndarray_max_size_v<bshape_t>;
                constexpr auto rmax  = asize > bmax ? asize : bmax;
                using new_type = resize_hybrid_ndarray_max_size_t<bshape_t,rmax>;
                return as_value_v<new_type>;
            }
            else if constexpr (
                is_fixed_index_array_v<ashape_t> && is_dynamic_index_array_v<bshape_t>
            ) /* prefer dynamic */
                return as_value<bshape_t>{};
            else if constexpr (
                is_dynamic_index_array_v<ashape_t> && is_fixed_index_array_v<bshape_t>
            ) /* prefer dynamic */
                return as_value_v<ashape_t>;
            else if constexpr (
                is_fixed_index_array_v<ashape_t> && is_fixed_index_array_v<bshape_t>
            ) /* both are fixed */ {
                constexpr auto asize = fixed_index_array_size_v<ashape_t>;
                constexpr auto bsize = fixed_index_array_size_v<bshape_t>;
                constexpr auto rsize = asize > bsize ? asize : bsize;
                using new_type = transform_bounded_array_t<tuple_to_array_t<ashape_t>>;
                using type = resize_fixed_index_array_t<new_type,rsize>;
                return as_value_v<type>;
            }
            else return as_value_v<error::BROADCAST_SHAPE_UNSUPPORTED>;
        }();

        using type = type_t<meta::remove_cvref_t<decltype(vtype)>>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_BROADCAST_SHAPE_HPP