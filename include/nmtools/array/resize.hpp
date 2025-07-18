#ifndef NMTOOLS_ARRAY_VIEW_RESIZE_HPP
#define NMTOOLS_ARRAY_VIEW_RESIZE_HPP

#include "nmtools/core/indexing.hpp"
#include "nmtools/index/resize.hpp"
#include "nmtools/utility/as_static.hpp"
#include "nmtools/utility/unwrap.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/utility/isequal/isequal.hpp"

namespace nmtools::view
{
    template <typename src_shape_t, typename dst_shape_t>
    struct resize_t
        : base_indexer_t<resize_t<src_shape_t,dst_shape_t>>
    {
        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;
        using dst_shape_type = meta::resolve_optype_t<index::shape_resize_t,src_shape_type,dst_shape_t>;
        using dst_size_type  = meta::resolve_optype_t<index::product_t,dst_shape_type>;
        using src_size_type  = meta::resolve_optype_t<index::product_t,src_shape_type>;

        static constexpr auto n_inputs  = 1;
        static constexpr auto n_outputs = 1;

        src_shape_type src_shape;
        dst_shape_type dst_shape;

        constexpr resize_t(const src_shape_t& src_shape
            , const dst_shape_t& dst_shape
        )
            : src_shape(fwd_attribute(src_shape))
            , dst_shape(index::shape_resize(src_shape,dst_shape))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            auto src_indices = index::resize(indices,src_shape,unwrap(dst_shape));
            return src_indices;
        }

        template <typename...args_t>
        constexpr auto operator==(resize_t<args_t...> other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(dst_shape,other.dst_shape)
            ;
        }
    }; // resize_t

    template <typename array_t, typename dst_shape_t>
    constexpr auto make_resize(const array_t& array, const dst_shape_t& dst_shape)
    {
        auto src_shape = shape<true>(array);
        auto indexer = resize_t{src_shape,dst_shape};
        return indexing(array,indexer);
    }

    template <typename array_t, typename dst_shape_t>
    constexpr auto resize(const array_t& array, const dst_shape_t& dst_shape)
    {
        auto f = [](const auto&...args){
            return make_resize(args...);
        };
        return lift_indexing(f,array,dst_shape);
    }
} // namespace nmtools::view

namespace nmtools
{
    template <typename...args_t, auto max_dim>
    struct as_static_t<
        view::resize_t<args_t...>, max_dim
    >
    {
        using attribute_type = view::resize_t<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto src_shape = as_static<max_dim>(attribute.src_shape);
            // TODO: error handling
            auto dst_shape = as_static<max_dim>(unwrap(attribute.dst_shape));
            return view::resize_t{src_shape,dst_shape};
        }
    };
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        view::resize_t<args_t...>, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(const view::resize_t<args_t...>& kwargs) const noexcept
        {
            nmtools_string str;
            str += "resize";
            str += "{";
            str += ".src_shape=";
            str += utils::to_string(kwargs.src_shape,Compact);
            str += ",";
            str += ".dst_shape=";
            str += utils::to_string(kwargs.dst_shape,Compact);
            str += "}";
            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_RESIZE_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_RESIZE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_RESIZE_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/array/resize.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct resize_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::resize(args...);
            }
        };
    }

    constexpr inline auto resize = functor_t{unary_fmap_t<fun::resize_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_RESIZE_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_RESIZE_HPP
#define NMTOOLS_ARRAY_ARRAY_RESIZE_HPP

#include "nmtools/array/resize.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename dst_shape_t>
    constexpr auto resize(const array_t& array, const dst_shape_t& dst_shape,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto resized = view::resize(array,dst_shape);
        return eval(resized
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // resize
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_RESIZE_HPP