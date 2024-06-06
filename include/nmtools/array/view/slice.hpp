#ifndef NMTOOLS_ARRAY_VIEW_SLICE_HPP
#define NMTOOLS_ARRAY_VIEW_SLICE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/indexing.hpp"
#include "nmtools/array/index/slice.hpp"

namespace nmtools::view
{
    template <typename src_shape_t, typename slices_t, typename src_size_t>
    struct slice_t
        : base_indexer_t<slice_t<src_shape_t,slices_t,src_size_t>>
    {
        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;
        using src_size_type  = meta::fwd_attribute_t<src_size_t>;

        // TODO: fix fwd_attribute
        // using slices_type = meta::fwd_attribute_t<slices_t>;
        using slices_type = slices_t;

        using dst_shape_type = decltype(index::apply_shape_slice(meta::declval<src_shape_type>(),meta::declval<slices_type>()));
        // TODO: support slice size inference
        // using dst_size_type  = src_size_type;
        using dst_size_type = decltype(index::product(meta::declval<dst_shape_type>()));

        static constexpr auto n_inputs  = 1;
        static constexpr auto n_outputs = 1;

        // currently non-const because split use push_back
        // TODO: update split to use emplace_back and make this const
        src_shape_type src_shape;
        slices_type    slices;
        src_size_type  src_size;
        dst_shape_type dst_shape;
        dst_size_type  dst_size;

        constexpr slice_t(const src_shape_t& src_shape_
            , const slices_t& slices_
            , const src_size_t& src_size_
        )
            : src_shape(fwd_attribute(src_shape_))
            // TODO: fix fwd_attribute
            // , slices(fwd_attribute(slices_))
            , slices(slices_)
            , src_size(fwd_attribute(src_size_))
            , dst_shape(fwd_attribute(index::apply_shape_slice(src_shape,slices)))
            , dst_size(index::product(dst_shape))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            auto src_indices = index::apply_slice(indices,src_shape,slices);
            return src_indices;
        }

        template <typename...args_t>
        constexpr auto operator==(slice_t<args_t...> other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(dst_shape,other.dst_shape)
                // TODO: also check if the slices is the same
            ;
        }
    };

    template <typename src_shape_t, typename src_size_t, typename slices_t>
    constexpr auto slicer(const src_shape_t& src_shape, const slices_t& slices, const src_size_t& src_size)
    {
        auto m_dst_shape = index::apply_shape_slice(src_shape,slices);
        if constexpr (meta::is_maybe_v<decltype(m_dst_shape)>) {
            using result_t = decltype(slice_t{unwrap(src_shape),unwrap(slices),unwrap(src_size)});
            using return_t = nmtools_maybe<result_t>;
            return (has_value(m_dst_shape)
                ? return_t{result_t{unwrap(src_shape),unwrap(slices),unwrap(src_size)}}
                : return_t{meta::Nothing}
            );
        } else {
            return slice_t{unwrap(src_shape),unwrap(slices),unwrap(src_size)};
        }
    }

    template <typename array_t, typename slices_t>
    constexpr auto apply_slice(const array_t& array, const slices_t& slices)
    {
        auto f = [](const auto& array, const auto& slices){
            auto src_shape = shape<true>(array);
            auto src_size  = size<true>(array);
            auto indexer   = slicer(src_shape,slices,src_size);
            return indexing(array,indexer);
        };
        return lift_indexing(f,array,slices);
    } // apply_slice

    template <typename array_t, typename...slices_t>
    constexpr auto slice(const array_t& array, slices_t...slices)
    {
        auto slices_pack = nmtools_tuple{slices...};
        return apply_slice(array,slices_pack);
    } // slice
} // namespace nmtools::view

namespace nmtools::array
{
    template <typename...args_t, auto max_dim>
    struct as_static_t<
        view::slice_t<args_t...>, max_dim
    > {
        using attribute_type = view::slice_t<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto src_shape = as_static<max_dim>(attribute.src_shape);
            auto src_size  = as_static<max_dim>(attribute.src_size);
            auto slices = attribute.slices;
            // TODO: support fwd_attribute for slices
            // auto slices    = as_static<max_dim>(attribute.slices);
            return view::slicer(src_shape,slices,src_size);
        }
    };
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        view::slice_t<args_t...>, fmt_string_t<fmt_args...>
    >
    {
        using result_type = nmtools_string;

        auto operator()(const view::slice_t<args_t...>& kwargs) const noexcept
        {
            nmtools_string str;
            str += "slice{";
            str += ".src_shape="; str += to_string(kwargs.src_shape,Compact);
            str += ",.slices=";   str += NMTOOLS_TYPENAME_TO_STRING(decltype(kwargs.slices));
            // TODO: support to_string for slices
            // str += ",.slices=";   str += apply_to_string(kwargs.slices,Compact);
            str += ",.src_size="; str += to_string(kwargs.src_size,Compact);
            str += "}";
            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_SLICE_HPP