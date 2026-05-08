#ifndef NMTOOLS_ARRAY_VIEW_BROADCAST_TO_HPP
#define NMTOOLS_ARRAY_VIEW_BROADCAST_TO_HPP

#include "nmtools/core/decorator.hpp"

#include "nmtools/index/broadcast_to.hpp"
#include "nmtools/index/compute_strides.hpp"

#include "nmtools/utility/unwrap.hpp"
#include "nmtools/utility/isequal/isequal.hpp"
#include "nmtools/core/indexing.hpp"

namespace nmtools::index
{
    struct broadcast_to_strides_t {};

    template <typename src_shape_t, typename dst_shape_t>
    constexpr auto broadcast_to_strides(
        [[maybe_unused]] const src_shape_t& src_shape
        , [[maybe_unused]] const dst_shape_t& dst_shape)
    {
        using result_t = resolve_optype_t<broadcast_to_strides_t,src_shape_t,dst_shape_t>;

        auto result = result_t {};

        if constexpr (!is_fail_v<result_t>
            && !is_constant_index_array_v<result_t>
        ) {
            auto src_dim = len(src_shape);
            auto dim = len(dst_shape);

            if constexpr (is_resizable_v<result_t>) {
                result.resize(dim);
            }

            const auto src_strides = compute_strides(src_shape);

            constexpr auto DIM = len_v<result_t>;

            if constexpr (DIM > 0) {
                template_for<DIM>([&](auto i){
                    constexpr auto I = decltype(i)::value;
                    constexpr auto idx = ct_v<-(nm_index_t)(I+1)>;
                    using result_i_t = decltype(at(result,idx));
                    if constexpr (!is_constant_index_v<result_i_t>) {
                        auto value = 0;
                        if (i<(nm_size_t)src_dim) {
                            auto src_stride_i = at(src_strides,(nm_index_t)idx);
                            auto src_shape_i  = at(src_shape,(nm_index_t)idx);
                            if (has_value(src_stride_i) && has_value(src_shape_i)) {
                                value = (src_shape_i == 1 ? (nm_size_t)0 : (nm_size_t)src_stride_i);
                            } else if (has_value(src_stride_i)) {
                                value = src_stride_i;
                            }
                        }
                        at(result,idx) = value;
                    }
                });
            } else {
                for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
                    auto value = 0;
                    auto idx = -(nm_index_t)(i+1);
                    if (i<(nm_size_t)src_dim) {
                        auto src_stride_i = at(src_strides,idx);
                        auto src_shape_i  = at(src_shape,idx);
                        if (has_value(src_stride_i) && has_value(src_shape_i)) {
                            value = (src_shape_i == 1 ? 0 : src_stride_i);
                        } else if (has_value(src_stride_i)) {
                            value = src_stride_i;
                        }
                    }
                    at(result,idx) = value;
                }
            }
        }

