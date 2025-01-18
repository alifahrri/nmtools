#ifndef NMTOOLS_ARRAY_EVAL_SIMD_VECTOR_EXTENSION_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_VECTOR_EXTENSION_HPP

#include "nmtools/array/evaluator/simd/ufunc.hpp"
#include "nmtools/array/evaluator/simd/evaluator.hpp"
#include "nmtools/array/evaluator/simd/bit_width.hpp"

#include "nmtools/platform/builtin_math.hpp"

namespace nmtools::array::simd
{

    // clang accepts both, but gcc only the latter
    // error: ignoring attributes applied to dependent type ‘dtype_t’ without an associated declaration
    #if 0
    template <auto bit_width, typename dtype_t>
    using vector_type_t = dtype_t __attribute__((vector_size(bit_width / sizeof(dtype_t))));
    #else
    template <auto bit_width, typename dtype_t>
    using vector_type_t __attribute__((vector_size(bit_width / sizeof(dtype_t)))) = dtype_t;
    #endif

    template <auto n_bit>
    struct vector_t
    {
        static constexpr auto bit_width = n_bit;
    };
}

namespace nmtools::meta
{
    template <auto n_bit>
    struct bit_width<array::simd::vector_t<n_bit>>
    {
        static constexpr auto value = n_bit;
    };
}

namespace nmtools::array::simd
{
    using meta::is_same_v;

    // platform agnostic simd op
    template <auto n_bit, typename T>
    struct simd_op_t<vector_t<n_bit>,T,meta::enable_if_t<
        meta::is_floating_point_v<T> || meta::is_integral_v<T>
    >>
    {
        using data_t = T;
        using simd_tag_t = vector_t<n_bit>;

        using vector_type = vector_type_t<n_bit,T>;

        static constexpr inline auto bit_width  = meta::bit_width_v<simd_tag_t>;
        static constexpr inline auto n_elements = bit_width / (sizeof(T) * 8);
        NMTOOLS_ALWAYS_INLINE
        static auto loadu(const data_t* inp_ptr) noexcept
        {
            vector_type res;
            #if 0
            for (auto i=0ul; i<n_elements; i++) {
                res[i] = inp_ptr[i];
            }
            #else
            meta::template_for<n_elements>([&](auto index){
                constexpr auto i = decltype(index)::value;
                res[i] = inp_ptr[i];
            });
            #endif
            return res;
        }

        // NOTE: use packed_t as template parameters instead of member alias
        // to avoid warning: ignoring attributes on template argument ‘__m256’ {aka ‘__vector(8) float’}

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto storeu(data_t* out_ptr, packed_t simd) noexcept
        {
            #if 0
            for (auto i=0ul; i<n_elements; i++) {
                out_ptr[i] = simd[i];
            }
            #else
            meta::template_for<n_elements>([&](auto index){
                constexpr auto i = decltype(index)::value;
                out_ptr[i] = simd[i];
            });
            #endif
        }

        #define NMTOOLS_SIMD_VECTOR_BUILTIN(function,res,x) \
        packed_t res = {}; \
        for (auto i=0ul; i<n_elements; i++) { \
            res[i] = nmtools_builtin_##function(x[i]); \
        }

        #define NMTOOLS_SIMD_VECTOR_BUILTIN_BINARY(function,res,x,y) \
        packed_t res = {}; \
        for (auto i=0ul; i<n_elements; i++) { \
            res[i] = nmtools_builtin_##function(x[i],y[i]); \
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto sqrt(packed_t x) noexcept
        {
            if constexpr (meta::is_same_v<data_t,float>) {
                NMTOOLS_SIMD_VECTOR_BUILTIN(sqrtf,result,x);
                return result;
            } else {
                NMTOOLS_SIMD_VECTOR_BUILTIN(sqrt,result,x);
                return result;
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto floor(packed_t x) noexcept
        {
            if constexpr (meta::is_same_v<data_t,float>) {
                NMTOOLS_SIMD_VECTOR_BUILTIN(floorf,result,x);
                return result;
            } else {
                NMTOOLS_SIMD_VECTOR_BUILTIN(floor,result,x);
                return result;
            }
        }

        template <typename X> NMTOOLS_ALWAYS_INLINE
        static auto set1(X x) noexcept
        {
            vector_type result;
            #if 0
            for (auto i=0ul; i<n_elements; i++) {
                result[i] = x;
            }
            #else
            meta::template_for<n_elements>([&](auto index){
                constexpr auto i = decltype(index)::value;
                result[i] = x;
            });
            #endif
            return result;
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto ceil(packed_t x) noexcept
        {
            if constexpr (meta::is_same_v<data_t,float>) {
                NMTOOLS_SIMD_VECTOR_BUILTIN(ceilf,result,x);
                return result;
            } else {
                NMTOOLS_SIMD_VECTOR_BUILTIN(ceil,result,x);
                return result;
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto max(packed_t x, packed_t y) noexcept
        {
            if constexpr (meta::is_same_v<data_t,float>) {
                NMTOOLS_SIMD_VECTOR_BUILTIN_BINARY(fmaxf,result,x,y);
                return result;
            } else {
                NMTOOLS_SIMD_VECTOR_BUILTIN_BINARY(fmax,result,x,y);
                return result;
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto min(packed_t x, packed_t y) noexcept
        {
            if constexpr (meta::is_same_v<data_t,float>) {
                NMTOOLS_SIMD_VECTOR_BUILTIN_BINARY(fminf,result,x,y);
                return result;
            } else {
                NMTOOLS_SIMD_VECTOR_BUILTIN_BINARY(fmin,result,x,y);
                return result;
            }
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto cmpge(packed_t x, packed_t y) noexcept
        {
            return x >= y;
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto mul(packed_t x, packed_t y) noexcept
        {
            return x * y;
        }

        template <typename packed_t, typename mask_t> NMTOOLS_ALWAYS_INLINE
        static auto blendv(packed_t x, packed_t y, mask_t mask) noexcept
        {
            return (mask ? y : x);
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto add(packed_t x, packed_t y) noexcept
        {
            return x + y;
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto sub(packed_t x, packed_t y) noexcept
        {
            return x - y;
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto cmple(packed_t x, packed_t y) noexcept
        {
            return x <= y;
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto logical_and(packed_t x, packed_t y) noexcept
        {
            return x && y;
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto logical_or(packed_t x, packed_t y) noexcept
        {
            return x || y;
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto div(packed_t x, packed_t y) noexcept
        {
            return x / y;
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto cmplt(packed_t x, packed_t y) noexcept
        {
            return x < y;
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto cmpgt(packed_t x, packed_t y) noexcept
        {
            return x > y;
        }

        template <typename packed_t> NMTOOLS_ALWAYS_INLINE
        static auto fmadd(packed_t a, packed_t b, packed_t c) noexcept
        {
            return (a * b) + c;
        }

        #undef NMTOOLS_SIMD_VECTOR_BUILTIN
        #undef NMTOOLS_SIMD_VECTOR_BUILTIN_BINARY
    };
}

#endif // NMTOOLS_ARRAY_EVAL_SIMD_VECTOR_EXTENSION_HPP