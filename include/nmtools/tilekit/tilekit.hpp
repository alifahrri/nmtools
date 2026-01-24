#ifndef NMTOOLS_TILEKIT_TILEKIT_HPP
#define NMTOOLS_TILEKIT_TILEKIT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/core.hpp"
#include "nmtools/array/tiling_window.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/index/add_indices.hpp"
#include "nmtools/ndarray/array.hpp"

namespace nmtools::tilekit::view
{
    // TODO: remove
    template <typename array_t, typename offset_t, typename shape_t, typename axis_t=none_t>
    constexpr auto load(const array_t& array, const offset_t& offset, const shape_t& shape, const axis_t& axis=axis_t{})
    {
        static_assert( meta::is_constant_index_array_v<shape_t> );
        static_assert( meta::is_constant_index_v<axis_t> || is_none_v<axis_t> );

        constexpr auto DIM = meta::len_v<offset_t>;
        static_assert( DIM > 0 );
        static_assert( meta::is_tuple_v<offset_t> );

        auto slices = utility::tuple_append(offset,Ellipsis);
        auto window = nmtools::view::tiling_window(array,shape,axis);
        auto sliced = unwrap(nmtools::view::apply_slice(window,slices));

        return sliced;
    }
}

namespace nmtools::tilekit
{
    struct scalar_t {};

    constexpr inline auto Scalar = scalar_t {};

    template <typename ctx_t, typename array_t, typename tile_shape_t, typename padding_t, typename=void>
    struct load_t;

    template <typename ctx_t, typename output_t, typename padding_t, typename=void>
    struct store_t;

    template <typename context_t, typename array_t, typename tile_shape_t, typename padding_t>
    struct load_t<
        context_t, array_t, tile_shape_t, padding_t
        , enable_if_t<is_same_v<remove_cvref_t<context_t>,none_t> || is_same_v<remove_cvref_t<context_t>,scalar_t>>
    > {
        using context_type    = context_t;
        using tile_shape_type = tile_shape_t;
        using array_type      = array_t;
        using element_type    = get_element_type_t<array_t>;
        using padding_type    = padding_t;

        static constexpr auto SIZE = index::product(to_value_v<tile_shape_t>);
        using buffer_type   = nmtools_array<element_type,SIZE>;
        using result_type   = object_t<buffer_type,tile_shape_type>;

        template <typename ctx_t, typename result_t, typename src_shape_t, typename offset_t, typename tile_stride_t>
        static auto load(ctx_t
            , result_t& result
            , const array_type& array
            , const src_shape_t& src_shape
            , const offset_t& offset
            , const tile_shape_type& tile_shape
            , const tile_stride_t& tile_stride
            , [[maybe_unused]] padding_type padding)
        {
            for (nm_size_t i=0; i<(nm_size_t)SIZE; i++) {
                auto tile_indices = index::compute_indices(i,tile_shape,tile_stride);
                auto src_indices  = index::add_indices(tile_indices,offset);
                if constexpr (padding_t::value) {
                    auto dim = len(src_indices);
                    auto valid = true;
                    for (nm_size_t j=0; (j<dim) && valid; j++) {
                        valid = valid && (at(src_indices,j) < at(src_shape,j));
                    }
                    // TODO: configurable padding value
                    result.data()[i] = (!valid ? 0 : apply_at(array,src_indices));
                } else {
                    result.data()[i] = apply_at(array,src_indices);
                }
            }
        }

        template <typename ctx_t, typename offset_t>
        static auto load(ctx_t
            , const array_type& array
            , const offset_t& offset
            , const tile_shape_type& tile_shape
            , padding_type padding)
        {
            auto result = result_type{};
            
            auto src_shape = shape(array);
            auto tile_stride = index::compute_strides(tile_shape);

            load(ctx_t{}, result,array,src_shape,offset,tile_shape,tile_stride,padding);

            return result;
        }

        template <typename ctx_t, typename offset_t>
        auto operator()(ctx_t, const array_type& array, const offset_t& offset, const tile_shape_type& tile_shape, padding_type padding) const
        {
            return load(ctx_t{},array,offset,tile_shape,padding);
        }
    }; // load_t

