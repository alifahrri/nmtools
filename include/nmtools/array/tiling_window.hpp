#ifndef NMTOOLS_ARRAY_TILING_WINDOW_HPP
#define NMTOOLS_ARRAY_TILING_WINDOW_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/index/normalize_axis.hpp"

namespace nmtools::index
{
    struct shape_tiling_window_t {};

    template <typename src_shape_t
        , typename tile_shape_t
        , typename axis_t=none_t>
    constexpr auto shape_tiling_window(
        [[maybe_unused]] const src_shape_t& src_shape
        , [[maybe_unused]] const tile_shape_t& tile_shape
        , [[maybe_unused]] const axis_t& axis=axis_t{}
    ) {
        if constexpr (meta::is_maybe_v<src_shape_t>
            || meta::is_maybe_v<tile_shape_t>
            || meta::is_maybe_v<axis_t>
        ) {
            using result_t = decltype(shape_tiling_window(unwrap(src_shape),unwrap(tile_shape),unwrap(axis)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(src_shape) && has_value(tile_shape) && has_value(axis)
                ? return_t{shape_tiling_window(unwrap(src_shape),unwrap(tile_shape),unwrap(axis))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<shape_tiling_window_t,src_shape_t,tile_shape_t,axis_t>;

            auto result = result_t {};

            if constexpr (!meta::is_constant_index_array_v<result_t>
                && !meta::is_fail_v<result_t>
            ) {
                [[maybe_unused]]
                constexpr auto SRC_DIM = meta::len_v<src_shape_t>;
                [[maybe_unused]]
                constexpr auto DST_DIM = meta::len_v<result_t>;
                auto src_dim = len(src_shape);

                auto tile_dim = [&]()->nm_size_t{
                    if constexpr (meta::is_num_v<tile_shape_t> && is_none_v<axis_t>) {
                        return src_dim;
                    } else if constexpr (meta::is_num_v<tile_shape_t>) {
                        return 1;
                    } else {
                        return len(tile_shape);
                    }
                }();

                [[maybe_unused]]
                auto dst_dim = src_dim + tile_dim;

                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(dst_dim);
                }

                [[maybe_unused]]
                auto normalized_axis = [&](){
                    if constexpr (meta::is_num_v<tile_shape_t> && is_none_v<axis_t>) {
                        constexpr auto SRC_DIM = meta::len_v<src_shape_t>;
                        [[maybe_unused]]
                        constexpr auto SRC_BDIM = meta::bounded_size_v<src_shape_t>;
                        if constexpr (SRC_DIM > 0) {
                            using m_axis_t = nmtools_array<nm_size_t,SRC_DIM>;
                            auto m_axis = m_axis_t{};
                            for (nm_size_t i=0; i<len(m_axis); i++) {
                                at(m_axis,i) = i;
                            }
                            return m_axis;
                        } else if constexpr (!meta::is_fail_v<decltype(SRC_BDIM)>) {
                            using m_axis_t = nmtools_static_vector<nm_size_t,SRC_BDIM>;
                            auto m_axis = m_axis_t{};
                            m_axis.resize(src_dim);
                            for (nm_size_t i=0; i<len(m_axis); i++) {
                                at(m_axis,i) = i;
                            }
                            return m_axis;
                        } else {
                            // TODO: support small_vector
                            using m_axis_t = nmtools_list<nm_size_t>;
                            auto m_axis = m_axis_t{};
                            m_axis.resize(src_dim);
                            for (nm_size_t i=0; i<len(m_axis); i++) {
                                at(m_axis,i) = i;
                            }
                            return m_axis;
                        }
                    } else if constexpr (is_none_v<axis_t>) {
                        return axis;
                    } else {
                        // TODO: propagate error
                        return unwrap(normalize_axis(axis,src_dim));
                    }
                }();

                if constexpr (meta::is_index_v<tile_shape_t> && is_none_v<axis_t>) {
                    if constexpr (SRC_DIM > 0) {
                        // handle mixed index array
                        meta::template_for<SRC_DIM>([&](auto i){
                            auto s_i = at(src_shape,i);
                            if (has_value(s_i)) {
                                at(result,i) = s_i / tile_shape;
                            }
                        });
                    } else {
                        for (nm_size_t i=0; i<src_dim; i++) {
                            // TODO: check & propagate error
                            at(result,i) = at(src_shape,i) / tile_shape;
                        }
                    }
                    if constexpr ((SRC_DIM > 0) && (DST_DIM > 0)) {
                        meta::template_for<DST_DIM-SRC_DIM>([&](auto i){
                            auto I = meta::ct_v<SRC_DIM+decltype(i)::value>;
                            at(result,I) = tile_shape;
                        });
                    } else {
                        for (nm_size_t i=src_dim; i<dst_dim; i++) {
                            at(result,i) = tile_shape;
                        }
                    }
                } else if constexpr (meta::is_index_array_v<tile_shape_t> && meta::is_index_array_v<axis_t>) {
                    for (nm_size_t i=0; i<src_dim; i++) {
                        auto src_i = at(src_shape,i);
                        if (has_value(src_i)) {
                            at(result,i) = src_i;
                        }
                    }
                    for (nm_size_t i=0; i<len(normalized_axis); i++) {
                        // TODO: handle error
                        auto ai = at(unwrap(normalized_axis),i);
                        if (!has_value(at(result,ai))) {
                            continue;
                        }
                        at(result,ai) /= at(tile_shape,i);
                        at(result,src_dim+i) = at(tile_shape,i);
                    }
                } else if constexpr (meta::is_index_array_v<tile_shape_t>) {
                    if constexpr (SRC_DIM > 0) {
                        // handle mixed index array
                        meta::template_for<SRC_DIM>([&](auto i){
                            auto src_i = at(src_shape,i);
                            auto tile_i = at(tile_shape,i);
                            if (has_value(src_i) && has_value(tile_i)) {
                                at(result,i) = src_i / tile_i;
                            }
                        });
                    } else {
                        // assume len(tile_shape) == len(src_shape)
                        // TODO: check & propagate error
                        for (nm_size_t i=0; i<src_dim; i++) {
                            // TODO: check & propagate error
                            at(result,i) = at(src_shape,i) / at(tile_shape,i);
                        }
                    }
                    if constexpr (DST_DIM > 0) {
                        meta::template_for<DST_DIM-SRC_DIM>([&](auto i){
                            auto I = meta::ct_v<SRC_DIM+decltype(i)::value>;
                            at(result,I) = at(tile_shape,i);
                        });
                    } else {
                        for (nm_size_t i=src_dim; i<dst_dim; i++) {
                            at(result,i) = at(tile_shape,i-src_dim);
                        }
                    }
                } else /* if constexpr (meta::is_index_v<tile_shape_t> && is_none_v<axis_t>) */ {
                    for (nm_size_t i=0; i<src_dim; i++) {
                        auto src_i = at(src_shape,i);
                        if ((i == normalized_axis) && has_value(src_i)) {
                            at(result,i) = src_i / tile_shape;
                        } else if (has_value(src_i)) {
                            at(result,i) = src_i;
                        }
                    }
                    at(result,src_dim) = tile_shape;
                }
            }

            return result;
        }
    } // shape_tiling_window

    struct tiling_window_t {};

    template <typename dst_indices_t
        , typename src_shape_t
        , typename tile_shape_t
        , typename axis_t=none_t>
    constexpr auto tiling_window(
        const dst_indices_t& dst_indices
        , const src_shape_t& src_shape
        , const tile_shape_t& tile_shape
        , [[maybe_unused]] const axis_t& axis=axis_t{}
    ) {
        using result_t = meta::resolve_optype_t<tiling_window_t,dst_indices_t,src_shape_t,tile_shape_t,axis_t>;

        auto result = result_t {};

        [[maybe_unused]] auto src_dim = len(src_shape);
        [[maybe_unused]] auto dst_dim = len(dst_indices);

        if constexpr (meta::is_resizable_v<result_t>) {
            result.resize(src_dim);
        }

        if constexpr (meta::is_index_array_v<tile_shape_t> && meta::is_index_array_v<axis_t>) {
            for (nm_size_t i=0; i<src_dim; i++) {
                at(result,i) = at(dst_indices,i);
            }
            for (nm_size_t i=0; i<len(axis); i++) {
                auto ai = at(axis,i);
                auto ts = at(tile_shape,i);
                at(result,ai) *= ts;
                at(result,ai) += at(dst_indices,src_dim+i);
            }
        } else if constexpr (meta::is_index_array_v<tile_shape_t>) {
            for (nm_size_t i=0; i<src_dim; i++) {
                at(result,i) = at(dst_indices,i) * at(tile_shape,i);
            }
            for (nm_size_t i=src_dim; i<dst_dim; i++) {
                at(result,i-src_dim) += at(dst_indices,i);
            }
        } else if constexpr (meta::is_num_v<tile_shape_t> && is_none_v<axis_t>) {
            for (nm_size_t i=0; i<src_dim; i++) {
                at(result,i) = at(dst_indices,i) * tile_shape;
            }
            for (nm_size_t i=src_dim; i<dst_dim; i++) {
                at(result,i-src_dim) += at(dst_indices,i);
            }
        } else if constexpr (meta::is_num_v<tile_shape_t> && meta::is_num_v<axis_t>) {
            for (nm_size_t i=0; i<src_dim; i++) {
                // assume normalized already
                if (i == (nm_size_t)axis) {
                    at(result,i) = at(dst_indices,i) * tile_shape;
                } else {
                    at(result,i) = at(dst_indices,i);
                }
            }
            at(result,axis) += at(dst_indices,src_dim);
        }

        return result;
    }
} // nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template<typename...>
        struct SHAPE_TILING_WINDOW_UNSUPPORTED : detail::fail_t {};

        template<typename...>
        struct TILING_WINDOW_UNSUPPORTED : detail::fail_t {};
    }

