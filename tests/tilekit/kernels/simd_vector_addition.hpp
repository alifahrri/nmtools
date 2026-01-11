#ifndef NMTOOLS_TESTS_KERNELS_SIMD_ADDITION_HPP
#define NMTOOLS_TESTS_KERNELS_SIMD_ADDITION_HPP

#include "nmtools/tilekit/vector.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

using nmtools_tuple;
using namespace nmtools::literals;

using nmtools::shape;

template <typename out_t, typename a_t, typename b_t>
auto simd_vector_addition(out_t& out, const a_t& a, const b_t& b)
{
    auto tile_shape = tuple{4_ct};
    auto [dim0]     = tile_shape;
    auto [a_dim0]   = shape(a);
    auto n_iter     = a_dim0 / dim0;

    for (nm_size_t i=0; i<n_iter; i++) {
        auto offset  = tuple{i*dim0};
        auto block_a = tk::vector::load(a,offset,tile_shape);
        auto block_b = tk::vector::load(b,offset,tile_shape);
        auto result  = block_a + block_b;

        tk::vector::store(out,offset,result);
    }
}

#endif // NMTOOLS_TESTS_KERNELS_SIMD_ADDITION_HPP