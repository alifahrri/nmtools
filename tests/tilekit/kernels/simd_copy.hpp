#ifndef NMTOOLS_TESTS_KERNELS_SIMD_COPY_HPP
#define NMTOOLS_TESTS_KERNELS_SIMD_COPY_HPP

#include "nmtools/nmtools.hpp"
#include "nmtools/tilekit/vector.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

template <typename out_t, typename array_t>
auto simd_copy_kernel(out_t& out, const array_t& array)
{
    auto tile_shape = tuple{4_ct};
    auto [blk_dim0] = tile_shape;
    auto [inp_dim0] = shape(array);

    auto n_iter = inp_dim0 / blk_dim0;
    for (nm_size_t i=0; i<n_iter; i++) {
        auto offset = tuple{i*blk_dim0};
        auto block  = tk::vector::load(array,offset,tile_shape);

        tk::vector::store(out,offset,block);
    }
}

#endif // NMTOOLS_TESTS_KERNELS_SIMD_COPY_HPP