    template <typename src_shape_t
        , typename tile_shape_t
        , typename axis_t>
    struct resolve_optype<void,index::shape_tiling_window_t,src_shape_t,tile_shape_t,axis_t>
    {
        static constexpr auto vtype = [](){
            if constexpr (
                   !is_index_array_v<src_shape_t>
                || !(
                    (is_index_v<tile_shape_t> && is_none_v<axis_t>)
                    || (is_index_v<tile_shape_t> && is_index_v<axis_t>)
                    || (is_index_array_v<tile_shape_t> && (is_none_v<axis_t> || is_index_array_v<axis_t>))
                )
            ) {
                using type = error::SHAPE_TILING_WINDOW_UNSUPPORTED<src_shape_t,tile_shape_t,axis_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<src_shape_t>
                && (
                    (is_constant_index_v<tile_shape_t> && is_none_v<axis_t>)
                    || (is_constant_index_v<tile_shape_t> && is_constant_index_v<axis_t>)
                    || (is_constant_index_array_v<tile_shape_t> && is_constant_index_array_v<axis_t>)
                )
            ) {
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto tile_shape = to_value_v<tile_shape_t>;
                constexpr auto axis = to_value_v<axis_t>;
                constexpr auto result = index::shape_tiling_window(src_shape,tile_shape,axis);
                using nmtools::at, nmtools::len;
                // TODO: handle maybe result
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_type = type_t<decltype(init)>;
                    using res_type  = append_type_t<init_type,ct<at(result,I)>>;
                    return as_value_v<res_type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto SRC_DIM = len_v<src_shape_t>;
                [[maybe_unused]]
                constexpr auto SRC_BDIM = bounded_size_v<src_shape_t>;
                [[maybe_unused]]
                constexpr auto TILE_DIM = len_v<tile_shape_t>;
                [[maybe_unused]]
                constexpr auto TILE_BDIM = bounded_size_v<tile_shape_t>;
                using index_t = conditional_t<is_nullable_index_array_v<src_shape_t>,nullable_num<nm_size_t>,nm_size_t>;
                if constexpr ((SRC_DIM > 0) && is_none_v<axis_t> 
                    && (is_constant_index_v<tile_shape_t> || is_constant_index_array_v<tile_shape_t>)
                ) {
                    // results in mixed index
                    auto vtype = meta::template_reduce<SRC_DIM>([&](auto init, auto){
                        using init_t = type_t<decltype(init)>;
                        using type = append_type_t<init_t,nm_index_t>;
                        return as_value_v<type>;
                    }, as_value_v<nmtools_tuple<>>);
                    if constexpr (is_constant_index_v<tile_shape_t>) {
                        using type = append_type_t<type_t<decltype(vtype)>,tile_shape_t>;
                        return as_value_v<type>;
                    } else {
                        using type = concat_type_t<type_t<decltype(vtype)>,tile_shape_t>;
                        return as_value_v<type>;
                    }
                } else if constexpr ((SRC_DIM > 0) && (TILE_DIM > 0)) {
                    constexpr auto DST_DIM = SRC_DIM + TILE_DIM;
                    using type = nmtools_array<index_t,DST_DIM>;
                    return as_value_v<type>;
                } else if constexpr ((SRC_DIM > 0) && (is_index_v<tile_shape_t> && is_none_v<axis_t>)) {
                    constexpr auto DST_DIM = SRC_DIM * 2;
                    using type = nmtools_array<index_t,DST_DIM>;
                    return as_value_v<type>;
                } else if constexpr ((SRC_DIM > 0) && (is_index_v<tile_shape_t> && is_index_v<axis_t>)) {
                    constexpr auto DST_DIM = SRC_DIM + 1;
                    using type = nmtools_array<index_t,DST_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(SRC_BDIM)> && !is_fail_v<decltype(TILE_BDIM)>) {
                    constexpr auto DST_BDIM = SRC_BDIM + TILE_BDIM;
                    using type = nmtools_static_vector<index_t,DST_BDIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(SRC_BDIM)> && (is_index_v<tile_shape_t> && is_none_v<axis_t>)) {
                    constexpr auto DST_BDIM = SRC_BDIM * 2;
                    using type = nmtools_static_vector<index_t,DST_BDIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(SRC_BDIM)> && (is_index_v<tile_shape_t> && is_index_v<axis_t>)) {
                    constexpr auto DST_BDIM = SRC_BDIM + 1;
                    using type = nmtools_static_vector<index_t,DST_BDIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small_vector
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename dst_indices_t
        , typename src_shape_t
        , typename tile_shape_t
        , typename axis_t>
    struct resolve_optype<
        void, index::tiling_window_t
        , dst_indices_t
        , src_shape_t
        , tile_shape_t
        , axis_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (
                !is_index_array_v<src_shape_t>
                || !(
                    (is_index_v<tile_shape_t> && is_none_v<axis_t>)
                    || (is_index_v<tile_shape_t> && is_index_v<axis_t>)
                    || (is_index_array_v<tile_shape_t> && (is_none_v<axis_t> || is_index_array_v<axis_t>))
                )
                || !is_index_array_v<dst_indices_t>
            ) {
                using type = error::TILING_WINDOW_UNSUPPORTED<src_shape_t,dst_indices_t,tile_shape_t,axis_t>;
                return as_value_v<type>;
            } else {
                // TODO: support compile-time index computation
                constexpr auto SRC_DIM = len_v<src_shape_t>;
                [[maybe_unused]]
                constexpr auto SRC_BDIM = bounded_size_v<src_shape_t>;
                if constexpr (SRC_DIM > 0) {
                    using type = nmtools_array<nm_size_t,SRC_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(SRC_BDIM)>) {
                    using type = nmtools_static_vector<nm_size_t,SRC_BDIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // nmtools::meta

/* ============================================================================== */

#include "nmtools/core/indexing.hpp"
#include "nmtools/core/decorator.hpp"
#include "nmtools/utility/unwrap.hpp"
#include "nmtools/utility/fwd.hpp"
#include "nmtools/utility/to_string/to_string.hpp"

namespace nmtools::view
{
    template <typename src_shape_t
        , typename tile_shape_t
        , typename axis_t
        , typename dst_shape_t>
    struct tiling_window_t
        : base_indexer_t<tiling_window_t<src_shape_t,tile_shape_t,axis_t,dst_shape_t>>
    {
        using src_shape_type  = meta::fwd_attribute_t<src_shape_t>;
        using tile_shape_type = meta::fwd_attribute_t<tile_shape_t>;
        using axis_type = meta::fwd_attribute_t<axis_t>;
        // pass dst_shape from indexer creation so we don't have to recompute
        using dst_shape_type = meta::fwd_attribute_t<dst_shape_t>;
        
        static constexpr auto n_inputs  = 1;
        static constexpr auto n_outputs = 1;

        template <typename string_t=nmtools_static_string>
        static constexpr auto name() noexcept
        {
            return string_t("tiling_window");
        }

        const src_shape_type  src_shape;
        const tile_shape_type tile_shape;
        const axis_type       axis;
        const dst_shape_type  dst_shape;

        constexpr tiling_window_t(const src_shape_t& src_shape
            , const tile_shape_t& tile_shape
            , const axis_t& axis
            , const dst_shape_t& dst_shape
        )
            : src_shape(fwd_attribute(src_shape))
            , tile_shape(fwd_attribute(tile_shape))
            , axis(fwd_attribute(axis))
            , dst_shape(fwd_attribute(dst_shape))
        {}

        template <typename string_t=nmtools_static_string>
        constexpr auto to_string() const noexcept
        {
            string_t str;
            str += "tiling_window";
            str += "{";
            str += ".src_shape=";
            str += string_t::to_string(src_shape);
            str += ".window_shape=";
            str += string_t::to_string(tile_shape);
            str += ".axis=";
            str += string_t::to_string(axis);
            str += "}";
            return str;
        }

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            auto src_indices = index::tiling_window(indices
                , src_shape, tile_shape, axis
            );
            return src_indices;
        }

        template <typename...args_t>
        constexpr auto operator==(const tiling_window_t<args_t...>& other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(tile_shape,other.src_shape)
                && utils::isequal(axis,other.axis)
            ;
        }
    };

    template <typename src_shape_t
        , typename tile_shape_t
        , typename axis_t=none_t>
    constexpr auto tiling_window_indexer(const src_shape_t& src_shape
        , const tile_shape_t& tile_shape
        , const axis_t& axis)
    {
        if constexpr (meta::is_maybe_v<src_shape_t>
            || meta::is_maybe_v<tile_shape_t>
            || meta::is_maybe_v<axis_t>
        ) {
            using result_t = decltype(tiling_window_indexer(unwrap(src_shape),unwrap(tile_shape),unwrap(axis)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(src_shape) && has_value(tile_shape) && has_value(axis)
                ? return_t{tiling_window_indexer(unwrap(src_shape),unwrap(tile_shape),unwrap(axis))}
                : return_t{meta::Nothing}
            );
        } else {
            auto dst_shape = index::shape_tiling_window(src_shape,tile_shape,axis);
            using dst_shape_t = decltype(dst_shape);
            if constexpr (meta::is_maybe_v<dst_shape_t>) {
                using result_t = tiling_window_t<src_shape_t,tile_shape_t,axis_t,meta::get_maybe_type_t<dst_shape_t>>;
                using return_t = nmtools_maybe<result_t>;
                return (dst_shape
                    ? return_t{src_shape,tile_shape,axis,unwrap(dst_shape)}
                    : return_t{meta::Nothing}
                );
            } else {
                using result_t = tiling_window_t<src_shape_t,tile_shape_t,axis_t,dst_shape_t>;
                return result_t{src_shape,tile_shape,axis,dst_shape};
            }
        }
    } // tiling_window_indexer

    template <typename array_t
        , typename tile_shape_t
        , typename axis_t=none_t>
    constexpr auto tiling_window(const array_t& array
        , const tile_shape_t& tile_shape
        , const axis_t& axis=axis_t{})
    {
        auto f = [](const auto& array, const auto& tile_shape, const auto& axis){
            auto src_shape = shape<true>(array);
            auto indexer = tiling_window_indexer(src_shape,tile_shape,axis);
            return indexing(array,indexer);
        };
        return lift_indexing(f,array,tile_shape,axis);
    } // tiling_window
}

namespace nmtools
{
    template <typename...args_t, auto max_dim>
    struct as_static_t<
        view::tiling_window_t<args_t...>, max_dim
    > {
    
        using attribute_type = view::tiling_window_t<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto src_shape  = as_static<max_dim>(attribute.src_shape);
            // NOTE: as_static keep num as num, not make it clipped
            auto tile_shape = as_static<max_dim>(attribute.tile_shape);
            auto axis = as_static<max_dim>(attribute.axis);
            return view::tiling_window_indexer(src_shape,tile_shape,axis);
        }
    };
} // nmtools

namespace nmtools::meta
{
    template <typename src_shape_t
        , typename tile_shape_t
        , typename axis_t
        , typename dst_shape_t>
    struct to_value<
        view::tiling_window_t<src_shape_t,tile_shape_t,axis_t,dst_shape_t>
    > {
        static constexpr auto value = [](){
            [[maybe_unused]] constexpr auto SRC_DIM  = len_v<src_shape_t>;
            [[maybe_unused]] constexpr auto TILE_DIM = len_v<tile_shape_t>;
            [[maybe_unused]] constexpr auto AXIS_DIM = len_v<axis_t>;

            [[maybe_unused]] constexpr auto SRC_BDIM  = max_len_v<src_shape_t>;
            [[maybe_unused]] constexpr auto TILE_BDIM = max_len_v<tile_shape_t>;
            [[maybe_unused]] constexpr auto AXIS_BDIM = max_len_v<axis_t>;

            constexpr auto src_shape  = [&](){
                auto src_shape = to_value_v<src_shape_t>;
                if constexpr (!is_fail_v<decltype(src_shape)>) {
                    return src_shape;
                } else if constexpr (SRC_DIM > 0) {
                    using type = nmtools_array<nullable_num<nm_index_t>,SRC_DIM>;
                    return type{};
                // TODO: enable? what is the size?
                // } else if constexpr (SRC_BDIM > 0) {
                //     using type = nmtools_static_vector<nullable_num<nm_index_t>,SRC_BDIM>;
                //     return type{};
                } else {
                    // fail
                    return src_shape;
                }
            }();
            constexpr auto tile_shape = [&](){
                auto tile_shape = to_value_v<tile_shape_t>;
                if constexpr (!is_fail_v<decltype(tile_shape)>) {
                    return tile_shape;
                } else if constexpr (TILE_DIM > 0) {
                    using type = nmtools_array<nullable_num<nm_index_t>,SRC_DIM>;
                    return type{};
                } else {
                    return tile_shape;
                }
            }();
            constexpr auto axis = [&](){
                auto axis = to_value_v<axis_t>;
                if constexpr (!is_fail_v<decltype(axis)>) {
                    return axis;
                } else if constexpr (AXIS_DIM > 0) {
                    using type = nmtools_array<nullable_num<nm_index_t>,SRC_DIM>;
                    return type{};
                } else {
                    return axis;
                }
            }();

            if constexpr (!is_fail_v<decltype(src_shape)> && !is_fail_v<decltype(tile_shape)> && !is_fail_v<decltype(axis)>) {
                return view::tiling_window_indexer(src_shape,tile_shape,axis);
            } else {
                return error::TO_VALUE_UNSUPPORTED<>{};
            }
        }();
    };
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        view::tiling_window_t<args_t...>, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(const view::tiling_window_t<args_t...>& kwargs) const noexcept
        {
            nmtools_string str;
            str += kwargs.to_string().c_str();
            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#include "nmtools/core/functor.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct tiling_window
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::tiling_window(args...);
            }
        };
    }

    constexpr auto inline tiling_window = functor_t{unary_fmap_t<fun::tiling_window>()};
} // nmtools::functional

#include "nmtools/core/eval.hpp"

namespace nmtools
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename array_t, typename tile_shape_t, typename axis_t=none_t>
    constexpr auto tiling_window(const array_t& array, const tile_shape_t& tile_shape, const axis_t& axis=axis_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto tiling_window = view::tiling_window(array,tile_shape,axis);
        return eval(
            tiling_window
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // tiling_window
}

#endif // NMTOOLS_ARRAY_TILING_WINDOW_HPP