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
}

namespace nmtools::index::impl
{
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
                return meta::ct_v<(size_t)N>;
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

            if constexpr (meta::is_resizable_v<result_t>)
                res.resize(rdim);
            
            auto broadcast_shape_impl = [&](auto i){
                using idx_t = meta::remove_address_space_t<meta::make_signed_t<element_t>>;
                // compute index to fill from behind
                #if 0
                // OK in gcc but failed on clang 🤷
                auto si = [&](){
                    using rdim_t = decltype(rdim);
                    if constexpr (is_constant_index_v<rdim_t> && is_constant_index_v<decltype(i)>) {
                        return meta::ct_v<(rdim_t::value - decltype(i)::value - 1)>;
                    } else {
                        return idx_t(rdim - i - 1);
                    }
                }();
                #else
                auto si = [&](auto rdim, auto i){
                    using rdim_t = decltype(rdim);
                    if constexpr (is_constant_index_v<rdim_t> && is_constant_index_v<decltype(i)>) {
                        return meta::ct_v<(rdim_t::value - decltype(i)::value - 1)>;
                    } else {
                        return idx_t(rdim - i - 1);
                    }
                }(rdim,i);
                #endif
                idx_t ai = ((idx_t)adim - (idx_t)i) - 1;
                idx_t bi = ((idx_t)bdim - (idx_t)i) - 1;
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

        using return_t = nmtools_maybe<result_t>;
        if (success) {
            return return_t{res};
        } else {
            return return_t{meta::Nothing};
        }
    } // broadcast_shape
}

namespace nmtools::index
{
    template <typename ashape_t, typename bshape_t>
    constexpr auto broadcast_shape(const ashape_t& ashape, const bshape_t& bshape)
    {
        if constexpr (meta::is_maybe_v<ashape_t>) {
            using result_type = decltype(broadcast_shape(*ashape,bshape));
            using return_type = meta::conditional_t<meta::is_maybe_v<result_type>
                , result_type, nmtools_maybe<result_type>
            >;
            if (static_cast<bool>(ashape)) {
                auto result = broadcast_shape(*ashape,bshape);
                if constexpr (meta::is_maybe_v<result_type>) {
                    return (static_cast<bool>(result)
                        ? return_type{result}
                        : return_type{meta::Nothing})
                    ;
                } else {
                    return return_type{result};
                }
            } else {
                return return_type{meta::Nothing};
            }
        } else if constexpr (meta::is_maybe_v<bshape_t>) {
            using result_type = decltype(broadcast_shape(ashape,*bshape));
            using return_type = meta::conditional_t<meta::is_maybe_v<result_type>
                , result_type, nmtools_maybe<result_type>
            >;
            if (static_cast<bool>(bshape)) {
                auto result = broadcast_shape(ashape,*bshape);
                if constexpr (meta::is_maybe_v<result_type>) {
                    return (static_cast<bool>(result)
                        ? return_type{result}
                        : return_type{meta::Nothing})
                    ;
                } else {
                    return return_type{result};
                }
            } else {
                return return_type{meta::Nothing};
            }
        } else {
            return impl::broadcast_shape(ashape,bshape);
        }
    }

    template <typename ashape_t, typename bshape_t, typename cshape_t, typename...other_shapes_t>
    constexpr auto broadcast_shape(const ashape_t& ashape, const bshape_t& bshape, const cshape_t& cshape, const other_shapes_t&...other_shapes)
    {
        // TODO: use optional
        #if 0
        const auto [success_,shape_] = broadcast_shape(ashape,bshape);
        const auto [success, shape]  = broadcast_shape(shape_,cshape,other_shapes...);
        using return_t = nmtools_tuple<bool,meta::remove_cvref_t<meta::remove_address_space_t<decltype(shape)>>>;
        return return_t{success && success_, shape};
        #else
        auto result_ = broadcast_shape(ashape,bshape);
        using result_t = decltype(broadcast_shape(*result_,cshape,other_shapes...));
        if (result_) {
            return broadcast_shape(*result_,cshape,other_shapes...);
        } else {
            return result_t{meta::Nothing};
        }
        #endif
    } // broadcast_shape

    struct broadcast_size_t {};

    template <typename dst_shape_t, typename a_size_t, typename b_size_t, typename...other_sizes_t>
    constexpr auto broadcast_size([[maybe_unused]] const dst_shape_t& dst_shape
        , [[maybe_unused]] a_size_t a_size
        , [[maybe_unused]] b_size_t b_size
        , [[maybe_unused]] other_sizes_t... other_sizes)
    {
        using result_t = meta::resolve_optype_t<broadcast_size_t,dst_shape_t,a_size_t,b_size_t,other_sizes_t...>;

        if constexpr (meta::is_maybe_v<result_t>) {
            if (static_cast<bool>(a_size)) {
                auto result = broadcast_size(dst_shape,*a_size,b_size,other_sizes...);
                // assume not nested optional
                return result_t{result};
            } else {
                return result_t{meta::Nothing};
            }
        } else {
            auto result = result_t {};

            if constexpr (!meta::is_constant_index_v<result_t>) {
                result = index::product(dst_shape);
            }

            return result;
        }
    } // broadcast_size

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

