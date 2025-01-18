#ifndef NMTOOLS_ARRAY_EVAL_SIMD_SIMDE_AVX512_SIMD_OP_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_SIMDE_AVX512_SIMD_OP_HPP

#include "nmtools/array/evaluator/simd/ufunc.hpp"
#include "nmtools/array/evaluator/simd/evaluator.hpp"
#include "nmtools/array/evaluator/simd/bit_width.hpp"

#include <simde/x86/avx512.h>

namespace nmtools::array::simd
{
    struct simde_avx512_t {};
}

namespace nmtools::meta
{
    template <>
    struct bit_width<array::simd::simde_avx512_t>
    {
        static constexpr auto value = 512;
    };
}

namespace nmtools::array::simd
{
    constexpr inline auto simde_AVX512 = array::simd_base_t<simde_avx512_t>{};

    using meta::is_same_v;

    template <typename T>
    struct simd_op_t<simde_avx512_t,T,meta::enable_if_t<
        meta::is_floating_point_v<T> || meta::is_integral_v<T>
    >>
    {
        using data_t = T;

        static constexpr inline auto bit_width = meta::bit_width_v<simde_avx512_t>;

        NMTOOLS_ALWAYS_INLINE
        static auto loadu(const data_t* inp_ptr) noexcept
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(data_t) * 8;
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_loadu_ps(inp_ptr);
            } else if constexpr (is_same_v<data_t,double>) {
                return simde_mm512_loadu_pd(inp_ptr);
            } else if constexpr (meta::is_integral_v<data_t>) {
                return simde_mm512_loadu_si512(inp_ptr);
            }
            static_assert( 
                meta::is_floating_point_v<data_t>
                || (n_bit == 64)
                || (n_bit == 32)
                || (n_bit == 16)
                || (n_bit == 8)
                , "expected data_t is not floating point or unsupported bit width"
            );
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto storeu(data_t* out_ptr, packed_t simd) noexcept
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(data_t) * 8;
            if constexpr (is_same_v<data_t,float>) {
                simde_mm512_storeu_ps(out_ptr,simd);
            } else if constexpr (is_same_v<data_t,double>) {
                simde_mm512_storeu_pd(out_ptr,simd);
            } else if constexpr (meta::is_integral_v<data_t>) {
                simde_mm512_storeu_si512(out_ptr,simd);
            }
            static_assert( 
                meta::is_floating_point_v<data_t>
                || (n_bit == 64)
                || (n_bit == 32)
                || (n_bit == 16)
                || (n_bit == 8)
                , "expected data_t is not floating point or unsupported bit width"
            );
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto sqrt(packed_t x) noexcept
        {
            // TODO: restrict to floating point only (no integer)
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_sqrt_ps(x);
            } else {
                return simde_mm512_sqrt_pd(x);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto floor(packed_t x) noexcept
        {
            // TODO: restrict to floating point only (no integer)
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_floor_ps(x);
            } else {
                return simde_mm512_floor_pd(x);
            }
        }

