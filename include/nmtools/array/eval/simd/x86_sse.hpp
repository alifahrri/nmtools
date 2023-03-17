#ifndef NMTOOLS_ARRAY_EVAL_SIMD_X86_SSE_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_X86_SSE_HPP

#include "nmtools/array/eval/simd/ufunc.hpp"
#include "nmtools/array/eval/simd/evaluator.hpp"

#include <x86intrin.h>

namespace nmtools::array::simd
{
    // simd_tag_t
    struct x86_sse_t {};

    constexpr inline auto x86_SSE = array::simd_base_t<x86_sse_t>{};

    using meta::is_same_v;

    template <typename T>
    struct simd_op_t<x86_sse_t,T,meta::enable_if_t<meta::is_floating_point_v<T>>>
    {
        using data_t = T;

        static constexpr inline auto bit_width = 128;

        // NOTE: use packed_t as template parameters instead of member alias
        // to avoid warning: ignoring attributes on template argument ‘__m128’ {aka ‘__vector(4) float’}

        NMTOOLS_ALWAYS_INLINE
        static auto loadu(const data_t* inp_ptr) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm_loadu_ps(inp_ptr);
            } else {
                return _mm_loadu_pd(inp_ptr);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto storeu(data_t* out_ptr, packed_t simd) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                _mm_storeu_ps(out_ptr,simd);
            } else {
                _mm_storeu_pd(out_ptr,simd);
            }
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
            if constexpr (is_same_v<data_t,float>) {
                return _mm_set1_ps(x);
            } else {
                return _mm_set1_pd(x);
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
            if constexpr (is_same_v<data_t,float>) {
                return _mm_mul_ps(x,y);
            } else {
                return _mm_mul_pd(x,y);
            }
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
            if constexpr (is_same_v<data_t,float>) {
                return _mm_add_ps(x,y);
            } else {
                return _mm_add_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto sub(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm_sub_ps(x,y);
            } else {
                return _mm_sub_pd(x,y);
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
    }; // simd_op_t<x86_sse_t,float>


} // namespace nmtools::array::simd

#endif // NMTOOLS_ARRAY_EVAL_SIMD_X86_SSE_HPP