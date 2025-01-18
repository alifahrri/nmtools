#ifndef NMTOOLS_ARRAY_EVAL_SIMD_X86_AVX_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_X86_AVX_HPP

#include "nmtools/evaluator/simd/ufunc.hpp"
#include "nmtools/evaluator/simd/evaluator.hpp"
#include "nmtools/evaluator/simd/bit_width.hpp"

#include <x86intrin.h>

namespace nmtools::array::simd
{
    // simd_tag_t
    struct x86_avx_t {};
}

namespace nmtools::meta
{
    template <>
    struct bit_width<array::simd::x86_avx_t>
    {
        static constexpr auto value = 256;
    };
}

namespace nmtools::array::simd
{
    constexpr inline auto x86_AVX = array::simd_base_t<x86_avx_t>{};

    using meta::is_same_v;

    template <typename T>
    struct simd_op_t<x86_avx_t,T,meta::enable_if_t<
        meta::is_floating_point_v<T> || meta::is_integral_v<T>
    >>
    {
        using data_t = T;

        static constexpr inline auto bit_width = meta::bit_width_v<x86_avx_t>;

        NMTOOLS_ALWAYS_INLINE
        static auto loadu(const data_t* inp_ptr) noexcept
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(data_t) * 8;
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_loadu_ps(inp_ptr);
            } else if constexpr (is_same_v<data_t,double>) {
                return _mm256_loadu_pd(inp_ptr);
            } else if constexpr (meta::is_integral_v<data_t>) {
                return _mm256_loadu_si256((__m256i*)inp_ptr);
            }
            static_assert(
                meta::is_floating_point_v<data_t>
                || (n_bit == 64)
                || (n_bit == 32)
                || (n_bit == 16)
                || (n_bit == 8)
                , "unsupported: is not floating point or unsupported bit width"
            );
        }

        // NOTE: use packed_t as template parameters instead of member alias
        // to avoid warning: ignoring attributes on template argument ‘__m256’ {aka ‘__vector(8) float’}

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto storeu(data_t* out_ptr, packed_t simd) noexcept
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(data_t) * 8;
            if constexpr (is_same_v<data_t,float>) {
                _mm256_storeu_ps(out_ptr,simd);
            } else if constexpr (is_same_v<data_t,double>) {
                _mm256_storeu_pd(out_ptr,simd);
            } else if constexpr (meta::is_integral_v<data_t>) {
                _mm256_storeu_si256((__m256i*)out_ptr,simd);
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
                return _mm256_sqrt_ps(x);
            } else {
                return _mm256_sqrt_pd(x);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto floor(packed_t x) noexcept
        {
            // TODO: restrict to floating point only (no integer)
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_floor_ps(x);
            } else {
                return _mm256_floor_pd(x);
            }
        }

        template <typename X> NMTOOLS_ALWAYS_INLINE
        static auto set1(X x) noexcept
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(X) * 8;
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_set1_ps(x);
            } else if constexpr (is_same_v<data_t,double>) {
                return _mm256_set1_pd(x);
            } else if constexpr (n_bit == 8) {
                return _mm256_set1_epi8(x);
            } else if constexpr (n_bit == 16) {
                return _mm256_set1_epi16(x);
            } else if constexpr (n_bit == 32) {
                return _mm256_set1_epi32(x);
            } else if constexpr (n_bit == 64) {
                return _mm256_set1_epi64x(x);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto ceil(packed_t x) noexcept
        {
            // TODO: restrict to floating point only (no integer)
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_ceil_ps(x);
            } else {
                return _mm256_ceil_pd(x);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto max(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_max_ps(x,y);
            } else {
                return _mm256_max_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto min(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_min_ps(x,y);
            } else {
                return _mm256_min_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto cmpge(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_cmp_ps(x,y,_CMP_GE_OS);
            } else {
                return _mm256_cmp_pd(x,y,_CMP_GE_OS);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto mul(packed_t x, packed_t y) noexcept
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(data_t) * 8;
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_mul_ps(x,y);
            } else if constexpr (is_same_v<data_t,double>) {
                return _mm256_mul_pd(x,y);
            } else if constexpr (n_bit == 16) {
                return _mm256_mullo_epi16(x,y);
            } else if constexpr (n_bit == 32) {
                return _mm256_mullo_epi32(x,y);
            }
            // TODO: support 8-bit, 64-bit mul
        }

        template <typename packed_t, typename mask_t> NMTOOLS_ALWAYS_INLINE
        static auto blendv(packed_t x, packed_t y, mask_t z) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_blendv_ps(x,y,z);
            } else {
                return _mm256_blendv_pd(x,y,z);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto add(packed_t x, packed_t y) noexcept
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(data_t) * 8;
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_add_ps(x,y);
            } else if constexpr (is_same_v<data_t,double>) {
                return _mm256_add_pd(x,y);
            } else if constexpr (n_bit == 8) {
                return _mm256_add_epi8(x,y);
            } else if constexpr (n_bit == 16) {
                return _mm256_add_epi16(x,y);
            } else if constexpr (n_bit == 32) {
                return _mm256_add_epi32(x,y);
            } else if constexpr (n_bit == 64) {
                return _mm256_add_epi64(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto sub(packed_t x, packed_t y) noexcept
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(data_t) * 8;
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_sub_ps(x,y);
            } else if constexpr (is_same_v<data_t,double>) {
                return _mm256_sub_pd(x,y);
            } else if constexpr (n_bit == 8) {
                return _mm256_sub_epi8(x,y);
            } else if constexpr (n_bit == 16) {
                return _mm256_sub_epi16(x,y);
            } else if constexpr (n_bit == 32) {
                return _mm256_sub_epi32(x,y);
            } else if constexpr (n_bit == 64) {
                return _mm256_sub_epi64(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto cmple(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_cmp_ps(x,y,_CMP_LE_OS);
            } else {
                return _mm256_cmp_pd(x,y,_CMP_LE_OS);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto logical_and(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_and_ps(x,y);
            } else {
                return _mm256_and_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto logical_or(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_or_ps(x,y);
            } else {
                return _mm256_or_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto div(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_div_ps(x,y);
            } else {
                return _mm256_div_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto cmplt(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_cmp_ps(x,y,_CMP_LT_OS);
            } else {
                return _mm256_cmp_pd(x,y,_CMP_LT_OS);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto cmpgt(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_cmp_ps(x,y,_CMP_GT_OS);
            } else {
                return _mm256_cmp_pd(x,y,_CMP_GT_OS);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto fmadd(packed_t a, packed_t b, packed_t c) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_fmadd_ps(a,b,c);
            } else {
                return _mm256_fmadd_pd(a,b,c);
            }
        }
    }; // simd_op_t<x86_avx_t,float>


} // namespace nmtools::array::simd

#endif // NMTOOLS_ARRAY_EVAL_SIMD_X86_AVX_HPP