#ifndef NMTOOLS_ARRAY_EVAL_SIMD_VECTOR_128_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_VECTOR_128_HPP

#include "nmtools/evaluator/simd/vector_extension.hpp"

namespace nmtools::simd
{
    using vector_128_t = vector_t<128>;

    constexpr inline auto vector_128 = simd_base_t<vector_128_t>{};
}

#endif // NMTOOLS_ARRAY_EVAL_SIMD_VECTOR_128_HPP