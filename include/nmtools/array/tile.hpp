#ifndef NMTOOLS_ARRAY_VIEW_TILE_HPP
#define NMTOOLS_ARRAY_VIEW_TILE_HPP

#include "nmtools/utility.hpp"

#include "nmtools/core/indexing.hpp"
#include "nmtools/utility/as_static.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/utility/isequal/isequal.hpp"

/*************************************************************************** */

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type of shape_tile op
     * 
     */
    struct shape_tile_t {};

    /**
     * @brief compute the resulting shape for tile view
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
        using result_t = resolve_optype_t<shape_tile_t,shape_t,reps_t>;
        auto ret = result_t {};

        if constexpr (!is_fail_v<result_t>
            && !is_constant_index_array_v<result_t>
        ) {
            [[maybe_unused]] auto n_shape = (nm_index_t)len(shape);
            [[maybe_unused]] auto n_reps  = (nm_index_t)len(reps);

            if constexpr (is_resizable_v<result_t>) {
                ret.resize(n_shape > n_reps ? n_shape : n_reps);
            }

            constexpr auto N_RES = len_v<result_t>;

            if constexpr (N_RES > 0) {
                template_for<N_RES>([&](auto i){
                    [[maybe_unused]] constexpr auto N_SHAPE = (nm_index_t)len_v<shape_t>;
                    [[maybe_unused]] constexpr auto N_REPS  = (nm_index_t)len_v<reps_t>;
                    constexpr auto I  = (nm_index_t)decltype(i)::value;
                    constexpr auto SI = -(I+1);
                    auto si = ct_v<SI>;
                    using ret_i_t = decltype(at(ret,si));
                    if constexpr (!is_constant_index_v<ret_i_t>) {
                        if constexpr (
                            ((N_SHAPE-I) > 0)
                            && ((N_REPS-I) > 0)
                        ) {
                            if (has_value(at(shape,si)) && has_value(at(reps,si))) {
                                at(ret,si) = at(shape,si) * at(reps,si);
                            }
                        } else if constexpr ((N_SHAPE-I) > 0) {
                            if ((n_reps-I) > 0) {
                                if (has_value(at(shape,si)) && has_value(at(reps,SI))) {
                                    at(ret,si) = at(shape,si) * at(reps,SI);
                                }
                            } else {
                                if (has_value(at(shape,si))) {
                                    at(ret,si) = at(shape,si);
                                }
                            }
                        } else if constexpr ((N_REPS-I) > 0) {
                            if ((n_shape-I) > 0) {
                                if (has_value(at(shape,SI)) && has_value(at(reps,si))) {
                                    at(ret,si) = at(shape,SI) * at(reps,si);
                                }
                            } else {
                                if (has_value(at(reps,si))) {
                                    at(ret,si) = at(reps,si);
                                }
                            }
                        } else {
                            // NOT possible? result_t derived from either shape or reps, one of them must be fixed len
                        }
                    }
                });
            } else {
                auto n_res = len(ret);
                for (nm_index_t i=0; i<(nm_index_t)n_res; i++) {
                    auto si = -(i+1);
                    if (((n_shape-i) > 0) && ((n_reps-i) > 0)) {
                        if (has_value(at(shape,si)) && has_value(at(reps,si))) {
                            at(ret,si) = at(shape,si) * at(reps,si);
                        }
                    } else if ((n_shape-i) > 0) {
                        if (has_value(at(shape,si))) {
                            at(ret,si) = at(shape,si);
                        }
                    } else if ((n_reps-i) > 0) {
                        if (has_value(at(reps,si))) {
                            at(ret,si) = at(reps,si);
                        }
                    } else {
                        // do nothing
                    }
                }
            }
        }

        return ret;
    } // shape_tile
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_TILE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    // TODO: compute at compile-time whenever possible
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
        static constexpr auto value = [](){
            if constexpr (!is_index_array_v<shape_t>
                || !is_index_array_v<reps_t>
            ) {
                using type = error::SHAPE_TILE_UNSUPPORTED<shape_t,reps_t>;
                return as_value_v<type>;
            } else if constexpr (
                (is_constant_index_array_v<shape_t> || is_mixed_index_array_v<shape_t>)
                && (is_constant_index_array_v<reps_t> || is_mixed_index_array_v<reps_t>)
            ) {
                constexpr auto shape  = to_value_v<shape_t>;
                constexpr auto reps   = to_value_v<reps_t>;
                constexpr auto result = index::shape_tile(shape, reps);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_type = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    constexpr auto res_i = at(result,I);
                    if constexpr (has_value(res_i)) {
                        using type = append_type_t<init_type,ct<unwrap(res_i)>>;
                        return as_value_v<type>;
                    } else {
                        using type = append_type_t<init_type,nm_size_t>;
                        return as_value_v<type>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto N_SHAPE = len_v<shape_t>;
                constexpr auto N_REPS  = len_v<reps_t>;
                [[maybe_unused]] constexpr auto MAX_N_SHAPE = max_len_v<shape_t>;
                [[maybe_unused]] constexpr auto MAX_N_REPS  = max_len_v<reps_t>;
                using index_t = conditional_t<
                    is_nullable_index_array_v<shape_t>
                    || is_nullable_index_array_v<reps_t>
                    , null_int
                    , get_index_element_type_t<shape_t>
                >;
                if constexpr ((N_SHAPE > 0) && (N_REPS > 0)) {
                    constexpr auto N = N_SHAPE > N_REPS ? N_SHAPE : N_REPS;
                    using type = nmtools_array<index_t,N>;
                    return as_value_v<type>;
                } else if constexpr ((MAX_N_SHAPE > 0) && (MAX_N_REPS > 0)) {
                    constexpr auto N = MAX_N_SHAPE > MAX_N_REPS ? MAX_N_SHAPE : MAX_N_REPS;
                    using type = nmtools_static_vector<index_t,N>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(value)>;
    }; // resolve_optype
} // namespace nmtools::meta

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
        using return_t = resolve_optype_t<tile_t,shape_t,reps_t,indices_t>;

        auto ret = return_t {};

        // len(indices) == max(len(shape),len(reps))
        auto m = len(shape);
        auto n = len(indices);
        // clang (android & emscripten) complains about ambiguous call
        auto s = [&]()->nm_size_t{ // quick workaround for inconsistent type error
            // TODO: better deduction
            if ((nm_size_t)m > (nm_size_t)n) {
                return m;
            } else {
                return n;
            }
        }();

        if constexpr (is_resizable_v<return_t>)
            ret.resize(len(shape));
        
        // use int since ai/bi may be negative
        for (int i=0; i<(int)s; i++) {
            int ai = m - i - 1;
            int bi = n - i - 1;
            if (ai >= 0) {
                auto idx = at(indices,bi);
                auto s = at(shape,ai);
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
        template <typename...>
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
            if constexpr (
                is_constant_index_array_v<shape_t>
                || is_clipped_index_array_v<shape_t>
            ) {
                // return as_value_v<error::INDEX_TILE_UNSUPPORTED<shape_t,reps_t,indices_t>>;
                using index_t = get_index_element_type_t<shape_t>;
                using type = nmtools_array<index_t,len_v<shape_t>>;
                return as_value_v<type>;
            } else if constexpr (is_fixed_index_array_v<shape_t>) {
                return as_value_v<transform_bounded_array_t<shape_t>>;
            } else if constexpr (is_index_array_v<shape_t>) {
                return as_value_v<shape_t>;
            } else {
                return as_value_v<error::INDEX_TILE_UNSUPPORTED<shape_t,reps_t,indices_t>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype
} // namespace nmtools::meta

/*************************************************************************** */

