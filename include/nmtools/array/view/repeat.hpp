#ifndef NMTOOLS_ARRAY_VIEW_REPEAT_HPP
#define NMTOOLS_ARRAY_VIEW_REPEAT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/indexing.hpp"
#include "nmtools/utility/shape.hpp"

#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/repeat.hpp"

namespace nmtools::view
{
    template <typename src_shape_t, typename repeats_t, typename axis_t, typename src_size_t>
    struct repeat_t
        : base_indexer_t<repeat_t<src_shape_t,repeats_t,axis_t,src_size_t>>
    {
        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;
        using src_size_type  = meta::fwd_attribute_t<src_size_t>;
        using repeats_type   = meta::fwd_attribute_t<repeats_t>;
        using axis_type      = meta::fwd_attribute_t<axis_t>;
        using dst_shape_type = meta::resolve_optype_t<index::shape_repeat_t,src_shape_type,repeats_type,axis_type>;

        // TODO: support repeat size inference
        // using dst_size_type  = src_size_type;
        using dst_size_type = decltype(index::product(meta::declval<dst_shape_type>()));

        static constexpr auto n_inputs  = 1;
        static constexpr auto n_outputs = 1;

        const src_shape_type src_shape;
        const repeats_type   repeats;
        const axis_type      axis;
        const src_size_type  src_size;
        const dst_shape_type dst_shape;
        const dst_size_type  dst_size;

        constexpr repeat_t(const src_shape_t& src_shape_
            , const repeats_t& repeats_
            , const axis_t& axis_
            , const src_size_t& src_size_
        )
            : src_shape(fwd_attribute(src_shape_))
            , repeats(fwd_attribute(repeats_))
            , axis(fwd_attribute(axis_))
            , src_size(fwd_attribute(src_size_))
            , dst_shape(index::shape_repeat(src_shape,repeats,axis))
            , dst_size(index::product(dst_shape))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            auto src_indices = index::repeat(src_shape,indices,repeats,axis);
            return src_indices;
        }

        template <typename...args_t>
        constexpr auto operator==(repeat_t<args_t...> other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(repeats,other.repeats)
                && utils::isequal(axis,other.axis)
            ;
        }
    }; // repeat_t

    template <typename src_shape_t, typename src_size_t, typename repeats_t, typename axis_t>
    constexpr auto repeater(const src_shape_t& src_shape, const repeats_t& repeats, const axis_t& axis, const src_size_t& src_size)
    {
        auto m_dst_shape = index::shape_repeat(src_shape,repeats,axis);
        if constexpr (meta::is_maybe_v<decltype(m_dst_shape)>) {
            using result_t = decltype(repeat_t{unwrap(src_shape),unwrap(repeats),unwrap(axis),unwrap(src_size)});
            using return_t = nmtools_maybe<result_t>;
            if (static_cast<bool>(m_dst_shape)) {
                return return_t{repeat_t{unwrap(src_shape),unwrap(repeats),unwrap(axis),unwrap(src_size)}};
            } else {
                return return_t{meta::Nothing};
            }
        } else {
            return repeat_t{unwrap(src_shape),unwrap(repeats),unwrap(axis),unwrap(src_size)};
        }
    }

    template <typename array_t, typename repeats_t, typename axis_t>
    constexpr auto repeat(const array_t& array, const repeats_t& repeats, const axis_t& axis)
    {
        auto f = [](const auto& array, const auto& repeats, const auto& axis){
            auto src_shape = shape<true>(array);
            auto src_size  = size<true>(array);
            auto indexer   = repeater(src_shape,repeats,axis,src_size);
            return indexing(array,indexer);
        };
        return lift_indexing(f,array,repeats,axis);
    }
} // namespace nmtools::view

namespace nmtools::array
{
    template <typename...args_t, auto max_dim>
    struct as_static_t<
        view::repeat_t<args_t...>, max_dim
    > {
        using attribute_type = view::repeat_t<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto src_shape = as_static<max_dim>(attribute.src_shape);
            auto src_size  = as_static<max_dim>(attribute.src_size);
            auto repeats   = as_static<max_dim>(attribute.repeats);
            auto axis      = as_static<max_dim>(attribute.axis);
            return view::repeater(src_shape,repeats,axis,src_size);
        }
    };
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        view::repeat_t<args_t...>, fmt_string_t<fmt_args...>
    >
    {
        using result_type = nmtools_string;

        auto operator()(const view::repeat_t<args_t...>& kwargs) const noexcept
        {
            nmtools_string str;
            str += "repeat";
            str += "{";
            str += ".src_shape="; str += to_string(kwargs.src_shape,Compact);
            str += ",.repeats=";  str += to_string(kwargs.repeats,Compact);
            str += ",.axis=";     str += to_string(kwargs.axis,Compact);
            str += ",.src_size="; str += to_string(kwargs.src_size,Compact);
            str += "}";
            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_REPEAT_HPP