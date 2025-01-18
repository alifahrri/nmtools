#ifndef NMTOOLS_ARRAY_VIEW_TILE_HPP
#define NMTOOLS_ARRAY_VIEW_TILE_HPP

#include "nmtools/core/indexing.hpp"
#include "nmtools/array/index/tile.hpp"
#include "nmtools/utility/as_static.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/utility/isequal/isequal.hpp"

namespace nmtools::view
{
    template <typename src_shape_t, typename reps_t>
    struct tile_t
        : base_indexer_t<tile_t<src_shape_t,reps_t>>
    {
        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;
        using reps_type = meta::fwd_attribute_t<reps_t>;
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

namespace nmtools::array
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
#include "nmtools/array/indexing.hpp"
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

namespace nmtools::array
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
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename reps_t>
    constexpr auto tile(const array_t& array, const reps_t& reps,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto tiled = view::tile(array,reps);
        return eval(tiled
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // tile
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_TILE_HPP