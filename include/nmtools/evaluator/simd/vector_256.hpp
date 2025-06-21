#ifndef NMTOOLS_ARRAY_EVAL_SIMD_VECTOR_256_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_VECTOR_256_HPP

#include "nmtools/evaluator/simd/vector_extension.hpp"

namespace nmtools::simd
{
    using vector_256_t = vector_t<256>;

    constexpr inline auto vector_256 = simd_base_t<vector_256_t>{};
}

#endif // NMTOOLS_ARRAY_EVAL_SIMD_VECTOR_256_HPP