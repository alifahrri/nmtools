#ifndef NMTOOLS_ARRAY_EVAL_SIMD_INDEX_UFUNC_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_INDEX_UFUNC_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/eval/simd/index/common.hpp"
#include "nmtools/array/index/compute_offset.hpp"
#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/array/index/compute_indices.hpp"

namespace nmtools::index
{
    template <typename index_t=size_t, auto N_ELEM_PACK, typename out_shape_t, typename lhs_shape_t, typename rhs_shape_t>
    auto binary_2d_simd_shape(meta::as_type<N_ELEM_PACK>, [[maybe_unused]] const out_shape_t& out_shape, const lhs_shape_t& lhs_shape, const rhs_shape_t& rhs_shape)
    {
        using result_t = nmtools_array<index_t,2>;

        auto result = result_t{};

        auto lhs_rows = at(lhs_shape,0);

        auto rhs_rows = at(rhs_shape,0);

        auto out_cols = (len(out_shape) == 1 ? at(out_shape,0) : at(out_shape,1));

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

        auto out_cols = (len(out_shape) == 1 ? at(out_shape,0) : at(out_shape,1));

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

    enum ReductionKind : int
    {
        HORIZONTAL=0,
        VERTICAL=1,
    };

    template <typename index_t=size_t, ReductionKind reduction_kind, auto N_ELEM_PACK, typename inp_shape_t, typename out_shape_t, typename axis_t>
    auto reduction_nd_reshape(meta::as_type<reduction_kind>, meta::as_type<N_ELEM_PACK>, const inp_shape_t& inp_shape, const out_shape_t&, [[maybe_unused]] axis_t axis)
    {
        using result_t = nmtools_array<index_t,2>;

        auto result = result_t{};

        auto dim = len(inp_shape);

        if constexpr (meta::is_resizable_v<result_t>) {
            result.resize(2); // strictly 2
        }
        at(result,0) = 1;
        at(result,1) = 1;

        if constexpr (reduction_kind == ReductionKind::HORIZONTAL) {
            auto horizontal_axis = dim-1; // last
            for (size_t i=0; i<(size_t)horizontal_axis; i++) {
                at(result,0) *= at(inp_shape,i);
            }
            auto n_ops = at(inp_shape, horizontal_axis);
            at(result,1) = n_ops;
        } else if constexpr (reduction_kind == ReductionKind::VERTICAL) {
            auto vertical_axis = dim;
            int i = 0;
            for (; i<=(int)axis; i++) {
                at(result,0) *= at(inp_shape,i);
            }
            for (; i<(int)vertical_axis; i++) {
                at(result,1) *= at(inp_shape,i);
            }
        }
        if (dim == 1) {
            at(result,0) = 1;
            at(result,1) = at(inp_shape,0);
        }

        return result;
    }

    template <typename index_t=size_t, ReductionKind reduction_kind, auto N_ELEM_PACK, typename inp_shape_t, typename out_shape_t>
    auto reduction_2d_shape(meta::as_type<reduction_kind>, meta::as_type<N_ELEM_PACK>, const inp_shape_t& inp_shape, const out_shape_t&)
    {
        using result_t = nmtools_array<index_t,2>;

        auto result = result_t{};

        if constexpr (meta::is_resizable_v<result_t>) {
            result.resize(2); // strictly 2
        }

        constexpr auto row_idx = meta::ct_v<0>;
        constexpr auto col_idx = meta::ct_v<1>;

        [[maybe_unused]] auto inp_rows = at(inp_shape,row_idx);
        [[maybe_unused]] auto inp_cols = at(inp_shape,col_idx);

        if constexpr (reduction_kind == ReductionKind::HORIZONTAL) {
            at(result,row_idx) = inp_rows;
            at(result,col_idx) = (inp_cols / N_ELEM_PACK) + ((inp_cols % N_ELEM_PACK ? 1 : 0));
        } else if constexpr (reduction_kind == ReductionKind::VERTICAL) {
            at(result,row_idx) = inp_rows;
            at(result,col_idx) = (inp_cols / N_ELEM_PACK) + (inp_cols % N_ELEM_PACK);
        }

        return result;
    }
    
    template <typename index_t=size_t, ReductionKind reduction_kind, auto N_ELEM_PACK, typename inp_shape_t, typename out_shape_t, typename axis_t=index_t>
    auto reduction_2d_shape(meta::as_type<reduction_kind> kind, meta::as_type<N_ELEM_PACK> n_elem_pack, const inp_shape_t& inp_shape, const out_shape_t& out_shape, axis_t axis)
    {
        auto inp_reshaped = reduction_nd_reshape(kind,n_elem_pack,inp_shape,out_shape,axis);
        auto result = reduction_2d_shape(kind,n_elem_pack,inp_reshaped,out_shape);
        return result;
    }

    template <typename index_t=size_t, ReductionKind reduction_kind, auto N_ELEM_PACK, typename simd_index_t, typename simd_shape_t, typename out_shape_t, typename inp_shape_t>
    auto reduction_2d(meta::as_type<reduction_kind>, meta::as_type<N_ELEM_PACK>, const simd_index_t& simd_index, const simd_shape_t&, const out_shape_t& out_shape, const inp_shape_t& inp_shape)
    {
        using tagged_index_t = nmtools_tuple<SIMD,index_t>;
        using result_t = nmtools_array<tagged_index_t,2>;

        auto result = result_t {};

        const auto n_ops  = [&](){
            if constexpr (reduction_kind == ReductionKind::VERTICAL) {
                return at(inp_shape,meta::ct_v<-1>);
            } else {
                return at(inp_shape,meta::ct_v<-1>);
            }
        }();
        const auto n_simd = n_ops / N_ELEM_PACK;

        if constexpr (reduction_kind == ReductionKind::HORIZONTAL) {
            const auto n_rest = n_ops - (n_simd * N_ELEM_PACK);
            auto out_index  = at(simd_index,meta::ct_v<0>);
            auto inp_offset = (out_index * n_ops);
            auto inner_idx  = at(simd_index,meta::ct_v<1>);
            auto inp_index  = (inner_idx * N_ELEM_PACK);

            const auto out_tag = (nm_size_t(inner_idx+1) == nm_size_t(n_simd+static_cast<bool>(n_rest)) ? SIMD::ACCUMULATE : SIMD::NOP);
            const auto inp_tag = static_cast<bool>(nm_size_t(inp_index + N_ELEM_PACK) > nm_size_t(n_ops)) ? static_cast<SIMD>(N_ELEM_PACK - n_rest) : SIMD::PACKED;
            inp_index = inp_offset + inp_index;
            at(result,meta::ct_v<0>) = tagged_index_t{out_tag,static_cast<index_t>(out_index)};
            at(result,meta::ct_v<1>) = tagged_index_t{inp_tag,static_cast<index_t>(inp_index)};
        } else if constexpr (reduction_kind == ReductionKind::VERTICAL) {
            auto inp_offset = at(simd_index,meta::ct_v<0>) * at(inp_shape,meta::ct_v<1>);
            auto out_offset = len(out_shape) > 1 ? (at(simd_index,meta::ct_v<0>) / (at(inp_shape,meta::ct_v<0>) / at(out_shape,meta::ct_v<0>))) * at(out_shape,meta::ct_v<-1>) : 0;
            auto out_index  = at(simd_index,meta::ct_v<1>) * N_ELEM_PACK;
            auto inp_index  = at(simd_index,meta::ct_v<1>) * N_ELEM_PACK;

            auto rel_scalar_index = n_simd * N_ELEM_PACK + (at(simd_index,meta::ct_v<1>) - n_simd);
            out_index = (nm_size_t)out_index > (nm_size_t)n_ops ? (out_offset + rel_scalar_index) : (out_offset + out_index);
            inp_index = (nm_size_t)inp_index > (nm_size_t)n_ops ? (inp_offset + rel_scalar_index) : (inp_offset + inp_index);

            // prefer scalar instead of padding because scalar store for output
            const auto out_tag = static_cast<bool>(nm_size_t((at(simd_index,meta::ct_v<1>) * N_ELEM_PACK) + N_ELEM_PACK) <= nm_size_t(n_ops)) ? SIMD::ACCUMULATE_PACKED : SIMD::ACCUMULATE;
            const auto inp_tag = static_cast<bool>(nm_size_t((at(simd_index,meta::ct_v<1>) * N_ELEM_PACK) + N_ELEM_PACK) <= nm_size_t(n_ops)) ? SIMD::PACKED : SIMD::SCALAR;
            at(result,meta::ct_v<0>) = tagged_index_t{out_tag,static_cast<index_t>(out_index)};
            at(result,meta::ct_v<1>) = tagged_index_t{inp_tag,static_cast<index_t>(inp_index)};
        }

        return result;
    } // reduction_2d

    template <typename index_t, ReductionKind reduction_kind, auto N_ELEM_PACK, typename out_shape_t, typename inp_shape_t>
    struct reduction_2d_enumerator_t
    {
        using inp_shape_type  = const inp_shape_t;
        using out_shape_type  = const out_shape_t;

        using simd_shape_type = meta::remove_cvref_t<decltype(reduction_2d_shape(meta::as_type_v<reduction_kind>,meta::as_type_v<N_ELEM_PACK>,meta::declval<inp_shape_t>(),meta::declval<out_shape_t>()))>;
        using simd_index_type = nmtools_array<index_t,2>;
        using index_type = index_t;
        using size_type  = index_t;

        meta::as_type<N_ELEM_PACK> n_elem_pack;
        meta::as_type<reduction_kind> kind;
        out_shape_type  out_shape;
        inp_shape_type  inp_shape;
        simd_shape_type simd_shape;

        reduction_2d_enumerator_t(meta::as_type<N_ELEM_PACK>, meta::as_type<reduction_kind>, const out_shape_t& out_shape_, const inp_shape_t& inp_shape_)
            : n_elem_pack{}
            , kind{}
            , out_shape(out_shape_)
            , inp_shape(inp_shape_)
            , simd_shape(reduction_2d_shape(kind,n_elem_pack,inp_shape,out_shape))
        {}

        constexpr auto size() const noexcept
        {
            return index::product(simd_shape);
        }

        constexpr auto operator[](index_type i) const noexcept
        {
            auto index_i = i / at(simd_shape,meta::ct_v<1>);
            auto index_j = i % at(simd_shape,meta::ct_v<1>);
            return reduction_2d(kind,n_elem_pack,simd_index_type{index_i,index_j},simd_shape,out_shape,inp_shape);
        }
    };

    template <typename index_t=size_t, ReductionKind reduction_kind, auto N_ELEM_PACK, typename out_shape_t, typename inp_shape_t>
    constexpr auto reduction_2d_enumerator(meta::as_type<reduction_kind> kind, meta::as_type<N_ELEM_PACK> n_elem_pack, const out_shape_t& out_shape, const inp_shape_t& inp_shape)
    {
        using enumerator_t = reduction_2d_enumerator_t<index_t,reduction_kind,N_ELEM_PACK,out_shape_t,inp_shape_t>;
        return enumerator_t{n_elem_pack,kind,out_shape,inp_shape};
    }

    template <typename index_t=size_t, ReductionKind reduction_kind, auto N_ELEM_PACK, typename out_shape_t, typename inp_shape_t, typename axis_t>
    constexpr auto reduction_2d_enumerator(meta::as_type<reduction_kind> kind, meta::as_type<N_ELEM_PACK> n_elem_pack, const out_shape_t& out_shape, const inp_shape_t& inp_shape, axis_t axis)
    {
        auto inp_reshaped = reduction_nd_reshape(kind,n_elem_pack,inp_shape,out_shape,axis);
        auto out_reshaped = reduction_nd_reshape(kind,n_elem_pack,out_shape,out_shape,axis);
        return reduction_2d_enumerator(kind,n_elem_pack,out_reshaped,inp_reshaped);
    }

    template <auto N_ELEM_PACK, typename out_shape_t, typename lhs_shape_t, typename rhs_shape_t>
    constexpr auto outer_simd_shape(meta::as_type<N_ELEM_PACK>, const out_shape_t& out_shape, const lhs_shape_t& lhs_shape, const rhs_shape_t& rhs_shape)
    {
        // TODO: compile-time inference
        // same dim as out
        using result_t = out_shape_t;
        auto result = result_t {};

        if constexpr (meta::is_resizable_v<result_t>) {
            auto dim = len(out_shape);
            result.resize(dim);
        }

        const auto n_ops = at(out_shape,meta::ct_v<-1>);
        const auto n_packed_ops = n_ops / N_ELEM_PACK;

        auto lhs_dim = len(lhs_shape);
        for (size_t i=0; i<lhs_dim; i++) {
            at(result,i) = at(lhs_shape,i);
        }
        auto rhs_dim = len(rhs_shape);
        for (size_t i=0; i<rhs_dim; i++) {
            at(result,lhs_dim+i) = at(rhs_shape,i);
        }
        at(result,meta::ct_v<-1>) = n_packed_ops + (n_ops % N_ELEM_PACK ? 1 : 0);

        return result;
    } // outer_simd_shape

    template <typename index_t=size_t, auto N_ELEM_PACK, typename simd_index_t, typename simd_shape_t, typename out_strides_t, typename out_shape_t, typename lhs_shape_t, typename rhs_shape_t, typename lhs_strides_t, typename rhs_strides_t>
    constexpr auto outer_simd(meta::as_type<N_ELEM_PACK>, const simd_index_t& simd_index, const simd_shape_t&, const out_strides_t& out_strides, const out_shape_t& out_shape, const lhs_shape_t& lhs_shape, const rhs_shape_t& rhs_shape, const lhs_strides_t& lhs_strides, const rhs_strides_t& rhs_strides)
    {
        using tagged_index_t = nmtools_tuple<SIMD,index_t>;
        using result_t = nmtools_array<tagged_index_t,3>;

        const auto compute_outer_simd_offset = [](const auto& indices, const auto& strides){
            index_t offset = 0;
            auto m = len(indices)-1;
            for (index_t i=0; i<m; i++) {
                offset += static_cast<index_t>(at(strides,i)) * static_cast<index_t>(at(indices,i));
            }
            return offset;
        };

        const auto n_ops = at(out_shape,meta::ct_v<-1>);
        const auto n_packed_ops = n_ops / N_ELEM_PACK;

        // assume simd_index is 2D
        const auto s_j = at(simd_index,meta::ct_v<-1>);

        const auto out_tag = s_j * N_ELEM_PACK + N_ELEM_PACK > n_ops ? static_cast<SIMD>(N_ELEM_PACK - (n_ops - (n_packed_ops * N_ELEM_PACK))) : SIMD::PACKED;
        const auto lhs_tag = SIMD::BROADCAST;
        const auto rhs_tag = out_tag;

        const auto outer_offset = compute_outer_simd_offset(simd_index,out_strides);

        const auto compute_offset = [](const auto& indices, const auto& strides, index_t start_dim, index_t N){
            index_t offset = 0;
            for (index_t i=0; i<N; i++) {
                index_t stride = at(strides,i);
                index_t index  = at(indices,i+start_dim);
                offset += stride * index;
            }
            return offset;
        };
        const auto out_offset = outer_offset + (s_j * N_ELEM_PACK);

        auto lhs_dim = len(lhs_shape);
        auto rhs_dim = len(rhs_shape);
        const auto lhs_offset = [&]()->index_t{
            switch (lhs_dim) {
                case 1: {
                    return at(simd_index,meta::ct_v<0>);
                } break;
                case 2: {
                    // only works for 2-dim
                    return at(simd_index,meta::ct_v<0>) * at(out_shape,meta::ct_v<1>) + at(simd_index,meta::ct_v<1>);
                } break;
                default: {
                    return compute_offset(simd_index,lhs_strides,0,lhs_dim);
                }
            }
        }();
        const auto rhs_offset = [&]()->index_t{
            switch (rhs_dim) {
                case 1: {
                    return s_j * N_ELEM_PACK;
                } break;
                case 2: {
                    // only works for 2-dim
                    return at(simd_index,meta::ct_v<-2>) * at(out_shape,meta::ct_v<-1>) + (s_j * N_ELEM_PACK);
                } break;
                default: {
                    auto rhs_offset = compute_offset(simd_index,rhs_strides,lhs_dim,rhs_dim-1);
                    return rhs_offset + (s_j * N_ELEM_PACK);
                }
            }
            // (rhs_tag == SIMD::PACKED ? (s_j * N_ELEM_PACK) : (s_j) * N_ELEM_PACK);
        }();

        auto result = result_t {};
        at(result,0) = tagged_index_t{out_tag,out_offset};
        at(result,1) = tagged_index_t{lhs_tag,lhs_offset};
        at(result,2) = tagged_index_t{rhs_tag,rhs_offset};

        return result;
    } // outer_simd

    template <typename index_t=size_t, auto N_ELEM_PACK, typename simd_index_t, typename simd_shape_t, typename out_shape_t, typename lhs_shape_t, typename rhs_shape_t>
    constexpr auto outer_simd(meta::as_type<N_ELEM_PACK> n_elem_pack, const simd_index_t& simd_index, const simd_shape_t& simd_shape, const out_shape_t& out_shape, const lhs_shape_t& lhs_shape, const rhs_shape_t& rhs_shape)
    {
        const auto out_strides = compute_strides(out_shape);
        const auto lhs_strides = compute_strides(lhs_shape);
        const auto rhs_strides = compute_strides(rhs_shape);
        return outer_simd(n_elem_pack,simd_index,simd_shape,out_strides,out_shape,lhs_shape,rhs_shape,lhs_strides,rhs_strides);
    } // outer_simd

    template <typename index_t, auto N_ELEM_PACK, typename out_shape_t, typename lhs_shape_t, typename rhs_shape_t>
    struct outer_simd_enumerator_t
    {
        using out_shape_type = const out_shape_t;
        using lhs_shape_type = const lhs_shape_t;
        using rhs_shape_type = const rhs_shape_t;

        using simd_shape_type = out_shape_t;
        using index_type = index_t;
        using size_type  = index_t;
        using simd_index_type = simd_shape_type;

        using out_strides_type  = meta::remove_cvref_t<decltype(compute_strides(meta::declval<out_shape_type>()))>;
        using lhs_strides_type  = meta::remove_cvref_t<decltype(compute_strides(meta::declval<lhs_shape_type>()))>;
        using rhs_strides_type  = meta::remove_cvref_t<decltype(compute_strides(meta::declval<rhs_shape_type>()))>;
        using simd_strides_type = meta::remove_cvref_t<decltype(compute_strides(meta::declval<simd_shape_type>()))>;

        meta::as_type<N_ELEM_PACK> n_elem_pack;
        out_shape_type  out_shape;
        lhs_shape_type  lhs_shape;
        rhs_shape_type  rhs_shape;
        simd_shape_type simd_shape;
        out_strides_type  out_strides;
        lhs_strides_type  lhs_strides;
        rhs_strides_type  rhs_strides;
        simd_strides_type simd_strides;

        outer_simd_enumerator_t(meta::as_type<N_ELEM_PACK>, const out_shape_t& out_shape_, const lhs_shape_t& lhs_shape_, const rhs_shape_t& rhs_shape_)
            : n_elem_pack{}
            , out_shape(out_shape_)
            , lhs_shape(lhs_shape_)
            , rhs_shape(rhs_shape_)
            , simd_shape(outer_simd_shape(n_elem_pack,out_shape_,lhs_shape_,rhs_shape_))
            , out_strides(compute_strides(out_shape))
            , lhs_strides(compute_strides(lhs_shape))
            , rhs_strides(compute_strides(rhs_shape))
            , simd_strides(compute_strides(simd_shape))
        {}

        constexpr auto size() const noexcept
        {
            return index::product(simd_shape);
        }

        constexpr auto operator[](index_type i) const
        {
            auto index = compute_indices(i,simd_shape,simd_strides);
            return outer_simd(n_elem_pack,index,simd_shape,out_strides,out_shape,lhs_shape,rhs_shape,lhs_strides,rhs_strides);
        }
    }; // outer_simd_enumerator_t

    template <typename index_t=size_t, auto N_ELEM_PACK, typename out_shape_t, typename lhs_shape_t, typename rhs_shape_t>
    constexpr auto outer_simd_enumerator(meta::as_type<N_ELEM_PACK> n_elem_pack, const out_shape_t& out_shape, const lhs_shape_t& lhs_shape, const rhs_shape_t& rhs_shape)
    {
        using enumerator_type = outer_simd_enumerator_t<index_t,N_ELEM_PACK,out_shape_t,lhs_shape_t,rhs_shape_t>;
        return enumerator_type{n_elem_pack,out_shape,lhs_shape,rhs_shape};
    } // outer_simd_enumerator
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_EVAL_SIMD_INDEX_UFUNC_HPP