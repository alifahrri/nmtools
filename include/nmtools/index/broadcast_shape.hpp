#ifndef NMTOOLS_ARRAY_INDEX_BROADCAST_SHAPE_HPP
#define NMTOOLS_ARRAY_INDEX_BROADCAST_SHAPE_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/stl.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/unwrap.hpp"
#include "nmtools/index/ref.hpp"
#include "nmtools/index/max.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/index/sum.hpp"
#include "nmtools/index/where.hpp"

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
        using element_t [[maybe_unused]] = meta::remove_cvref_t<meta::get_index_element_type_t<result_t>>;

        if constexpr (meta::is_constant_index_array_v<result_t>) {
            // do nothing, already computed at compile-time
            // the type holds broadcasted shape
            return result_t{};
        } else {
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

            if constexpr (!is_none_v<ashape_t> && !is_none_v<bshape_t>) {
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
                    for (nm_size_t i=0; i<(nm_size_t)adim; i++)
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
        // TODO: check if results is constant index, don't make it maybe type if so
        auto result_ = broadcast_shape(ashape,bshape);
        using result_t  = decltype(result_);
        using results_t = decltype(broadcast_shape(result_,cshape,other_shapes...));
        using return_t  = meta::conditional_t<meta::is_maybe_v<results_t>,results_t,nmtools_maybe<results_t>>;
        if constexpr (meta::is_maybe_v<result_t>) {
            return (result_ ?
                return_t{broadcast_shape(*result_,cshape,other_shapes...)}
                : return_t{meta::Nothing}
            );
        } else {
            return return_t{broadcast_shape(result_,cshape,other_shapes...)};
        }
    } // broadcast_shape

    struct broadcast_size_t {};

    template <typename dst_shape_t, typename a_size_t, typename b_size_t, typename...other_sizes_t>
    constexpr auto broadcast_size([[maybe_unused]] const dst_shape_t& dst_shape
        , [[maybe_unused]] a_size_t a_size
        , [[maybe_unused]] b_size_t b_size
        , [[maybe_unused]] other_sizes_t... other_sizes)
    {
        if constexpr (meta::is_maybe_v<dst_shape_t>) {
            using result_t = decltype(broadcast_size(unwrap(dst_shape),a_size,b_size,other_sizes...));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (dst_shape ?
                return_t{broadcast_size(unwrap(dst_shape),a_size,b_size,other_sizes...)}
                : return_t{meta::Nothing}
            );
        } else {
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
        }
    } // broadcast_size

} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        // error type for in-compatible shapes
        template <typename...>
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
            // TODO: deduce index_t from ashape and bshape
            using index_t [[maybe_unused]] = nm_size_t;
            if constexpr (!(is_index_array_v<ashape_t> || is_none_v<ashape_t>)
                || !(is_index_array_v<bshape_t> || is_none_v<bshape_t>)
            ) {
                using type = error::BROADCAST_SHAPE_UNSUPPORTED<ashape_t,bshape_t>;
                return as_value_v<type>;
            } else if constexpr (is_none_v<ashape_t> && is_none_v<bshape_t>){
                using type = none_t;
                return as_value_v<type>;
            } else if constexpr  (
                (is_constant_index_array_v<ashape_t> || is_none_v<ashape_t>)
                && (is_constant_index_array_v<bshape_t> || is_none_v<bshape_t>)
            ) {
                constexpr auto ashape = to_value_v<ashape_t>;
                constexpr auto bshape = to_value_v<bshape_t>;
                constexpr auto result = index::broadcast_shape(ashape,bshape);
                if constexpr (has_value(result)) {
                    using nmtools::at, nmtools::len;
                    constexpr auto DIM = len(unwrap(result));
                    static_assert( is_index_v<decltype(DIM)>, "internal error" );
                    return meta::template_reduce<DIM>([&](auto init, auto index){
                        using init_t = type_t<decltype(init)>;
                        constexpr auto I = decltype(index)::value;
                        constexpr auto shape_i = at(unwrap(result),I);
                        using type = append_type_t<init_t,ct<(nm_size_t)shape_i>>;
                        return as_value_v<type>;
                    }, as_value_v<nmtools_tuple<>>);
                } else {
                    using type = error::BROADCAST_SHAPE_ERROR<ashape_t,bshape_t>;
                    return as_value_v<type>;
                }
            } else {
                // TODO: return maybe constant index if ashape or bshape is constant index (without 1 as entry)
                [[maybe_unused]] constexpr auto A_DIM = len_v<ashape_t>;
                [[maybe_unused]] constexpr auto B_DIM = len_v<bshape_t>;
                [[maybe_unused]] constexpr auto A_B_DIM = bounded_size_v<ashape_t>;
                [[maybe_unused]] constexpr auto B_B_DIM = bounded_size_v<bshape_t>;
                if constexpr ((A_DIM > 0) && (B_DIM > 0)) {
                    constexpr auto MAX_DIM = (A_DIM > B_DIM ? A_DIM : B_DIM);
                    using type = nmtools_array<index_t,MAX_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(A_B_DIM)> && !is_fail_v<decltype(B_B_DIM)>) {
                    constexpr auto MAX_DIM = (A_B_DIM > B_B_DIM ? A_B_DIM : B_B_DIM);
                    using type = nmtools_static_vector<index_t,MAX_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(A_B_DIM)> && is_none_v<bshape_t>) {
                    // TODO: try to deduce for fixed dim
                    using type = nmtools_static_vector<index_t,A_B_DIM>;
                    return as_value_v<type>;
                } else if constexpr (is_none_v<ashape_t> && !is_fail_v<decltype(B_B_DIM)>) {
                    using type = nmtools_static_vector<index_t,B_B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                }
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