        return result;
    } // broadcast_to_strides

    template <typename indices_t, typename src_shape_t, typename dst_strides_t, typename src_strides_t>
    constexpr auto broadcast_to_v2(const indices_t& indices, const src_shape_t& src_shape, const dst_strides_t& dst_strides, const src_strides_t& src_strides)
    {
        // TODO: further optimize by trying to compute partially at compile time for mixed shape
        auto offset = index::compute_offset(indices,dst_strides);
        auto src_indices = index::compute_indices(offset,src_shape,src_strides);
        return src_indices;
    } // broadcast_to_v2
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template<typename...>
        struct BROADCAST_TO_STRIDES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename src_shape_t, typename dst_shape_t>
    struct resolve_optype<
        void, index::broadcast_to_strides_t, src_shape_t, dst_shape_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<src_shape_t>
                || !is_index_array_v<dst_shape_t>
            ) {
                using type = error::BROADCAST_TO_STRIDES_UNSUPPORTED<src_shape_t,dst_shape_t>;
                return as_value_v<type>;
            } else if constexpr (
                (is_constant_index_array_v<src_shape_t> || is_mixed_index_array_v<src_shape_t>)
                && (is_constant_index_array_v<dst_shape_t> || is_mixed_index_array_v<dst_shape_t>)
            ) {
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto dst_shape = to_value_v<dst_shape_t>;
                constexpr auto result = index::broadcast_to_strides(src_shape,dst_shape);
                using nmtools::at, nmtools::len, nmtools::has_value;
                // TODO: check if all entries is null, if so return normal index array
                return template_reduce<len(result)>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    constexpr auto v = at(result,I);
                    using init_t = type_t<decltype(init)>;
                    if constexpr (has_value(v)) {
                        using type = append_type_t<init_t,ct<(nm_size_t)v>>;
                        return as_value_v<type>;
                    } else {
                        using type = append_type_t<init_t,nm_size_t>;
                        return as_value_v<type>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto DIM = len_v<dst_shape_t>;
                [[maybe_unused]]
                constexpr auto MAX_DIM = max_len_v<dst_shape_t>;
                using element_t = get_index_element_type_t<dst_shape_t>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<element_t,DIM>;
                    return as_value_v<type>;
                } else if constexpr (MAX_DIM > 0) {
                    using type = nmtools_static_vector<element_t,MAX_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<element_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

/*************************************************************************** */

namespace nmtools::view
{
    template <typename src_shape_t, typename dst_shape_t, typename bsize_t>
    struct broadcast_to_v2_t
        : base_indexer_t<broadcast_to_v2_t<src_shape_t,dst_shape_t,bsize_t>>
    {
        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;
        using dst_shape_type = meta::fwd_attribute_t<dst_shape_t>;

        static constexpr auto dst_size_vtype = [](){
            if constexpr (is_none_v<bsize_t> && is_index_array_v<dst_shape_type>) {
                using type = decltype(index::product(declval<dst_shape_type>()));
                return as_value_v<type>;
            } else {
                using type = bsize_t;
                return as_value_v<type>;
            }
        }();
        using dst_size_type = type_t<decltype(dst_size_vtype)>;
        using dst_strides_type = resolve_optype_t<index::broadcast_to_strides_t,src_shape_type,dst_shape_type>;
        using src_strides_type = resolve_optype_t<index::compute_strides_t,src_shape_type>;

        static constexpr auto n_inputs  = 1;
        static constexpr auto n_outputs = 1;

        const src_shape_type src_shape;
        const dst_shape_type dst_shape;
        const dst_size_type  dst_size;
        const dst_strides_type dst_strides;
        const src_strides_type src_strides;

        constexpr broadcast_to_v2_t(const src_shape_t& src_shape
            , const dst_shape_t& dst_shape
            , const bsize_t& bsize
        )
            : src_shape(fwd_attribute(src_shape))
            , dst_shape(fwd_attribute(dst_shape))
            , dst_size([&](){
                if constexpr (is_none_v<bsize_t> && is_index_array_v<dst_shape_type>) {
                    return index::product(dst_shape);
                } else {
                    return fwd_attribute(bsize);
                }
            }())
            , dst_strides(index::broadcast_to_strides(src_shape,dst_shape))
            , src_strides(index::compute_strides(src_shape))
        {}

        template <typename indices_t>
        constexpr auto indices([[maybe_unused]] const indices_t& indices) const
        {
            if constexpr (is_none_v<src_shape_type>) {
                return None;
            } else {
                return index::broadcast_to_v2(indices,src_shape,dst_strides,src_strides);
            }
        }

        template <typename...args_t>
        constexpr auto operator==(broadcast_to_v2_t<args_t...> other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(dst_shape,other.dst_shape)
            ;
        }
    };

    template <typename src_shape_t, typename dst_shape_t, typename origin_axes_t, typename bsize_t>
    struct broadcast_to_t
        : base_indexer_t<broadcast_to_t<src_shape_t,dst_shape_t,origin_axes_t,bsize_t>>
    {
        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;
        using dst_shape_type = meta::fwd_attribute_t<dst_shape_t>;

        static constexpr auto dst_size_vtype = [](){
            if constexpr (is_none_v<bsize_t> && is_index_array_v<dst_shape_type>) {
                using type = decltype(index::product(declval<dst_shape_type>()));
                return as_value_v<type>;
            } else {
                using type = bsize_t;
                return as_value_v<type>;
            }
        }();
        using dst_size_type = type_t<decltype(dst_size_vtype)>;

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
                if constexpr (is_none_v<bsize_t> && is_index_array_v<dst_shape_type>) {
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
        if constexpr (is_maybe_v<dst_shape_t>) {
            using result_t = decltype(broadcaster(src_shape,unwrap(dst_shape),origin_axes,bsize));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            if (static_cast<bool>(dst_shape)) {
                if constexpr (is_maybe_v<result_t>) {
                    return broadcaster(src_shape,unwrap(dst_shape),origin_axes,bsize);
                } else {
                    return return_t{broadcaster(src_shape,unwrap(dst_shape),origin_axes,bsize)};
                }
            } else {
                return return_t{Nothing};
            }
        } else if constexpr (is_maybe_v<origin_axes_t>) {
            using result_t = decltype(broadcaster(src_shape,dst_shape,unwrap(origin_axes),bsize));
            using return_t = nmtools_maybe<result_t>;
            return (origin_axes ?
                return_t{broadcaster(src_shape,dst_shape,unwrap(origin_axes),bsize)}
                : return_t{Nothing}
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

    template <typename src_shape_t, typename dst_shape_t, typename bsize_t>
    constexpr auto broadcaster_v2(const src_shape_t& src_shape, const dst_shape_t& dst_shape, bsize_t bsize)
    {
        if constexpr (is_maybe_v<src_shape_t> || is_maybe_v<dst_shape_t> || is_maybe_v<bsize_t>) {
            using result_t = decltype(broadcaster_v2(unwrap(src_shape),unwrap(dst_shape),unwrap(bsize)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(src_shape) && has_value(dst_shape) && has_value(bsize)
                ? return_t{broadcaster_v2(unwrap(src_shape),unwrap(dst_shape),unwrap(bsize))}
                : return_t{Nothing}
            );
        } else {
            return broadcast_to_v2_t{src_shape,dst_shape,bsize};
        }
    }

    template <typename array_t, typename dst_shape_t, typename bsize_t=none_t>
    constexpr auto broadcast_to(const array_t& array, const dst_shape_t& dst_shape, bsize_t bsize=bsize_t{})
    {
        auto f = [](const auto& array, const auto& dst_shape, const auto bsize){
            auto src_shape = shape<true>(array);
            auto bcast_result   = index::shape_broadcast_to(src_shape,dst_shape);
            auto m_shape_origin = index::origin_axes(bcast_result);
            if constexpr (is_maybe_v<decltype(m_shape_origin)>) {
                using shape_origin_t = meta::get_maybe_type_t<decltype(m_shape_origin)>;
                using origin_t  = decltype(nmtools::get<1>(declval<shape_origin_t>()));
                using indexer_t = decltype(broadcaster(src_shape,dst_shape,declval<origin_t>(),bsize));
                using result_t  = decltype(indexing(array,declval<indexer_t>()));
                using return_t  = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
                if (static_cast<bool>(m_shape_origin)) {
                    auto origin = nmtools::get<1>(*m_shape_origin);
                    auto indexer = broadcaster(src_shape,dst_shape,origin,bsize);
                    return return_t{indexing(array,indexer)};
                } else {
                    return return_t{Nothing};
                }
            } else {
                auto origin = nmtools::get<1>(m_shape_origin);
                auto indexer = broadcaster(src_shape,dst_shape,origin,bsize);
                return indexing(array,indexer);
            }
        };
        return lift_indexing(f,array,dst_shape,bsize);
    } // broadcast_to

    template <typename array_t, typename dst_shape_t, typename bsize_t=none_t>
    constexpr auto broadcast_to_v2(const array_t& array, const dst_shape_t& dst_shape, bsize_t bsize=bsize_t{})
    {
        auto f = [](const auto& array, const auto& dst_shape, const auto bsize){
            const auto src_shape = shape<true>(array);
            auto indexer = broadcaster_v2(src_shape,dst_shape,bsize);
            return indexing(array,indexer);
        };
        return lift_indexing(f,array,dst_shape,bsize);
    }
} // namespace nmtools::view

namespace nmtools
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

    template <typename...args_t, auto max_dim>
    struct as_static_t<
        view::broadcast_to_v2_t<args_t...>, max_dim
    > {
        using attribute_type = view::broadcast_to_v2_t<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto src_shape = as_static<max_dim>(attribute.src_shape);
            auto dst_shape = as_static<max_dim>(attribute.dst_shape);
            auto bsize  = as_static<max_dim>(attribute.dst_size);
            return view::broadcaster_v2(src_shape,dst_shape,bsize);
        }
    };
} // namespace nmtools

namespace nmtools::meta
{
    template <typename array_t, typename...broadcast_args_t>
    struct is_broadcast_view<
        view::decorator_t<view::indexing_t, array_t, view::broadcast_to_t<broadcast_args_t...>>
    > : true_type {};

    template <typename array_t, typename...broadcast_args_t>
    struct is_broadcast_view<
        view::decorator_t<view::indexing_t, array_t, view::broadcast_to_v2_t<broadcast_args_t...>>
    > : true_type {};
}

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

    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        view::broadcast_to_v2_t<args_t...>, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(const view::broadcast_to_v2_t<args_t...>& kwargs) const noexcept
        {
            nmtools_string str;
            str += "broadcast_to";
            str += "{";
            str += ".src_shape=";   str += to_string(kwargs.src_shape,Compact);
            str += ",.dst_shape=";  str += to_string(kwargs.dst_shape,Compact);
            str += ",.bsize=";      str += to_string(kwargs.dst_size,Compact);
            str += "}";
            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_BROADCAST_TO_HPP