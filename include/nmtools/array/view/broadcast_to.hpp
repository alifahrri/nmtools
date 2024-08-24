#ifndef NMTOOLS_ARRAY_VIEW_BROADCAST_TO_HPP
#define NMTOOLS_ARRAY_VIEW_BROADCAST_TO_HPP

#include "nmtools/array/view/decorator.hpp"

#include "nmtools/array/index/broadcast_to.hpp"

#include "nmtools/utility/unwrap.hpp"
#include "nmtools/array/view/indexing.hpp"

namespace nmtools::view
{
    template <typename src_shape_t, typename dst_shape_t, typename origin_axes_t, typename bsize_t>
    struct broadcast_to_t
        : base_indexer_t<broadcast_to_t<src_shape_t,dst_shape_t,origin_axes_t,bsize_t>>
    {
        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;

        using dst_shape_type = meta::fwd_attribute_t<dst_shape_t>;

        static constexpr auto dst_size_vtype = [](){
            if constexpr (is_none_v<bsize_t> && meta::is_index_array_v<dst_shape_type>) {
                using type = decltype(index::product(meta::declval<dst_shape_type>()));
                return meta::as_value_v<type>;
            } else {
                using type = bsize_t;
                return meta::as_value_v<type>;
            }
        }();
        using dst_size_type = meta::type_t<decltype(dst_size_vtype)>;

        using origin_axes_type = meta::fwd_attribute_t<origin_axes_t>;

        static constexpr auto n_inputs  = 1;
        static constexpr auto n_outputs = 1;

        const src_shape_type   src_shape;
        const dst_shape_type   dst_shape;
        const origin_axes_type origin_axes;
        const dst_size_type    dst_size;

        constexpr broadcast_to_t(const src_shape_t& src_shape_
            , const dst_shape_t& dst_shape_
            , const origin_axes_t& origin_axes_
            , const bsize_t& bsize_
        )
            : src_shape(fwd_attribute(src_shape_))
            , dst_shape(fwd_attribute(dst_shape_))
            , origin_axes(fwd_attribute(origin_axes_))
            , dst_size([&](){
                if constexpr (is_none_v<bsize_t> && meta::is_index_array_v<dst_shape_type>) {
                    return index::product(dst_shape);
                } else {
                    return fwd_attribute(bsize_);
                }
            }())
        {}

        template <typename indices_t>
        constexpr auto indices([[maybe_unused]] const indices_t& indices) const
        {
            if constexpr (is_none_v<src_shape_type>) {
                return None;
            } else {
                auto src_indices = index::broadcast_to(indices,src_shape,dst_shape,origin_axes);
                return unwrap(src_indices);
            }
        }

        template <typename...args_t>
        constexpr auto operator==(broadcast_to_t<args_t...> other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(dst_shape,other.dst_shape)
                && utils::isequal(origin_axes,other.origin_axes)
            ;
        }
    }; // broadcast_to_t

    template <typename src_shape_t, typename dst_shape_t, typename origin_axes_t, typename bsize_t>
    constexpr auto broadcaster(const src_shape_t& src_shape, const dst_shape_t& dst_shape, const origin_axes_t& origin_axes, bsize_t bsize)
    {
        // NOTE: the size may be inferred from broadcast_arrays
        if constexpr (meta::is_maybe_v<dst_shape_t>) {
            using result_t = decltype(broadcaster(src_shape,unwrap(dst_shape),origin_axes,bsize));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            if (static_cast<bool>(dst_shape)) {
                if constexpr (meta::is_maybe_v<result_t>) {
                    return broadcaster(src_shape,unwrap(dst_shape),origin_axes,bsize);
                } else {
                    return return_t{broadcaster(src_shape,unwrap(dst_shape),origin_axes,bsize)};
                }
            } else {
                return return_t{meta::Nothing};
            }
        } else if constexpr (meta::is_maybe_v<origin_axes_t>) {
            using result_t = decltype(broadcaster(src_shape,dst_shape,unwrap(origin_axes),bsize));
            using return_t = nmtools_maybe<result_t>;
            return (origin_axes ?
                return_t{broadcaster(src_shape,dst_shape,unwrap(origin_axes),bsize)}
                : return_t{meta::Nothing}
            );
        } else {
            #if 0
            auto result = broadcast_to_t{src_shape,dst_shape,origin_axes,unwrap(bsize)};
            return result;
            #else
            return broadcast_to_t{src_shape,dst_shape,origin_axes,unwrap(bsize)};
            #endif
        }
    } // broadcaster

