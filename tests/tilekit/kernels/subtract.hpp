#ifndef NMTOOLS_TESTS_KERNELS_SUBTRACT_HPP
#define NMTOOLS_TESTS_KERNELS_SUBTRACT_HPP

#include "nmtools/tilekit/tilekit.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

using nmtools_tuple;
using nmtools_array;
using namespace nmtools::literals;

using nmtools::at, nmtools::shape;

template <typename context_t, typename out_t, typename a_t, typename b_t>
auto subtract_kernel(context_t& ctx, out_t& out, const a_t& a, const b_t& b)
{
    auto t_shape = tuple{2_ct,4_ct};
    auto [dim0,dim1] = t_shape;

    auto a_shape = shape(a);
    auto [a_dim0,a_dim1] = a_shape;

    auto b_shape = tuple{a_dim0/dim0,a_dim1/dim1};

    // TODO: tile_id
    [[maybe_unused]]
    auto t_id = tk::worker_id(ctx);

    auto offset = tk::ndoffset(b_shape,t_shape);
    for (nm_size_t i=0; i<offset.size(); i++) {
        auto tile_offset = offset[i];
        auto block_a = tk::load(ctx,a,tile_offset,t_shape);
        auto block_b = tk::load(ctx,b,tile_offset,t_shape);
        auto result  = block_a - block_b;

        tk::store(ctx,out,tile_offset,result);
    }
}

#endif // NMTOOLS_TESTS_KERNELS_SUBTRACT_HPP