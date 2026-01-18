#ifndef NMTOOLS_TESTS_KERNELS_ADD_HPP
#define NMTOOLS_TESTS_KERNELS_ADD_HPP

#include "nmtools/tilekit/tilekit.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

using nmtools_tuple;
using nmtools_array;
using namespace nmtools::literals;

using nmtools::at, nmtools::shape;

template <typename tile_shape_t=tuple<nm::ct<2>,nm::ct<4>>, typename context_t, typename out_t, typename a_t, typename b_t>
auto add_kernel(context_t& ctx, out_t& out, const a_t& a, const b_t& b, const tile_shape_t t_shape=tile_shape_t{})
{
    // TODO: tile_id
    [[maybe_unused]]
    auto t_id = tk::tile_id(ctx);

    auto a_shape = shape(a);
    auto offset  = tk::ndoffset(a_shape,t_shape);
    for (nm_size_t i=0; i<offset.size(); i++) {
        auto tile_offset = offset[i];
        auto block_a = tk::load(ctx,a,tile_offset,t_shape);
        auto block_b = tk::load(ctx,b,tile_offset,t_shape);
        auto result  = block_a + block_b;

        tk::store(ctx,out,tile_offset,result);
    }
}

#endif // NMTOOLS_TESTS_KERNELS_ADD_HPP