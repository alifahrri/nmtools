#ifndef NMTOOLS_ARRAY_EVAL_SIMD_X86_AVX_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_X86_AVX_HPP

#include "nmtools/array/eval/simd/ufunc.hpp"
#include "nmtools/array/eval/simd/evaluator.hpp"

#include <x86intrin.h>

namespace nmtools::array::simd
{
    // simd_tag_t
    struct x86_avx_t {};

    constexpr inline auto x86_AVX = array::simd_base_t<x86_avx_t>{};

    using meta::is_same_v;

    template <typename T>
    struct simd_op_t<x86_avx_t,T,meta::enable_if_t<meta::is_floating_point_v<T>>>
    {
        using data_t = T;

        static constexpr inline auto bit_width = 256;

        // NOTE: use packed_t as template parameters instead of member alias
        // to avoid warning: ignoring attributes on template argument ‘__m256’ {aka ‘__vector(8) float’}

        NMTOOLS_ALWAYS_INLINE
        static auto loadu(const data_t* inp_ptr) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_loadu_ps(inp_ptr);
            } else {
                return _mm256_loadu_pd(inp_ptr);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto storeu(data_t* out_ptr, packed_t simd) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                _mm256_storeu_ps(out_ptr,simd);
            } else {
                _mm256_storeu_pd(out_ptr,simd);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto sqrt(packed_t x) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_sqrt_ps(x);
            } else {
                return _mm256_sqrt_pd(x);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto floor(packed_t x) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_floor_ps(x);
            } else {
                return _mm256_floor_pd(x);
            }
        }

        template <typename X> NMTOOLS_ALWAYS_INLINE
        static auto set1(X x) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_set1_ps(x);
            } else {
                return _mm256_set1_pd(x);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto ceil(packed_t x) noexcept
        {
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
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_mul_ps(x,y);
            } else {
                return _mm256_mul_pd(x,y);
            }
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
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_add_ps(x,y);
            } else {
                return _mm256_add_pd(x,y);
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto sub(packed_t x, packed_t y) noexcept
        {
            if constexpr (is_same_v<data_t,float>) {
                return _mm256_sub_ps(x,y);
            } else {
                return _mm256_sub_pd(x,y);
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
    }; // simd_op_t<x86_avx_t,float>


} // namespace nmtools::array::simd

#endif // NMTOOLS_ARRAY_EVAL_SIMD_X86_AVX_HPP