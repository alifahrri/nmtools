#ifndef NMTOOLS_ARRAY_VIEW_TRANSPOSE_HPP
#define NMTOOLS_ARRAY_VIEW_TRANSPOSE_HPP

#include "nmtools/constants.hpp"

#include "nmtools/array/index/transpose.hpp"
#include "nmtools/array/index/scatter.hpp"
#include "nmtools/array/index/reverse.hpp"

#include "nmtools/utils/isequal/isequal.hpp"
#include "nmtools/array/view/indexing.hpp"
#include "nmtools/array/as_static.hpp"
#include "nmtools/utils/to_string/to_string.hpp"

namespace nmtools::view
{
    template <typename src_shape_t, typename axes_t=none_t, typename src_size_t=none_t>
    struct transpose_t
        : base_indexer_t<transpose_t<src_shape_t,axes_t,src_size_t>>
    {
        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;
        using axes_type = meta::fwd_attribute_t<axes_t>;
        using src_size_type = meta::fwd_attribute_t<src_size_t>;
        using dst_shape_type = meta::resolve_optype_t<index::shape_transpose_t,src_shape_type,axes_type>;
        // for transpose view, the resulting shape is the same as src
        using dst_size_type = src_size_type;

        static constexpr auto n_inputs  = 1;
        static constexpr auto n_outputs = 1;

        const src_shape_type src_shape;
        const axes_type axes;
        const src_size_type src_size;
        const dst_size_type dst_size;
        const dst_shape_type dst_shape;

        constexpr transpose_t(const src_shape_t& src_shape
            , const axes_t& axes=axes_t{}
            , const src_size_t& src_size=src_size_t{}
        )
            : src_shape(fwd_attribute(src_shape))
            , axes(fwd_attribute(axes))
            , src_size(fwd_attribute(src_size))
            , dst_size(src_size)
            , dst_shape(index::shape_transpose(src_shape,axes))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            // TODO: move to index/transpose.hpp
            if constexpr (is_none_v<axes_type>) {
                return index::reverse(indices);
            } else {
                return index::scatter(indices, axes);
            }
        }

        template <typename...args_t>
        constexpr auto operator==(transpose_t<args_t...> other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(dst_shape,other.dst_shape)
                && utils::isequal(axes,other.axes)
            ;
        }
    }; // transpose_t

    template <typename array_t, typename axes_t=none_t>
    constexpr auto make_transpose(const array_t& array, const axes_t& axes=axes_t{})
    {
        auto src_shape = shape<true>(array);
        auto src_size  = size<true>(array);
        auto indexer = transpose_t{src_shape,axes,src_size};
        return indexing(array,indexer);
    }

    template <typename array_t, typename axes_t=none_t>
    constexpr auto transpose(const array_t& array, const axes_t& axes=axes_t{})
    {
        auto f = [](const auto&...args){
            return make_transpose(args...);
        };
        return lift_indexing(f,array,axes);
    }
} // namespace nmtools::view

namespace nmtools::array
{
    template <typename...args_t, auto max_dim>
    struct as_static_t<
        view::transpose_t<args_t...>, max_dim
    > {
        using attribute_type = view::transpose_t<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto src_shape = as_static<max_dim>(attribute.src_shape);
            auto axes      = as_static<max_dim>(attribute.axes);
            auto src_size  = as_static<max_dim>(attribute.src_size);
            return view::transpose_t{src_shape,axes,src_size};
        }
    };
} // namespace nmtools::array

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        view::transpose_t<args_t...>, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(const view::transpose_t<args_t...>& kwargs) const noexcept
        {
            nmtools_string str;
            str += "transpose{";
            str += ".src_shape=";
            str += to_string(kwargs.src_shape,Compact);
            str += ",.axes=";
            str += to_string(kwargs.axes,Compact);
            str += ",.src_size=";
            str += to_string(kwargs.src_size,Compact);
            str += "}";
            return str;
        }

    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_TRANSPOSE_HPP