    template <typename context_t, typename output_t, typename padding_t>
    struct store_t<
        context_t, output_t, padding_t
        , enable_if_t<is_same_v<remove_cvref_t<context_t>,none_t> || is_same_v<remove_cvref_t<context_t>,scalar_t>>
    > {
        using context_type = context_t;
        using output_type  = output_t;
        using padding_type = padding_t;

        template <typename ctx_t, typename src_shape_t, typename offset_t, typename result_t>
        static auto store(ctx_t
            , output_type& output
            , const src_shape_t& src_shape
            , const offset_t& offset
            , const result_t& result
            , [[maybe_unused]] padding_type padding)
        {
            constexpr auto tile_shape  = fixed_shape_v<result_t>;
            constexpr auto tile_stride = index::compute_strides(tile_shape);
            constexpr auto SIZE = index::product(tile_shape);
            // TODO: use template_for to compute tile_indices at compile-time
            for (nm_size_t i=0; i<(nm_size_t)SIZE; i++) {
                auto tile_indices = index::compute_indices(i,tile_shape,tile_stride);
                auto src_indices  = index::add_indices(tile_indices,offset);
                if constexpr (padding_type::value) {
                    auto dim = len(src_indices);
                    auto valid = true;
                    for (nm_size_t j=0; (j<dim) && valid; j++) {
                        valid = valid && (at(src_indices,j) < at(src_shape,j));
                    }
                    if (valid) {
                        apply_at(output,src_indices) = result.data()[i];
                    }
                } else {
                    apply_at(output,src_indices) = result.data()[i];
                }
            }
        }

        template <typename ctx_t, typename offset_t, typename result_t>
        static auto store(ctx_t ctx
            , output_type& output
            , const offset_t& offset
            , const result_t& result
            , padding_type padding)
        {
            auto src_shape = shape(output);
            store(ctx,output,src_shape,offset,result,padding);
        }

        template <typename offset_t, typename result_t>
        auto operator()(context_type ctx, output_type& output, const offset_t& offset, const result_t& result, padding_type padding) const
        {
            return store(ctx,output,offset,result,padding);
        }
    };

    template <typename ctx_t, typename array_t, typename offset_t, typename tile_shape_t, typename padding_t=ct<0>>
    constexpr auto load(ctx_t&& ctx, const array_t& array, const offset_t& offset, const tile_shape_t& tile_shape, const padding_t& padding=padding_t{})
    {
        auto load = load_t<remove_cvref_t<ctx_t>,array_t,tile_shape_t,padding_t>{};
        return load(nmtools::forward<ctx_t>(ctx),array,offset,tile_shape,padding);
    }

    template <typename ctx_t, typename output_t, typename offset_t, typename result_t, typename padding_t=ct<0>>
    constexpr auto store([[maybe_unused]] ctx_t&& ctx, output_t& output, const offset_t& offset, const result_t& result, const padding_t& padding=padding_t{})
    {
        auto store = store_t<remove_cvref_t<ctx_t>,output_t,padding_t>{};
        return store(nmtools::forward<ctx_t>(ctx),output,offset,result,padding);
    }
}

// tilekit utility

namespace nmtools::tilekit
{
    template <typename block_shape_t>
    constexpr auto product(const block_shape_t& b_shape)
    {
        return nmtools::index::product(b_shape);
    }

    template <typename block_shape_t, typename tile_shape_t>
    struct ndoffset_t
    {
        using block_shape_type  = block_shape_t;
        using block_stride_type = meta::resolve_optype_t<index::compute_strides_t,block_shape_type>;
        using tile_shape_type   = tile_shape_t;
        using size_type = meta::resolve_optype_t<index::product_t,block_shape_t>;

        block_shape_type  block_shape_;
        block_stride_type block_stride_;
        tile_shape_type   tile_shape_;

        size_type size_;

        constexpr ndoffset_t(const block_shape_t& block_shape
            , const tile_shape_t& tile_shape)
            : block_shape_(block_shape)
            , block_stride_(index::compute_strides(block_shape))
            , tile_shape_(tile_shape)
            , size_(index::product(block_shape))
        {}

        constexpr auto size() const noexcept
        {
            return size_;
        }

        template <typename index_t>
        constexpr auto operator[](index_t i) const
        {
            auto indices = index::compute_indices(i,block_shape_,block_stride_);
            // assume fixed dim
            constexpr auto DIM = len_v<decltype(indices)>;
            meta::template_for<DIM>([&](auto i){
                constexpr auto I = decltype(i)::value;
                nmtools::get<I>(indices) *= nmtools::get<I>(tile_shape_);
            });
            return indices;
        }
    };

    struct compute_block_shape_t {};

