#ifndef NMTOOLS_ARRAY_VIEW_SLIDING_WINDOW_HPP
#define NMTOOLS_ARRAY_VIEW_SLIDING_WINDOW_HPP

#include "nmtools/array/view/indexing.hpp"
#include "nmtools/array/index/sliding_window.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/utility/unwrap.hpp"
#include "nmtools/utility/fwd.hpp"
#include "nmtools/utils/to_string/to_string.hpp"

namespace nmtools::view
{
    template <typename src_shape_t
        , typename window_shape_t
        , typename axis_t>
    struct sliding_window_t
        : base_indexer_t<sliding_window_t<src_shape_t,window_shape_t,axis_t>>
    {
        using src_shape_type    = meta::fwd_attribute_t<src_shape_t>;
        using window_shape_type = meta::fwd_attribute_t<window_shape_t>;
        using axis_type         = meta::fwd_attribute_t<axis_t>;
        using dst_shape_type = meta::resolve_optype_t<index::shape_sliding_window_t
            , src_shape_type, window_shape_type, axis_type>;
        using dst_size_type = meta::resolve_optype_t<index::product_t,dst_shape_type>;
        using src_size_type = meta::resolve_optype_t<index::product_t,src_shape_type>;

        static constexpr auto n_inputs  = 1;
        static constexpr auto n_outputs = 1;

        const src_shape_type src_shape;
        const window_shape_type window_shape;
        const axis_type axis;
        const dst_shape_type dst_shape;

        constexpr sliding_window_t(const src_shape_t& src_shape
            , const window_shape_t& window_shape
            , const axis_t& axis
        )
            : src_shape(fwd_attribute(src_shape))
            , window_shape(fwd_attribute(window_shape))
            , axis(fwd_attribute(axis))
            , dst_shape(index::shape_sliding_window(
                src_shape,window_shape,axis))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            auto src_indices = index::sliding_window(indices
                , unwrap(dst_shape), src_shape, window_shape, axis);
            return src_indices;
        }

        template <typename...args_t>
        constexpr auto operator==(sliding_window_t<args_t...> other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(dst_shape,other.dst_shape)
                && utils::isequal(window_shape,other.window_shape)
                && utils::isequal(axis,other.axis)
            ;
        }
    }; // sliding_window_t

    template <typename array_t, typename window_shape_t, typename axis_t=none_t>
    constexpr auto make_sliding_window(const array_t& array
        , const window_shape_t& window_shape, const axis_t& axis=axis_t{})
    {
        auto src_shape = shape<true>(array);
        auto indexer   = sliding_window_t{src_shape,window_shape,axis};
        return indexing(array,indexer);
    } // make_sliding_window

    template <typename array_t, typename window_shape_t, typename axis_t=none_t>
    constexpr auto sliding_window(const array_t& array
        , const window_shape_t& window_shape, const axis_t& axis=axis_t{})
    {
        auto f = [](const auto&...args){
            return make_sliding_window(args...);
        };
        return lift_indexing(f,array,window_shape,axis);
    } // sliding_window
} // namespace nmtools::view

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        view::sliding_window_t<args_t...>, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(const view::sliding_window_t<args_t...>& kwargs) const noexcept
        {
            nmtools_string str;
            str += "sliding_window{";
            str += ".src_shape=";
            str += to_string(kwargs.src_shape,Compact);
            str += ",.window_shape=";
            str += to_string(kwargs.window_shape,Compact);
            str += ",.axis=";
            str += to_string(kwargs.axis,Compact);
            str += "}";
            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING


#endif // NMTOOLS_ARRAY_VIEW_SLIDING_WINDOW_HPP