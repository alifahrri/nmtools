#ifndef NMTOOLS_ARRAY_EVAL_SIMD_X86_SSE_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_X86_SSE_HPP

#include "nmtools/evaluator/simd/ufunc.hpp"
#include "nmtools/evaluator/simd/evaluator.hpp"
#include "nmtools/evaluator/simd/bit_width.hpp"

#include <xmmintrin.h>
#include <emmintrin.h>
#include <tmmintrin.h>
#include <smmintrin.h>

namespace nmtools::array::simd
{
    // simd_tag_t
    struct x86_sse_t {};
} // namespace nmtools::array::simd

namespace nmtools::meta
{
    template <>
    struct bit_width<array::simd::x86_sse_t>
    {
        static constexpr auto value = 128;
    };
}

namespace nmtools::array::simd
{
    constexpr inline auto x86_SSE = array::simd_base_t<x86_sse_t>{};

    using meta::is_same_v;

    template <typename T>
    struct simd_op_t<x86_sse_t,T,meta::enable_if_t<
        meta::is_floating_point_v<T> || meta::is_integral_v<T>
    >>
    {
        using data_t = T;

        static constexpr inline auto bit_width = meta::bit_width_v<x86_sse_t>;

        // NOTE: use packed_t as template parameters instead of member alias
        // to avoid warning: ignoring attributes on template argument ‘__m128’ {aka ‘__vector(4) float’}

        NMTOOLS_ALWAYS_INLINE
        static auto loadu(const data_t* inp_ptr) noexcept
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(data_t) * 8;
            if constexpr (is_same_v<data_t,float>) {
                return _mm_loadu_ps(inp_ptr);
            } else if constexpr (is_same_v<data_t,double>) {
                return _mm_loadu_pd(inp_ptr);
            } else if constexpr (meta::is_integral_v<data_t>) {
                return _mm_loadu_si128((__m128i*)inp_ptr);
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

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto storeu(data_t* out_ptr, packed_t simd) noexcept
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(data_t) * 8;
            if constexpr (is_same_v<data_t,float>) {
                _mm_storeu_ps(out_ptr,simd);
            } else if constexpr (is_same_v<data_t,double>) {
                _mm_storeu_pd(out_ptr,simd);
            } else if constexpr (meta::is_integral_v<data_t>) {
                _mm_storeu_si128((__m128i*)out_ptr,simd);
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
            if constexpr (is_same_v<data_t,float>) {
                return _mm_sqrt_ps(x);
            } else {
                return _mm_sqrt_pd(x);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto ceil(packed_t x) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm_ceil_ps(x);
            } else {
                return _mm_ceil_pd(x);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto floor(packed_t x) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm_floor_ps(x);
            } else {
                return _mm_floor_pd(x);
            }
        }

        template <typename X> NMTOOLS_ALWAYS_INLINE
        static auto set1(X x) noexcept
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(data_t) * 8;
            if constexpr (is_same_v<data_t,float>) {
                return _mm_set1_ps(x);
            } else if constexpr (is_same_v<data_t,double>) {
                return _mm_set1_pd(x);
            } else if constexpr (n_bit == 8) {
                return _mm_set1_epi8(x);
            } else if constexpr (n_bit == 16) {
                return _mm_set1_epi16(x);
            } else if constexpr (n_bit == 32) {
                return _mm_set1_epi32(x);
            } else if constexpr (n_bit == 64) {
                return _mm_set1_epi64x(x);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto max(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm_max_ps(x,y);
            } else {
                return _mm_max_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto min(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm_min_ps(x,y);
            } else {
                return _mm_min_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto cmpge(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm_cmpge_ps(x,y);
            } else {
                return _mm_cmpge_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto mul(packed_t x, packed_t y) noexcept
        {
            // NOTE: for integers, use mullo
            // Multiply the packed 32-bit integers in a and b, producing intermediate 64-bit integers,
            // and store the low 32 bits of the intermediate integers in dst.
            // with the assumption that overflow is rare
            // TODO: handle overflow
            [[maybe_unused]] constexpr auto n_bit = sizeof(data_t) * 8;
            if constexpr (is_same_v<data_t,float>) {
                return _mm_mul_ps(x,y);
            } else if constexpr (is_same_v<data_t,double>) {
                return _mm_mul_pd(x,y);
            // 8-bit multiplication not supported yet
            // There is no such _mm_mullo_epi8
            // TODO: support 8-bit mul
            #if 0
            } else if constexpr (n_bit == 8) {
                return _mm_mullo_epi8(x,y);
            #endif
            } else if constexpr (n_bit == 16) {
                return _mm_mullo_epi16(x,y);
            } else if constexpr (n_bit == 32) {
                return _mm_mullo_epi32(x,y);
            }
            // 64-bit multiplication not supported yet
            // There is no such _mm_mullo_epi64 in sse, only avx512
            // TODO: support 64-bit mul
            #if 0
            else if constexpr (n_bit == 64) {
                return _mm_mullo_epi64(x,y);
            }
            #endif
        }

        template <typename packed_t, typename mask_t> NMTOOLS_ALWAYS_INLINE
        static auto blendv(packed_t x, packed_t y, mask_t z) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm_blendv_ps(x,y,z);
            } else {
                return _mm_blendv_pd(x,y,z);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto add(packed_t x, packed_t y) noexcept
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(data_t) * 8;
            if constexpr (is_same_v<data_t,float>) {
                return _mm_add_ps(x,y);
            } else if constexpr (is_same_v<data_t,double>) {
                return _mm_add_pd(x,y);
            } else if constexpr (n_bit == 8) {
                return _mm_add_epi8(x,y);
            } else if constexpr (n_bit == 16) {
                return _mm_add_epi16(x,y);
            } else if constexpr (n_bit == 32) {
                return _mm_add_epi32(x,y);
            } else if constexpr (n_bit == 64) {
                return _mm_add_epi64(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto sub(packed_t x, packed_t y) noexcept
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(data_t) * 8;
            if constexpr (is_same_v<data_t,float>) {
                return _mm_sub_ps(x,y);
            } else if constexpr (is_same_v<data_t,double>) {
                return _mm_sub_pd(x,y);
            } else if constexpr (n_bit == 8) {
                return _mm_sub_epi8(x,y);
            } else if constexpr (n_bit == 16) {
                return _mm_sub_epi16(x,y);
            } else if constexpr (n_bit == 32) {
                return _mm_sub_epi32(x,y);
            } else if constexpr (n_bit == 64) {
                return _mm_sub_epi64(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto cmple(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm_cmple_ps(x,y);
            } else {
                return _mm_cmple_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto logical_and(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm_and_ps(x,y);
            } else {
                return _mm_and_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto logical_or(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm_or_ps(x,y);
            } else {
                return _mm_or_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto div(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm_div_ps(x,y);
            } else {
                return _mm_div_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto cmplt(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm_cmplt_ps(x,y);
            } else {
                return _mm_cmplt_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto cmpgt(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm_cmpgt_ps(x,y);
            } else {
                return _mm_cmpgt_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto fmadd(packed_t a, packed_t b, packed_t c)
        {
            auto tmp = mul(a,b);
            return add(tmp,c);
        }

        template <auto POS, typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto insert(packed_t a, data_t data, meta::as_type<POS>)
        {
            [[maybe_unused]] constexpr auto n_bit = sizeof(data_t) * 8;
            constexpr auto is_integral = meta::is_integral_v<data_t>;
            if constexpr (is_integral && (n_bit == 8)) {
                return _mm_insert_epi8(a,data,POS);
            } else if constexpr (is_integral && (n_bit == 16)) {
                return _mm_insert_epi16(a,data,POS);
            } else if constexpr (is_integral && (n_bit == 32)) {
                return _mm_insert_epi32(a,data,POS);
            } else if constexpr (is_integral && (n_bit == 64)) {
                return _mm_insert_epi64(a,data,POS);
            } else /*if constexpr (is_same_v<data_t,float>)*/ {
                return _mm_insert_ps(a,set1(data),POS);
            }
        }
    }; // simd_op_t<x86_sse_t,float>


} // namespace nmtools::array::simd

#endif // NMTOOLS_ARRAY_EVAL_SIMD_X86_SSE_HPP