        template <typename...>
        struct BROADCAST_SIZE_UNSUPPORTED : detail::fail_t {};
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
                constexpr auto success = static_cast<bool>(broadcasted);
                if constexpr (success) {
                    // convert back from value to type
                    constexpr auto shape = *broadcasted;
                    return template_reduce<::nmtools::len(shape)>([&](auto init, auto index){
                        // init should be as_value<sometype>
                        using init_t = type_t<decltype(init)>;
                        constexpr auto I = at(shape,index);
                        // using `is_constant_shape_a` here seems to not working on avr-gcc
                        if constexpr (is_constant_index_array_v<ashape_t> && is_constant_index_array_v<bshape_t>) {
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
                constexpr auto c_value_a = to_value_v<ashape_t>;
                constexpr auto c_value_b = to_value_v<bshape_t>;
                using index_t = meta::get_index_element_type_t<ashape_t>;

                if constexpr ((len_a > 0) && (len_b > 0)) {
                    using type [[maybe_unused]] = nmtools_array<index_t,(len_a > len_b ? len_a : len_b)>;
                    if constexpr (!is_fail_v<decltype(c_value_a)> && (len_a >= len_b)) {
                        return meta::template_reduce<len_a>([&](auto init, auto index){
                            using init_type = type_t<decltype(init)>;
                            constexpr auto I = at(c_value_a,index);
                            // if there exists "1", bail out, we can't know the value at compile-time
                            if constexpr ((I > 1) && is_tuple_v<init_type>) {
                                using type = append_type_t<init_type,clipped_size_t<I>>;
                                return as_value_v<type>;
                            } else {
                                return as_value_v<type>;
                            }
                        }, as_value_v<nmtools_tuple<>>);
                    } else if constexpr (!is_fail_v<decltype(c_value_b)> && (len_b >= len_a)) {
                        return meta::template_reduce<len_b>([&](auto init, auto index){
                            using init_type = type_t<decltype(init)>;
                            constexpr auto I = at(c_value_b,index);
                            // if there exists "1", bail out, we can't know the value at compile-time
                            if constexpr ((I > 1) && is_tuple_v<init_type>) {
                                using type = append_type_t<init_type,clipped_size_t<I>>;
                                return as_value_v<type>;
                            } else {
                                return as_value_v<type>;
                            }
                        }, as_value_v<nmtools_tuple<>>);
                    } else {
                        return as_value_v<type>;
                    }
                } else if constexpr ((len_a > 0) && !is_fail_v<decltype(b_size_b)>) {
                    constexpr auto dim = (len_a > b_size_b ? len_a : b_size_b);
                    using type [[maybe_unused]] = array::static_vector<index_t,dim>;
                    if constexpr (!is_fail_v<decltype(c_value_a)> && (len_a >= b_size_b)) {
                        // NOTE: the following tries to deduce as bounded-shape to be able to compute at compile-time
                        // but the runtime part index::broadcast_shape is still not support it yet
                        // because of unhandled mixed constant index vs runtime index when computing result
                        #if 0
                        return meta::template_reduce<len_a>([&](auto init, auto index){
                            using init_type = type_t<decltype(init)>;
                            constexpr auto I = at(c_value_a,index);
                            // if there exists "1", bail out, we can't know the value at compile-time
                            if constexpr ((I > 1) && is_tuple_v<init_type>) {
                                using type = append_type_t<init_type,clipped_size_t<I>>;
                                return as_value_v<type>;
                            } else {
                                return as_value_v<type>;
                            }
                        }, as_value_v<nmtools_tuple<>>);
                        #else
                        // get max num and return clipped index packed in array instead of tuple
                        constexpr auto minmax = [&](){
                            auto min = at(c_value_a,0);
                            auto max = at(c_value_a,0);
                            for (size_t i=1; i<nmtools::len(c_value_a); i++) {
                                auto v_i = at(c_value_a,i);
                                max = (v_i > max ? v_i : max);
                                min = (v_i < min ? v_i : min);
                            }
                            return nmtools_tuple{min,max};
                        }();
                        constexpr auto min_dim = nmtools::get<0>(minmax);
                        constexpr auto max_dim = nmtools::get<1>(minmax);
                        if constexpr (min_dim == 1) {
                            // bail-out, can't decide max at compile time
                            return as_value_v<type>;
                        } else {
                            using type = nmtools_array<clipped_integer_t<index_t,0,max_dim>,(size_t)len_a>;
                            return as_value_v<type>;
                        }
                        #endif
                    } else {
                        return as_value_v<type>;
                    }
                } else if constexpr ((len_b > 0) && !is_fail_v<decltype(b_size_a)>) {
                    using type [[maybe_unused]] = array::static_vector<index_t,(len_b > b_size_a ? len_b : b_size_a)>;
                    if constexpr (!is_fail_v<decltype(c_value_b)> && (len_b >= b_size_a)) {
                        // NOTE: the following tries to deduce as bounded-shape to be able to compute at compile-time
                        // but the runtime part index::broadcast_shape is still not support it yet
                        // because of unhandled mixed constant index vs runtime index when computing result
                        #if 0
                        return meta::template_reduce<len_b>([&](auto init, auto index){
                            using init_type = type_t<decltype(init)>;
                            constexpr auto I = at(c_value_b,index);
                            // if there exists "1", bail out, we can't know the value at compile-time
                            if constexpr ((I > 1) && is_tuple_v<init_type>) {
                                using type = append_type_t<init_type,clipped_size_t<I>>;
                                return as_value_v<type>;
                            } else {
                                return as_value_v<type>;
                            }
                        }, as_value_v<nmtools_tuple<>>);
                        #else
                        // get max num and return clipped index packed in array instead of tuple
                        constexpr auto minmax = [&](){
                            auto min = at(c_value_b,0);
                            auto max = at(c_value_b,0);
                            for (size_t i=1; i<nmtools::len(c_value_b); i++) {
                                auto v_i = at(c_value_b,i);
                                max = (v_i > max ? v_i : max);
                                min = (v_i < min ? v_i : min);
                            }
                            return nmtools_tuple{min,max};
                        }();
                        constexpr auto min_dim = nmtools::get<0>(minmax);
                        constexpr auto max_dim = nmtools::get<1>(minmax);
                        if constexpr (min_dim == 1) {
                            return as_value_v<type>;
                        } else {
                            using type = nmtools_array<clipped_integer_t<index_t,0,max_dim>,(size_t)len_b>;
                            return as_value_v<type>;
                        }
                        #endif
                    } else {
                        return as_value_v<type>;
                    }
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
            else {
                return as_value_v<error::BROADCAST_SHAPE_UNSUPPORTED<ashape_t,bshape_t>>;
            }
        }();

        using type = type_t<decltype(vtype)>;
    }; // resolve_optype

    template <typename dst_shape_t, typename a_size_t, typename...other_sizes_t>
    struct resolve_optype<
        void, index::broadcast_size_t, dst_shape_t, a_size_t, other_sizes_t...
    >
    {
        using other_size_types = type_list<other_sizes_t...>;

        static constexpr auto vtype = [](){
            [[maybe_unused]] constexpr auto other_is_all_none = (is_same_v<remove_cvref_t<other_sizes_t>,ct<1ul>> && ...);
            if constexpr (is_maybe_v<a_size_t>) {
                using a_size_type = resolve_optype_t<index::broadcast_size_t,dst_shape_t,get_maybe_type_t<a_size_t>>;
                // TODO: handle other_sizes_t...
                // TODO: find upper bounds from other_sizes_t...
                return as_value_v<nmtools_maybe<a_size_type>>;
            } else if constexpr (is_constant_index_array_v<dst_shape_t>) {
                constexpr auto size = index::product(to_value_v<dst_shape_t>);
                using type = ct<size>;
                return as_value_v<type>;
            } else if constexpr (is_clipped_index_array_v<dst_shape_t>) {
                constexpr auto size = index::product(to_value_v<dst_shape_t>);
                using type = clipped_size_t<size>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_v<a_size_t> && other_is_all_none) {
                using type = ct<a_size_t::value>;
                return as_value_v<type>;
            } else if constexpr (is_clipped_integer_v<a_size_t> && other_is_all_none) {
                using type = clipped_size_t<a_size_t::max>;
                return as_value_v<type>;
            } else if constexpr (is_index_v<a_size_t>) {
                return template_reduce<sizeof...(other_sizes_t)>([](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    using type_i = at_t<other_size_types,I>;
                    using init_t = type_t<decltype(init)>;
                    if constexpr (is_same_v<init_t,ct<1ul>> && (is_constant_index_v<type_i> || is_clipped_integer_v<type_i>)) {
                        return as_value_v<type_i>;
                    } else if constexpr ((is_constant_index_v<init_t> || is_clipped_integer_v<init_t>) && is_same_v<type_i,ct<1ul>>) {
                        return as_value_v<init_t>;
                    } else {
                        return as_value_v<size_t>;
                    }
                }, as_value_v<a_size_t>);
            } else {
                return as_value_v<error::BROADCAST_SIZE_UNSUPPORTED<dst_shape_t, a_size_t, other_sizes_t...>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_BROADCAST_SHAPE_HPP