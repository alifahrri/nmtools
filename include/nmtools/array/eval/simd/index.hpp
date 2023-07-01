#ifndef NMTOOLS_ARRAY_EVAL_SIMD_INDEX_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_INDEX_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/shape.hpp"

namespace nmtools::index
{
    enum class SIMD
    {
        PACKED=0,
        BROADCAST,
        SCALAR,
    };

    template <typename index_t=size_t, auto N_ELEM_PACK, typename out_shape_t>
    auto binary_2d_simd_shape(meta::as_type<N_ELEM_PACK>, const out_shape_t& out_shape)
    {
        using result_t = nmtools_array<index_t,2>;

        auto result = result_t{};

        auto n_rows = at(out_shape,0);
        auto n_cols = at(out_shape,1);

        // assume output layout is contiguous on the last axis
        // TODO: generalize to arbitrary order layout

        at(result,0) = n_rows;
        at(result,1) = (n_cols / N_ELEM_PACK) + (n_cols % N_ELEM_PACK);

        return result;
    }

    template <typename index_t=size_t, auto N_ELEM_PACK, typename simd_indices_t, typename out_shape_t, typename simd_shape_t>
    auto binary_2d_simd(meta::as_type<N_ELEM_PACK>, const simd_indices_t& simd_indices, const simd_shape_t& simd_shape, const out_shape_t& out_shape)
    {
        using tagged_index_t = nmtools_tuple<SIMD,index_t>;
        using result_t = nmtools_array<tagged_index_t,3>;

        auto result = result_t{};

        auto simd_col = at(simd_indices,1);
        auto simd_row = at(simd_indices,0);

        auto n_cols = at(out_shape,1);
        // auto n_rows = at(out_shape,0);

        auto n_simd = n_cols / N_ELEM_PACK;
        auto is_scalar = simd_col >= n_simd;
        at(result,2) = (is_scalar ? tagged_index_t{SIMD::SCALAR,simd_row} : tagged_index_t{SIMD::BROADCAST,simd_row});
        at(result,1) = (is_scalar ? tagged_index_t{SIMD::SCALAR,n_simd * N_ELEM_PACK + (simd_col - n_simd)} : tagged_index_t{SIMD::PACKED,simd_col * N_ELEM_PACK});
        at(result,0) = (is_scalar
            ? tagged_index_t{SIMD::SCALAR,simd_row*n_cols + n_simd * N_ELEM_PACK + (simd_col - n_simd) }
            : tagged_index_t{SIMD::PACKED,simd_row*n_cols + simd_col * N_ELEM_PACK }
        );

        return result;
    }

    template <auto N_ELEM_PACK, typename out_shape_t, typename index_t=size_t>
    struct binary_2d_simd_enumerator_t
    {
        using out_shape_type  = const out_shape_t;
        using simd_shape_type = const nmtools_array<index_t,2>;
        using simd_indices_type = simd_shape_type;

        meta::as_type<N_ELEM_PACK> n_elem_pack;
        out_shape_type  out_shape;
        simd_shape_type simd_shape;

        binary_2d_simd_enumerator_t(meta::as_type<N_ELEM_PACK>, const out_shape_t& out_shape)
            : n_elem_pack{}
            , out_shape(out_shape)
            , simd_shape(binary_2d_simd_shape(n_elem_pack,out_shape))
        {}

        auto size() const noexcept
        {
            return index::product(simd_shape);
        }

        auto operator[](size_t i) const
        {
            const auto simd_rows = at(simd_shape,0);
            const auto simd_cols = at(simd_shape,1);
            auto simd_indices = simd_indices_type{i / simd_cols, i % simd_cols};
            return binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape);
        }
    };

    template <typename index_t=size_t, auto N_ELEM_PACK, typename out_shape_t>
    auto binary_2d_simd_enumerator(meta::as_type<N_ELEM_PACK> n_elem_pack, const out_shape_t& out_shape)
    {
        return binary_2d_simd_enumerator_t(n_elem_pack,out_shape);
    }
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_EVAL_SIMD_INDEX_HPP