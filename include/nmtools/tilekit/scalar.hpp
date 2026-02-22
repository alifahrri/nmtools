#ifndef NMTOOLS_TILEKIT_SCALAR_HPP
#define NMTOOLS_TILEKIT_SCALAR_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/core/unroll.hpp"
#include "nmtools/tilekit/tilekit.hpp"

namespace nmtools::tilekit
{
    struct scalar_t
    {
        nm_size_t worker_id = 0;
        nm_size_t worker_size = 1;

        static auto create_context(nm_size_t worker_id, nm_size_t worker_size)
        {
            return scalar_t{worker_id,worker_size};
        }
    };

    constexpr inline auto Scalar = scalar_t {};

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
        using result_type   = object_t<buffer_type,tile_shape_type,resolve_stride_type_t,row_major_offset_t,object_eval_resolver_t<LayoutKind::RowMajor>,unroll_t,false>;

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
            template_for<SIZE>([&](auto i){
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
            });
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
            template_for<SIZE>([&](auto i){
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
            });
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

    inline auto worker_id(scalar_t ctx)
    {
        return nmtools_tuple{ctx.worker_id};
    }

    inline auto worker_size(scalar_t ctx)
    {
        return nmtools_tuple{ctx.worker_size};
    }
}

#endif // NMTOOLS_TILEKIT_SCALAR_HPP