    template <typename array_shape_t, typename tile_shape_t, typename padding_t=ct<0>>
    constexpr auto compute_block_shape(const array_shape_t& array_shape, const tile_shape_t& tile_shape, padding_t padding=padding_t{})
    {
        using result_t = resolve_optype_t<compute_block_shape_t,array_shape_t,tile_shape_t,padding_t>;

        auto result = result_t {};

        if constexpr (!is_fail_v<result_t>
            && !is_constant_index_array_v<result_t>
        ) {
            constexpr auto DIM = len_v<result_t>;

            if constexpr (DIM > 0) {
                template_for<DIM>([&](auto i){
                    if constexpr (!is_constant_index_v<decltype(at(result,i))>) {
                        const auto& a_i = at(array_shape,i);
                        const auto& t_i = at(tile_shape,i);
                        if (has_value(a_i) && has_value(t_i)) {
                            at(result,i) = (a_i / t_i) + (padding ? ((a_i % t_i) ? 1 : 0) : 0);
                        }
                    }
                });
            } else {
                // TODO: check if len(array_shape) == len(tile_shape);
                auto dim = len(array_shape);
                if constexpr (is_resizable_v<result_t>) {
                    result.resize(dim);
                }
                for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
                    const auto& a_i = at(array_shape,i);
                    const auto& t_i = at(tile_shape,i);
                    if (has_value(a_i) && has_value(t_i)) {
                        at(result,i) = (a_i / t_i) + (padding ? ((a_i % t_i) ? 1 : 0) : 0);
                    }
                }
            }
        }

        return result;
    }

    template <typename array_shape_t, typename tile_shape_t, typename padding_t=ct<0>>
    constexpr auto ndoffset([[maybe_unused]] const array_shape_t& a_shape
        , [[maybe_unused]] const tile_shape_t& t_shape
        , padding_t padding=padding_t{})
    {
        auto b_shape = compute_block_shape(a_shape,t_shape,padding);
        return ndoffset_t(b_shape,t_shape);
    }
}

namespace nmtools::meta
{
    namespace error {
        template <typename...>
        struct COMPUTE_BLOCK_SHAPE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename array_shape_t, typename tile_shape_t, typename padding_t>
    struct resolve_optype<
        void, tilekit::compute_block_shape_t, array_shape_t, tile_shape_t, padding_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<array_shape_t>
                || !is_index_array_v<tile_shape_t>
                || !is_index_v<padding_t>
            ) {
                using type = error::COMPUTE_BLOCK_SHAPE_UNSUPPORTED<array_shape_t,tile_shape_t,padding_t>;
                return as_value_v<type>;
            } else if constexpr (
                (is_constant_index_array_v<array_shape_t> || is_mixed_index_array_v<array_shape_t>)
                && (is_constant_index_array_v<tile_shape_t> || is_mixed_index_array_v<tile_shape_t>)
                && (is_constant_index_v<padding_t>)
            ) {
                constexpr auto array_shape = to_value_v<array_shape_t>;
                constexpr auto tile_shape  = to_value_v<tile_shape_t>;
                constexpr auto padding     = to_value_v<padding_t>;
                constexpr auto result = tilekit::compute_block_shape(array_shape,tile_shape,padding);
                using ::nmtools::at, ::nmtools::len;
                constexpr auto N = len(result);
                // check if should return array
                constexpr auto return_array = [&](){
                    auto all_none = !has_value(at(result,0));
                    for (nm_size_t i=1; i<(nm_size_t)N; i++) {
                        all_none &= !has_value(at(result,i));
                    }
                    return all_none;
                }();
                if constexpr (return_array) {
                    using type = nmtools_array<nm_size_t,N>;
                    return as_value_v<type>;
                } else {
                    return template_reduce<N>([&](auto init, auto I){
                        using init_t = type_t<decltype(init)>;
                        constexpr auto res_i = at(result,I);
                        if constexpr (has_value(res_i)) {
                            using type = append_type_t<init_t,ct<(nm_size_t)res_i>>;
                            return as_value_v<type>;
                        } else {
                            using type = append_type_t<init_t,nm_size_t>;
                            return as_value_v<type>;
                        }
                    }, as_value_v<nmtools_tuple<>>);
                }
            } else if constexpr (
                is_nullable_index_array_v<array_shape_t>
                || is_nullable_index_array_v<tile_shape_t>
            ) {
                using type = conditional_t<
                    is_nullable_index_array_v<array_shape_t>
                    , array_shape_t
                    , tile_shape_t
                >;
                return as_value_v<type>;
            } else {
                constexpr auto A_DIM = len_v<array_shape_t>;
                constexpr auto T_DIM = len_v<tile_shape_t>;
                [[maybe_unused]] constexpr auto A_MAX_DIM = max_len_v<array_shape_t>;
                [[maybe_unused]] constexpr auto T_MAX_DIM = max_len_v<tile_shape_t>;
                if constexpr ((A_DIM > 0) && (T_DIM > 0)) {
                    // TODO: assert if A_DIM == T_DIM
                    using type = nmtools_array<nm_size_t,A_DIM>;
                    return as_value_v<type>;
                } else if constexpr (A_MAX_DIM > 0) {
                    using type = nmtools_static_vector<nm_size_t,A_MAX_DIM>;
                    return as_value_v<type>;
                } else if constexpr (T_MAX_DIM > 0) {
                    using type = nmtools_static_vector<nm_size_t,T_MAX_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_TILEKIT_TILEKIT_HPP