namespace nmtools::view
{
    template <typename src_shape_t, typename reps_t>
    struct tile_t
        : base_indexer_t<tile_t<src_shape_t,reps_t>>
    {
        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;
        using reps_type      = meta::fwd_attribute_t<reps_t>;
        using dst_shape_type = meta::resolve_optype_t<index::shape_tile_t,src_shape_type,reps_type>;

        using dst_size_type  = meta::resolve_optype_t<index::product_t,dst_shape_type>;
        using src_size_type  = meta::resolve_optype_t<index::product_t,src_shape_type>;

        static constexpr auto n_inputs  = 1;
        static constexpr auto n_outputs = 1;

        const src_shape_type src_shape;
        const reps_type reps;
        const dst_shape_type dst_shape;

        constexpr tile_t(const src_shape_t& src_shape
            , const reps_t& reps
        )
            : src_shape(fwd_attribute(src_shape))
            , reps(fwd_attribute(reps))
            , dst_shape(index::shape_tile(src_shape,reps))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            auto src_indices = index::tile(src_shape,reps,indices);
            return src_indices;
        }

        template <typename...args_t>
        constexpr auto operator==(tile_t<args_t...> other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(dst_shape,other.dst_shape)
                && utils::isequal(reps,other.reps)
            ;
        }
    }; // tile_t

    template <typename src_shape_t, typename reps_t>
    constexpr auto tile_indexer(const src_shape_t& src_shape, const reps_t& reps)
    {
        if constexpr (meta::is_maybe_v<src_shape_t> || meta::is_maybe_v<reps_t>) {
            using result_t = decltype(tile_indexer(unwrap(src_shape),unwrap(reps)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(src_shape) && has_value(reps)
                ? return_t{tile_indexer(unwrap(src_shape),unwrap(reps))}
                : return_t{meta::Nothing}
            );
        } else {
            auto indexer = tile_t{src_shape,reps};
            return indexer;
        }
    } // tile_indexer

    template <typename array_t, typename reps_t>
    constexpr auto tile(const array_t& array, const reps_t& reps)
    {
        auto f = [](const auto& array, const auto& reps){
            auto src_shape = shape<true>(array);
            auto indexer = tile_indexer(src_shape,reps);
            return indexing(array,indexer);
        };
        return lift_indexing(f,array,reps);
    } // tile
} // namespace nmtools::view

namespace nmtools
{
    template <typename...args_t, auto max_dim>
    struct as_static_t<
        view::tile_t<args_t...>, max_dim
    >{
        using attribute_type = view::tile_t<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto src_shape = as_static<max_dim>(attribute.src_shape);
            auto reps = as_static<max_dim>(attribute.reps);
            return view::tile_indexer(src_shape,reps);
        }
    };
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        view::tile_t<args_t...>, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(const view::tile_t<args_t...>& kwargs) const noexcept
        {
            nmtools_string str;
            str += "tile";
            str += "{";
            str += ".src_shape=";
            str += to_string(kwargs.src_shape,Compact);
            str += ",.reps=";
            str += to_string(kwargs.reps,Compact);
            str += "}";
            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_TILE_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_TILE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_TILE_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/array/tile.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct tile_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::tile(args...);
            }
        };
    }

    constexpr inline auto tile = functor_t{unary_fmap_t<fun::tile_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_TILE_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_TILE_HPP
#define NMTOOLS_ARRAY_ARRAY_TILE_HPP

#include "nmtools/array/tile.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly evaluate tile op.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam reps_t 
     * @param array     input array
     * @param reps      number of repetitions
     * @param context   evaluation context
     * @param output    optional output
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=default_context_t<>,
        typename array_t, typename reps_t>
    constexpr auto tile(const array_t& array, const reps_t& reps,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto tiled = view::tile(array,reps);
        return eval(tiled
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
        );
    } // tile
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_TILE_HPP