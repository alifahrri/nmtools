#ifndef NMTOOLS_ARRAY_INDEX_BROADCAST_SHAPE_HPP
#define NMTOOLS_ARRAY_INDEX_BROADCAST_SHAPE_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/ref.hpp"
#include "nmtools/array/index/max.hpp"
#include "nmtools/array/index/sum.hpp"
#include "nmtools/array/index/where.hpp"
#include "nmtools/array/ndarray.hpp"

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
        using result_t = meta::resolve_optype_t<broadcast_shape_t,ashape_t,bshape_t>;
        using element_t = meta::remove_cvref_t<meta::get_index_element_type_t<result_t>>;

        auto res = result_t{};
        bool success = true;

        [[maybe_unused]]
        auto len_ = [](const auto& shape){
            constexpr auto N = meta::len_v<meta::remove_cvref_t<decltype(shape)>>;
            if constexpr (N>0) {
                return meta::ct_v<N>;
            } else {
                return len(shape);
            }
        };

        if constexpr (meta::is_constant_index_array_v<result_t>) {
            // do nothing, already computed at compile-time
            // the type holds broadcasted shape
        }
        // for none return type (both ashape and bshape is scalar)
        // simply bypass this
        else if constexpr (!is_none_v<ashape_t> && !is_none_v<bshape_t>) {
            auto adim = len_(ashape);
            auto bdim = len_(bshape);
            using adim_t = decltype(adim);
            using bdim_t = decltype(bdim);
            using meta::is_constant_index_v;
            auto rdim = [&](){
                if constexpr (
                    is_constant_index_v<adim_t>
                    && is_constant_index_v<bdim_t>
                ) {
                    constexpr auto adim = adim_t::value;
                    constexpr auto bdim = bdim_t::value;
                    return meta::ct_v<(adim > bdim ? adim : bdim)>;
                } else {
                    return adim > bdim ? adim : bdim;
                }
            }();
            using rdim_t = decltype(rdim);

            if constexpr (meta::is_resizable_v<result_t>)
                res.resize(rdim);
            
            auto broadcast_shape_impl = [&](auto i){
                using idx_t = meta::make_signed_t<element_t>;
                // compute index to fill from behind
                auto si = [&](){
                    if constexpr (is_constant_index_v<rdim_t> && is_constant_index_v<decltype(i)>) {
                        return meta::ct_v<(rdim_t::value - decltype(i)::value - 1)>;
                    } else {
                        return idx_t(rdim - i - 1);
                    }
                }();
                idx_t ai = (idx_t)adim - (idx_t)i - 1;
                idx_t bi = (idx_t)bdim - (idx_t)i - 1;
                if ((ai>=0) && (bi>=0)) {
                    auto a = at(ashape,ai);
                    auto b = at(bshape,bi);
                    using common_t = meta::promote_index_t<decltype(a),decltype(b)>;
                    success = ((common_t)a==(common_t)b) || (a==1) || (b==1);
                    at(res,si) = (common_t)a > (common_t)b ? (common_t)a : (common_t)b;
                }
                else if (bi<0) {
                    auto a = at(ashape,ai);
                    at(res,si) = a;
                }
                else if (ai<0) {
                    auto b = at(bshape,bi);
                    at(res,si) = b;
                }
                else {} // not valid
            };

            constexpr auto N = meta::len_v<result_t>;
            if constexpr (N > 0) {
                meta::template_for<N>([&](auto i){
                    if (success) {
                        broadcast_shape_impl(i);
                    }
                });
            } else {
                for (size_t i=0; i<(size_t)len(res); i++) {
                    broadcast_shape_impl(i);
                    if (!success) break;
                }
            }
        }
        else if constexpr (is_none_v<ashape_t> && !is_none_v<bshape_t>) {
            // one of the shape is none (from shape of num type):
            // just copy the other shape, bshape in this case
            auto bdim = len(bshape);
            if constexpr (meta::is_resizable_v<result_t>)
                res.resize(bdim);
            if constexpr (meta::is_tuple_v<bshape_t>) {
                constexpr auto N = meta::len_v<bshape_t>;
                meta::template_for<N>([&](auto i){
                    at(res,i) = at(bshape,i);
                });
            } else {
                for (size_t i=0; i<bdim; i++)
                    at(res,i) = at(bshape,i);
            }
        }
        else if constexpr (is_none_v<bshape_t> && !is_none_v<ashape_t>) {
            // similar to above case, but ashape is index array instead of bshape
            auto adim = len(ashape);
            if constexpr (meta::is_resizable_v<result_t>)
                res.resize(adim);
            if constexpr (meta::is_tuple_v<ashape_t>) {
                constexpr auto N = meta::len_v<ashape_t>;
                meta::template_for<N>([&](auto i){
                    at(res,i) = at(ashape,i);
                });
            } else {
                for (size_t i=0; i<adim; i++)
                    at(res,i) = at(ashape,i);
            }
        } else {
            // do nothing
        }

        // TODO: use optional
        using return_t = meta::make_tuple_type_t<bool,result_t>;
        return return_t{success, res};
    } // broadcast_shape

    template <typename ashape_t, typename bshape_t, typename cshape_t, typename...other_shapes_t>
    constexpr auto broadcast_shape(const ashape_t& ashape, const bshape_t& bshape, const cshape_t& cshape, const other_shapes_t&...other_shapes)
    {
        // TODO: use optional
        const auto [success_,shape_] = broadcast_shape(ashape,bshape);
        const auto [success, shape]  = broadcast_shape(shape_,cshape,other_shapes...);
        using return_t = meta::make_tuple_type_t<bool,meta::remove_cvref_t<decltype(shape)>>;
        return return_t{success && success_, shape};
    } // broadcast_shape

} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        // error type for in-compatible shapes
        struct BROADCAST_SHAPE_ERROR : detail::fail_t {};
        // error type for unsupported ashape_t bshape_t
        template <typename...>
        struct BROADCAST_SHAPE_UNSUPPORTED : detail::fail_t {};
    }

    /**
     * @brief return resizable array
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
            constexpr auto is_constant_shape_a = is_constant_index_array_v<ashape_t>;
            constexpr auto is_constant_shape_b = is_constant_index_array_v<bshape_t>;
            // both ashape and bshape values are known at compile-time
            // then compute at compile-time
            if constexpr (
                (is_constant_shape_a || is_clipped_index_array_v<ashape_t>)
                && (is_constant_shape_b || is_clipped_index_array_v<bshape_t>)
            ) {
                constexpr auto ashape = to_value_v<ashape_t>;
                constexpr auto bshape = to_value_v<bshape_t>;
                constexpr auto broadcasted = index::broadcast_shape(ashape,bshape);
                constexpr auto success = at(broadcasted,meta::ct_v<0>);
                if constexpr (success) {
                    // convert back from value to type
                    constexpr auto shape = at(broadcasted,meta::ct_v<1>);
                    return template_reduce<::nmtools::len(shape)>([&](auto init, auto index){
                        // init should be as_value<sometype>
                        using init_t = type_t<decltype(init)>;
                        constexpr auto I = at(shape,index);
                        if constexpr (is_constant_shape_a && is_constant_shape_b) {
                            using type = append_type_t<init_t,ct<I>>;
                            return as_value_v<type>;
                        } else {
                            using type = append_type_t<init_t,clipped_size_t<I>>;
                            return as_value_v<type>;
                        }
                    }, meta::as_value_v<nmtools_tuple<>>);
                } else if constexpr (!is_constant_shape_a || !is_constant_shape_b) {
                    // actual value is runtime
                    constexpr auto len_a = len_v<ashape_t>;
                    constexpr auto len_b = len_v<bshape_t>;
                    constexpr auto dim = (len_a > len_b ? len_a : len_b);
                    // TODO: consider to use index_t
                    using type = nmtools_array<size_t,dim>;
                    return as_value_v<type>;
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
            } else if constexpr (is_index_array_v<ashape_t> && is_index_array_v<bshape_t>) {
                constexpr auto len_a = len_v<ashape_t>;
                constexpr auto len_b = len_v<bshape_t>;
                constexpr auto b_size_a = bounded_size_v<ashape_t>;
                constexpr auto b_size_b = bounded_size_v<bshape_t>;
                using index_t = meta::get_index_element_type_t<ashape_t>;
                if constexpr ((len_a > 0) && (len_b > 0)) {
                    using type = nmtools_array<index_t,(len_a > len_b ? len_a : len_b)>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(b_size_a)> && !is_fail_v<decltype(b_size_b)>) {
                    using type = array::static_vector<index_t,(b_size_a > b_size_b ? b_size_a : b_size_b)>;
                    return as_value_v<type>;
                } else {
                    // TODO: small buffer optimization
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                }
            }
            // return either b or a which is not None
            else if constexpr (is_none_v<ashape_t>) {
                using ret_t = transform_bounded_array_t<bshape_t>;
                return as_value_v<ret_t>;
            }
            else if constexpr (is_none_v<bshape_t>) {
                using ret_t = transform_bounded_array_t<ashape_t>;
                return as_value_v<ret_t>;
            }
            #if 0
            else if constexpr (
                is_dynamic_index_array_v<ashape_t> && is_dynamic_index_array_v<bshape_t>
            ) // both are dynamic resizable
                return as_value_v<ashape_t>;
            else if constexpr (
                is_dynamic_index_array_v<ashape_t> && is_hybrid_ndarray_v<bshape_t>
            ) // a is dynamic resizable
                return as_value_v<ashape_t>;
            else if constexpr (
                is_hybrid_ndarray_v<ashape_t> && is_dynamic_index_array_v<bshape_t>
            ) // b is dynamic resizable
                return as_value_v<bshape_t>;
            else if constexpr (
                is_hybrid_ndarray_v<ashape_t> && is_hybrid_ndarray_v<bshape_t>
            ) /* both is hybrid */ {
                constexpr auto amax = hybrid_ndarray_max_size_v<ashape_t>;
                constexpr auto bmax = hybrid_ndarray_max_size_v<bshape_t>;
                constexpr auto r_max = amax > bmax ? amax : bmax;
                using new_type = resize_hybrid_ndarray_max_size_t<ashape_t,r_max>;
                return as_value_v<new_type>;
            }
            else if constexpr (
                is_hybrid_ndarray_v<ashape_t> && is_fixed_index_array_v<bshape_t>
            ) /* a is hybrid & b is fixed, prefer a */ {
                constexpr auto amax  = hybrid_ndarray_max_size_v<ashape_t>;
                constexpr auto bsize = fixed_index_array_size_v<bshape_t>;
                constexpr auto r_max = amax > bsize ? amax : bsize;
                using new_type = resize_hybrid_ndarray_max_size_t<ashape_t,r_max>;
                return as_value_v<new_type>;
            }
            else if constexpr (
                is_fixed_index_array_v<ashape_t> && is_hybrid_ndarray_v<bshape_t>
            ) /* a is fixed & b is hybrid, prefer b */ {
                constexpr auto asize = fixed_index_array_size_v<ashape_t>;
                constexpr auto bmax  = hybrid_ndarray_max_size_v<bshape_t>;
                constexpr auto r_max = asize > bmax ? asize : bmax;
                using new_type = resize_hybrid_ndarray_max_size_t<bshape_t,r_max>;
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
            else if constexpr (
                is_index_array_v<ashape_t> && is_index_array_v<bshape_t>
            ) {
                constexpr auto len_a = len_v<ashape_t>;
                constexpr auto len_b = len_v<bshape_t>;
                // TODO: try to return static_vector
                // constexpr auto b_size_a = bounded_size_v<ashape_t>;
                // constexpr auto b_size_b = bounded_size_v<bshape_t>;
                if constexpr ((len_a > 0) && (len_b > 0)) {
                    constexpr auto max_size = (len_a > len_b) ? len_a : len_b;
                    // TODO: use index_type instead of size_t
                    using type = nmtools_array<size_t,max_size>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<size_t>;
                    return as_value_v<type>;
                }
            }
            #endif
            else {
                return as_value_v<error::BROADCAST_SHAPE_UNSUPPORTED<ashape_t,bshape_t>>;
            }
        }();

        using type = type_t<decltype(vtype)>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_BROADCAST_SHAPE_HPP