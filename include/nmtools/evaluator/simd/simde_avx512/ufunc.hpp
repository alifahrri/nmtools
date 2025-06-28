#ifndef NMTOOLS_ARRAY_EVAL_SIMD_SIMDE_AVX512_UFUNC_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_SIMDE_AVX512_UFUNC_HPP

#include "nmtools/evaluator/simd/simde_avx512/simd_op.hpp"

namespace nmtools::simd
{
    template <typename data_t, typename lambda_t>
    struct ufunc_simd_t<view::softshrink_t<lambda_t>,simde_avx512_t,data_t> : simd_op_t<simde_avx512_t,data_t>
    {
        using simd_t = simd_op_t<simde_avx512_t,data_t>;
        using simd_dtype_t = decltype(simd_t::set1(0));
        using ufunc_op_t = view::softshrink_t<lambda_t>;

        const simd_dtype_t zero = simd_t::set1(0);
        const simd_dtype_t one  = simd_t::set1(1);
        const simd_dtype_t pos_lambda;
        const simd_dtype_t neg_lambda;

        ufunc_simd_t(ufunc_op_t op)
            : pos_lambda(simd_t::set1(op.lambda))
            , neg_lambda(simd_t::set1(-op.lambda))
        {};

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t a) const noexcept
        {
            // __mmaskN
            const auto gt_pos_lambda = simd_t::cmpgt(a,pos_lambda);
            const auto lt_neg_lambda = simd_t::cmplt(a,neg_lambda);

            auto zero_mask_r = simd_t::cmple(a,pos_lambda);
            auto zero_mask_l = simd_t::cmpge(a,neg_lambda);
            auto zero_mask = [=](){
                using zero_mask_t = decltype(zero_mask_l);
                if constexpr (meta::is_same_v<zero_mask_t,simde__mmask16>) {
                    return simde_knot_mask16(simde_kxor_mask16(zero_mask_l,zero_mask_r));
                } else if constexpr (meta::is_same_v<zero_mask_t,simde__mmask32>) {
                    return simde_knot_mask32(simde_kxor_mask32(zero_mask_l,zero_mask_r));
                } else if constexpr (meta::is_same_v<zero_mask_t,simde__mmask64>) {
                    return simde_knot_mask64(simde_kxor_mask64(zero_mask_l,zero_mask_r));
                } else if constexpr (meta::is_same_v<zero_mask_t,simde__mmask8>) {
                    return simde_knot_mask8(simde_kxor_mask8(zero_mask_l,zero_mask_r));
                }
            }();

            // __mm512
            const auto x_sub_lambda = simd_t::sub(a,pos_lambda);
            const auto x_add_lambda = simd_t::add(a,pos_lambda);

            a = simd_t::mask_blend(gt_pos_lambda,a,x_sub_lambda);
            a = simd_t::mask_blend(lt_neg_lambda,a,x_add_lambda);
            a = simd_t::mask_blend(zero_mask,a,zero);

            return a;
        }
    }; // ufunc_simd_t

    template <typename data_t, typename lambda_t>
    struct ufunc_simd_t<view::hardshrink_t<lambda_t>,simde_avx512_t,data_t> : simd_op_t<simde_avx512_t,data_t>
    {
        using simd_t = simd_op_t<simde_avx512_t,data_t>;
        using simd_dtype_t = decltype(simd_t::set1(0));
        using ufunc_op_t = view::hardshrink_t<lambda_t>;

        const simd_dtype_t zero = simd_t::set1(0);
        const simd_dtype_t pos_lambda;
        const simd_dtype_t neg_lambda;

        ufunc_simd_t(ufunc_op_t op)
            : pos_lambda(simd_t::set1(op.lambda))
            , neg_lambda(simd_t::set1(-op.lambda))
        {};

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t a) const noexcept
        {
            auto zero_mask_l = simd_t::cmpge(a,neg_lambda);
            auto zero_mask_r = simd_t::cmple(a,pos_lambda);
            auto zero_mask = [=](){
                using zero_mask_t = decltype(zero_mask_l);
                if constexpr (meta::is_same_v<zero_mask_t,simde__mmask16>) {
                    return simde_knot_mask16(simde_kxor_mask16(zero_mask_l,zero_mask_r));
                } else if constexpr (meta::is_same_v<zero_mask_t,simde__mmask32>) {
                    return simde_knot_mask32(simde_kxor_mask32(zero_mask_l,zero_mask_r));
                } else if constexpr (meta::is_same_v<zero_mask_t,simde__mmask64>) {
                    return simde_knot_mask64(simde_kxor_mask64(zero_mask_l,zero_mask_r));
                } else if constexpr (meta::is_same_v<zero_mask_t,simde__mmask8>) {
                    return simde_knot_mask8(simde_kxor_mask8(zero_mask_l,zero_mask_r));
                }
            }();
            return simd_t::mask_blend(zero_mask,a,zero);
        }
    }; // ufunc_simd_t

    template <typename data_t>
    struct ufunc_simd_t<view::hardswish_t,simde_avx512_t,data_t> : simd_op_t<simde_avx512_t,data_t>
    {
        using simd_t = simd_op_t<simde_avx512_t,data_t>;
        using simd_dtype_t = decltype(simd_t::set1(0));
        using ufunc_op_t = view::hardswish_t;

        const simd_dtype_t zero  = simd_t::set1(0);
        const simd_dtype_t six   = simd_t::set1(6);
        const simd_dtype_t three = simd_t::set1(3);
        const simd_dtype_t neg_three = simd_t::set1(-3);

        ufunc_simd_t([[maybe_unused]] ufunc_op_t op) {}

        NMTOOLS_ALWAYS_INLINE
        auto eval(simd_dtype_t a) const noexcept
        {
            const auto inter_val = simd_t::div(simd_t::mul(a,simd_t::add(a,three)),six);

            auto mask_r = simd_t::cmplt(a,three);
            auto mask_l = simd_t::cmpge(a,neg_three);
            auto inter_mask = [=](){
                using mask_t = decltype(mask_l);
                if constexpr (meta::is_same_v<mask_t,simde__mmask16>) {
                    return simde_knot_mask16(simde_kxor_mask16(mask_l,mask_r));
                } else if constexpr (meta::is_same_v<mask_t,simde__mmask32>) {
                    return simde_knot_mask32(simde_kxor_mask32(mask_l,mask_r));
                } else if constexpr (meta::is_same_v<mask_t,simde__mmask64>) {
                    return simde_knot_mask64(simde_kxor_mask64(mask_l,mask_r));
                } else if constexpr (meta::is_same_v<mask_t,simde__mmask8>) {
                    return simde_knot_mask8(simde_kxor_mask8(mask_l,mask_r));
                }
            }();
            auto zero_mask = simd_t::cmplt(a,neg_three);
            auto x = simd_t::mask_blend(zero_mask,a,zero);
            return simd_t::mask_blend(inter_mask,x,inter_val);
        }
    };
}

#endif // NMTOOLS_ARRAY_EVAL_SIMD_SIMDE_AVX512_UFUNC_HPP