    template <typename array_t, typename dst_shape_t, typename bsize_t=none_t>
    constexpr auto broadcast_to(const array_t& array, const dst_shape_t& dst_shape, bsize_t bsize=bsize_t{})
    {
        auto f = [](const auto& array, const auto& dst_shape, const auto bsize){
            auto src_shape = shape<true>(array);
            auto bcast_result = index::shape_broadcast_to(src_shape,dst_shape);
            #if 0
            // when shape_origin is tuple<maybe<clipped_integer>...>
            // unusable in constexpr evaluation :|
            auto shape_origin = index::origin_axes(bcast_result);
            auto origin = nmtools::get<1>(shape_origin);
            auto indexer = broadcaster(src_shape,dst_shape,origin,bsize);
            return indexing(array,indexer);
            #else
            auto m_shape_origin = index::origin_axes(bcast_result);
            if constexpr (meta::is_maybe_v<decltype(m_shape_origin)>) {
                using shape_origin_t = meta::get_maybe_type_t<decltype(m_shape_origin)>;
                using origin_t  = decltype(nmtools::get<1>(meta::declval<shape_origin_t>()));
                using indexer_t = decltype(broadcaster(src_shape,dst_shape,meta::declval<origin_t>(),bsize));
                using result_t  = decltype(indexing(array,meta::declval<indexer_t>()));
                using return_t  = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
                if (static_cast<bool>(m_shape_origin)) {
                    auto origin = nmtools::get<1>(*m_shape_origin);
                    auto indexer = broadcaster(src_shape,dst_shape,origin,bsize);
                    return return_t{indexing(array,indexer)};
                } else {
                    return return_t{meta::Nothing};
                }
            } else {
                auto origin = nmtools::get<1>(m_shape_origin);
                auto indexer = broadcaster(src_shape,dst_shape,origin,bsize);
                return indexing(array,indexer);
            }
            #endif
        };
        return lift_indexing(f,array,dst_shape,bsize);
    } // broadcast_to
} // namespace nmtools::view

namespace nmtools::array
{
    template <typename...args_t, auto max_dim>
    struct as_static_t<
        view::broadcast_to_t<args_t...>, max_dim
    > {
        using attribute_type = view::broadcast_to_t<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto src_shape = as_static<max_dim>(attribute.src_shape);
            auto dst_shape = as_static<max_dim>(attribute.dst_shape);
            auto origin = as_static<max_dim>(attribute.origin_axes);
            auto bsize  = as_static<max_dim>(attribute.dst_size);
            return view::broadcaster(src_shape,dst_shape,origin,bsize);
        }
    };
} // namespace nmtools::array

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        view::broadcast_to_t<args_t...>, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(const view::broadcast_to_t<args_t...>& kwargs) const noexcept
        {
            nmtools_string str;
            str += "broadcast_to";
            str += "{";
            str += ".src_shape=";   str += to_string(kwargs.src_shape,Compact);
            str += ",.dst_shape=";  str += to_string(kwargs.dst_shape,Compact);
            str += ",.origin=";     str += to_string(kwargs.origin_axes,Compact);
            str += ",.bsize=";      str += to_string(kwargs.dst_size,Compact);
            str += "}";
            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_BROADCAST_TO_HPP