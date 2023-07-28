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

    template <typename index_t=size_t, auto N_ELEM_PACK, typename out_shape_t, typename lhs_shape_t, typename rhs_shape_t>
    auto binary_2d_simd_shape(meta::as_type<N_ELEM_PACK>, [[maybe_unused]] const out_shape_t& out_shape, const lhs_shape_t& lhs_shape, const rhs_shape_t& rhs_shape)
    {
        using result_t = nmtools_array<index_t,2>;

        auto result = result_t{};

        auto lhs_rows = at(lhs_shape,0);

        auto rhs_rows = at(rhs_shape,0);

        auto out_cols = at(out_shape,1);

        // assume layout is contiguous on last axis
        // TODO: generalize to arbitrary order layout

        // assume lhs_rows is equal to rhs_rows already

        // the number of packable load/store

        auto n_packed = out_cols / N_ELEM_PACK;
        at(result,0) = (rhs_rows == 1 ? lhs_rows : rhs_rows);
        at(result,1) = n_packed + out_cols % N_ELEM_PACK;

        return result;
    }

    template <typename index_t=size_t, auto N_ELEM_PACK, typename simd_indices_t, typename out_shape_t, typename simd_shape_t, typename lhs_shape_t, typename rhs_shape_t>
    auto binary_2d_simd(meta::as_type<N_ELEM_PACK>, const simd_indices_t& simd_indices, [[maybe_unused]] const simd_shape_t& simd_shape, const out_shape_t& out_shape, const lhs_shape_t& lhs_shape, const rhs_shape_t& rhs_shape)
    {
        using tagged_index_t = nmtools_tuple<SIMD,index_t>;
        using result_t = nmtools_array<tagged_index_t,3>;

        auto result = result_t{};

        auto lhs_cols = at(lhs_shape,1);
        auto lhs_rows = at(lhs_shape,0);

        auto out_cols = at(out_shape,1);

        auto rhs_cols = at(rhs_shape,1);
        auto rhs_rows = at(rhs_shape,0);

        auto simd_col = at(simd_indices,1);
        auto simd_row = at(simd_indices,0);

        auto n_packed = out_cols / N_ELEM_PACK;

        auto is_scalar_res = simd_col >= n_packed;

        auto scalar_res_idx = n_packed * N_ELEM_PACK + (simd_col - n_packed) + (simd_row * out_cols);

        auto packed_res_idx = simd_col * N_ELEM_PACK + (simd_row * out_cols);

        // if result is scalar then lhs & rhs must be scalar
        auto is_scalar_rhs    = is_scalar_res && (simd_col >= (rhs_cols  / N_ELEM_PACK));
        auto is_broadcast_rhs = (rhs_cols == 1);
        if (is_scalar_rhs) {
            auto n_packed = rhs_cols / N_ELEM_PACK;
            auto scalar_rhs_idx = (rhs_cols == 1 ? simd_row : ((n_packed * N_ELEM_PACK) + (simd_col - n_packed) + (simd_row * out_cols * static_cast<int>(rhs_rows > 1))));
            at(result,2) = tagged_index_t{SIMD::SCALAR,scalar_rhs_idx};
        } else if (is_broadcast_rhs) {
            at(result,2) = tagged_index_t{SIMD::BROADCAST,simd_row};
        } else {
            auto packed_rhs_idx = simd_col * N_ELEM_PACK + (simd_row * out_cols * static_cast<int>(rhs_rows > 1));
            at(result,2) = tagged_index_t{SIMD::PACKED,packed_rhs_idx};
        }

        auto is_scalar_lhs    = is_scalar_res && (simd_col >= (lhs_cols / N_ELEM_PACK));
        auto is_broadcast_lhs = (lhs_cols == 1);
        if (is_scalar_lhs) {
            auto n_packed = lhs_cols / N_ELEM_PACK;
            auto scalar_lhs_idx = (lhs_cols == 1 ? simd_row : ((n_packed * N_ELEM_PACK) + (simd_col - n_packed) + (simd_row * out_cols * static_cast<int>(lhs_rows > 1))));
            at(result,1) = tagged_index_t(SIMD::SCALAR,scalar_lhs_idx);
        } else if (is_broadcast_lhs) {
            at(result,1) = tagged_index_t{SIMD::BROADCAST,simd_row};
        } else {
            auto packed_lhs_idx = simd_col * N_ELEM_PACK + (simd_row * out_cols * static_cast<int>(lhs_rows > 1));
            at(result,1) = tagged_index_t{SIMD::PACKED,packed_lhs_idx};
        }

        at(result,0) = (is_scalar_res ? tagged_index_t{SIMD::SCALAR,scalar_res_idx} : tagged_index_t{SIMD::PACKED,packed_res_idx});

        return result;
    }

    template <auto N_ELEM_PACK, typename out_shape_t, typename lhs_shape_t, typename rhs_shape_t, typename index_t=size_t>
    struct binary_2d_simd_enumerator_t
    {
        using out_shape_type  = const out_shape_t;
        using lhs_shape_type  = const lhs_shape_t;
        using rhs_shape_type  = const rhs_shape_t;
        using simd_shape_type = const nmtools_array<index_t,2>;
        using simd_indices_type = simd_shape_type;

        meta::as_type<N_ELEM_PACK> n_elem_pack;
        out_shape_type  out_shape;
        lhs_shape_type  lhs_shape;
        rhs_shape_type  rhs_shape;
        simd_shape_type simd_shape;

        binary_2d_simd_enumerator_t(meta::as_type<N_ELEM_PACK>, const out_shape_t& out_shape, const lhs_shape_t& lhs_shape, const rhs_shape_t& rhs_shape)
            : n_elem_pack{}
            , out_shape(out_shape)
            , lhs_shape(lhs_shape)
            , rhs_shape(rhs_shape)
            , simd_shape(binary_2d_simd_shape(n_elem_pack,out_shape,lhs_shape,rhs_shape))
        {}

        auto size() const noexcept
        {
            return index::product(simd_shape);
        }

        auto operator[](size_t i) const
        {
            const auto simd_cols = at(simd_shape,1);
            auto simd_indices = simd_indices_type{i / simd_cols, i % simd_cols};
            return binary_2d_simd(n_elem_pack,simd_indices,simd_shape,out_shape,lhs_shape,rhs_shape);
        }
    };

    template <typename index_t=size_t, auto N_ELEM_PACK, typename out_shape_t, typename lhs_shape_t, typename rhs_shape_t>
    auto binary_2d_simd_enumerator(meta::as_type<N_ELEM_PACK> n_elem_pack, const out_shape_t& out_shape, const lhs_shape_t& lhs_shape, const rhs_shape_t& rhs_shape)
    {
        return binary_2d_simd_enumerator_t(n_elem_pack,out_shape,lhs_shape,rhs_shape);
    }
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_EVAL_SIMD_INDEX_HPP