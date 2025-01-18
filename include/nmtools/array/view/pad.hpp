#ifndef NMTOOLS_ARRAY_VIEW_PAD_HPP
#define NMTOOLS_ARRAY_VIEW_PAD_HPP

#include "nmtools/array/core/decorator.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/array/index/pad.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/core/indexing.hpp"
#include "nmtools/utility/isequal/isequal.hpp"
#include "nmtools/utility/isclose/isclose.hpp"
#include "nmtools/utility/to_string/to_string.hpp"

namespace nmtools::view
{
    enum class PADDING_MODE
    {
        CONSTANT,
    };

    template <typename src_shape_t, typename pad_width_t, typename src_size_t>
    struct pad_t
        : base_indexer_t<pad_t<src_shape_t,pad_width_t,src_size_t>>
    {
        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;
        using pad_width_type = meta::fwd_attribute_t<pad_width_t>;
        using dst_shape_type = meta::resolve_optype_t<index::shape_pad_t,src_shape_type,pad_width_type>;

        using src_size_type = src_size_t;
        using dst_size_type = decltype(unwrap(index::product(meta::declval<dst_shape_type>())));

        static constexpr auto n_inputs  = 2;
        static constexpr auto n_outputs = 1;

        const src_shape_type src_shape;
        const pad_width_type pad_width;
        const dst_shape_type dst_shape;
        const src_size_type  src_size;
        const dst_size_type  dst_size;

        constexpr pad_t(const src_shape_t& src_shape
            , const pad_width_t& pad_width
            , src_size_t src_size
        )
            : src_shape(fwd_attribute(src_shape))
            , pad_width(fwd_attribute(pad_width))
            , dst_shape(unwrap(index::shape_pad(src_shape,pad_width)))
            , src_size(src_size)
            , dst_size(unwrap(index::product(dst_shape)))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            auto src_indices = index::pad(indices,src_shape,dst_shape,pad_width);
            using src_indices_t = meta::get_maybe_type_t<decltype(src_indices)>;
            // TODO: change index::pad to return either<indices,None>
            using result_t = nmtools_either<src_indices_t,none_t>;
            if (src_indices) {
                return result_t{unwrap(src_indices)};
            } else {
                return result_t{None};
            }
        }

        template <typename...args_t>
        constexpr auto operator==(pad_t<args_t...> other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(pad_width,other.pad_width)
            ;
        }
    };

    template <typename src_shape_t, typename pad_width_t, typename src_size_t>
    constexpr auto padder(const src_shape_t& src_shape, const pad_width_t& pad_width, src_size_t src_size)
    {
        if constexpr (meta::is_maybe_v<src_shape_t>) {
            using result_t = decltype(padder(unwrap(src_shape),pad_width,src_size));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (src_shape
                ? return_t{padder(unwrap(src_shape),pad_width,src_size)}
                : return_t{meta::Nothing}
            );
        } else if constexpr (meta::is_maybe_v<pad_width_t>) {
            using result_t = decltype(padder(src_shape,unwrap(pad_width),src_size));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (pad_width
                ? return_t{padder(src_shape,unwrap(pad_width),src_size)}
                : return_t{meta::Nothing}
            );
        } else {
            [[maybe_unused]]
            auto dst_shape = index::shape_pad(src_shape,pad_width);
            if constexpr (meta::is_fail_v<decltype(dst_shape)>) {
                // let the caller handle type error
                return dst_shape;
            } else if constexpr (meta::is_maybe_v<decltype(dst_shape)>) {
                using result_t = decltype(pad_t{src_shape,pad_width,unwrap(src_size)});
                using return_t = nmtools_maybe<result_t>;
                return (dst_shape
                    ? return_t{pad_t{src_shape,pad_width,unwrap(src_size)}}
                    : return_t{meta::Nothing}
                );
            } else {
                return pad_t{src_shape,pad_width,unwrap(src_size)};
            }
        }
    } // padder

    template <typename array_t, typename pad_width_t, typename value_t=float>
    constexpr auto pad(const array_t& array, const pad_width_t& pad_width, value_t value=static_cast<value_t>(0))
    {
        auto f = [](const auto& array, const auto& pad_width, value_t value){
            using element_t = meta::get_element_type_t<meta::remove_cvref_t<decltype(array)>>;
            auto src_shape  = shape<true>(array);
            auto src_size   = size<true>(array);
            auto indexer    = padder(src_shape,pad_width,src_size);
            auto operands   = pack_operands(array,static_cast<element_t>(value));
            return indexing(operands,indexer);
        };
        return lift_indexing(f,array,pad_width,value);
    }
} // namespace nmtools::view

namespace nmtools::array
{
    template <typename...args_t, auto max_dim>
    struct as_static_t<
        view::pad_t<args_t...>, max_dim
    > {
        using attribute_type = view::pad_t<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto src_shape = as_static<max_dim>(attribute.src_shape);
            auto pad_width = as_static<max_dim>(attribute.pad_width);
            auto src_size  = as_static<max_dim>(attribute.src_size);
            return view::padder(src_shape,pad_width,src_size);
        }
    };
} // namespace nmtools::array

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        view::pad_t<args_t...>, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(const view::pad_t<args_t...>& kwargs) const noexcept
        {
            nmtools_string str;
            str += "pad";
            str += "{";
            str += ".src_shape=";
            str += to_string(kwargs.src_shape,Compact);
            str += ".pad_width=";
            str += to_string(kwargs.pad_width,Compact);
            str += ".src_size=";
            str += to_string(kwargs.src_size,Compact);
            str += "}";
            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_PAD_HPP