        template <typename X> NMTOOLS_ALWAYS_INLINE
        static auto set1(X x) noexcept
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(X) * 8;
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_set1_ps(x);
            } else if constexpr (is_same_v<data_t,double>) {
                return simde_mm512_set1_pd(x);
            } else if constexpr (n_bit == 8) {
                return simde_mm512_set1_epi8(x);
            } else if constexpr (n_bit == 16) {
                return simde_mm512_set1_epi16(x);
            } else if constexpr (n_bit == 32) {
                return simde_mm512_set1_epi32(x);
            } else if constexpr (n_bit == 64) {
                return simde_mm512_set1_epi64(x);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto ceil(packed_t x) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_ceil_ps(x);
            } else {
                return simde_mm512_ceil_pd(x);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto max(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_max_ps(x,y);
            } else {
                return simde_mm512_max_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto min(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_min_ps(x,y);
            } else {
                return simde_mm512_min_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto cmpge(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_cmp_ps_mask(x,y,SIMDE_CMP_GE_OS);
            } else {
                return simde_mm512_cmp_pd_mask(x,y,SIMDE_CMP_GE_OS);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto mul(packed_t x, packed_t y) noexcept
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(data_t) * 8;
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_mul_ps(x,y);
            } else if constexpr (is_same_v<data_t,double>) {
                return simde_mm512_mul_pd(x,y);
            } else if constexpr (n_bit == 16) {
                return simde_mm512_mullo_epi16(x,y);
            } else if constexpr (n_bit == 32) {
                return simde_mm512_mullo_epi32(x,y);
            } else if constexpr (n_bit == 64) {
                return simde_mm512_mullo_epi64(x,y);
            }
            // TODO: support 8-bit
        }

        template <typename packed_t, typename mask_t> NMTOOLS_ALWAYS_INLINE
        static auto blendv(packed_t x, packed_t y, mask_t z) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_mask_blend_ps(z,x,y);
            } else {
                return simde_mm512_mask_blend_pd(z,x,y);
            }
        }

        template <typename packed_t, typename mask_t> NMTOOLS_ALWAYS_INLINE
        static auto mask_blend(mask_t mask, packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_mask_blend_ps(mask,x,y);
            } else {
                return simde_mm512_mask_blend_pd(mask,x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto add(packed_t x, packed_t y) noexcept
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(data_t) * 8;
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_add_ps(x,y);
            } else if constexpr (is_same_v<data_t,double>) {
                return simde_mm512_add_pd(x,y);
            } else if constexpr (n_bit == 8) {
                return simde_mm512_add_epi8(x,y);
            } else if constexpr (n_bit == 16) {
                return simde_mm512_add_epi16(x,y);
            } else if constexpr (n_bit == 32) {
                return simde_mm512_add_epi32(x,y);
            } else if constexpr (n_bit == 64) {
                return simde_mm512_add_epi64(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto sub(packed_t x, packed_t y) noexcept
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(data_t) * 8;
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_sub_ps(x,y);
            } else if constexpr (is_same_v<data_t,double>) {
                return simde_mm512_sub_pd(x,y);
            } else if constexpr (n_bit == 8) {
                return simde_mm512_sub_epi8(x,y);
            } else if constexpr (n_bit == 16) {
                return simde_mm512_sub_epi16(x,y);
            } else if constexpr (n_bit == 32) {
                return simde_mm512_sub_epi32(x,y);
            } else if constexpr (n_bit == 64) {
                return simde_mm512_sub_epi64(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto cmple(packed_t x, packed_t y) noexcept
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(data_t) * 8;
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_cmp_ps_mask(x,y,SIMDE_CMP_LE_OS);
            } else {
                return simde_mm512_cmp_pd_mask(x,y,SIMDE_CMP_LE_OS);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto logical_and(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_and_ps(x,y);
            } else {
                return simde_mm512_and_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto logical_or(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_or_ps(x,y);
            } else {
                return simde_mm512_or_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto div(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_div_ps(x,y);
            } else {
                return simde_mm512_div_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto cmplt(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_cmp_ps_mask(x,y,SIMDE_CMP_LT_OS);
            } else {
                return simde_mm512_cmp_pd_mask(x,y,SIMDE_CMP_LT_OS);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto cmpgt(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_cmp_ps_mask(x,y,SIMDE_CMP_GT_OS);
            } else {
                return simde_mm512_cmp_pd_mask(x,y,SIMDE_CMP_GT_OS);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto fmadd(packed_t a, packed_t b, packed_t c) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return simde_mm512_fmadd_ps(a,b,c);
            } else {
                return simde_mm512_fmadd_ps(a,b,c);
            }
        }
    };
}

#endif // NMTOOLS_ARRAY_EVAL_SIMD_SIMDE_AVX512_SIMD_OP_HPP