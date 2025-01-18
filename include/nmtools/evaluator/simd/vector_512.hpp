#ifndef NMTOOLS_ARRAY_EVAL_SIMD_VECTOR_512_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_VECTOR_512_HPP

#include "nmtools/evaluator/simd/vector_extension.hpp"

namespace nmtools::array::simd
{
    using vector_512_t = vector_t<512>;

    constexpr inline auto vector_512 = array::simd_base_t<vector_512_t>{};
}

#endif // NMTOOLS_ARRAY_EVAL_SIMD_VECTOR_512_HPP