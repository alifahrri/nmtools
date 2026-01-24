#ifndef NMTOOLS_TESTS_KERNELS_SUBTRACT_HPP
#define NMTOOLS_TESTS_KERNELS_SUBTRACT_HPP

#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/profiling.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

using nmtools_tuple;
using nmtools_array;
using namespace nmtools::literals;

using nmtools::at, nmtools::shape;

struct subtract_kernel_t
{
    template <typename tile_shape_t=tuple<nm::ct<2>,nm::ct<4>>, typename context_t, typename out_t, typename a_t, typename b_t>
    auto operator()(context_t ctx, out_t& out, const a_t& a, const b_t& b, const tile_shape_t t_shape=tile_shape_t{})
    {
        nmtools_tracy_zone_scoped("Subtract Kernel");

        auto [t_id] = tk::worker_id(ctx);
        auto [t_size] = tk::worker_size(ctx);

        auto a_shape = shape(a);
        auto offset  = tk::ndoffset(a_shape,t_shape);
        auto n_iter = (offset.size()/t_size);
        for (nm_size_t i=0; i<n_iter; i++) {
            auto tile_offset = offset[(t_id*n_iter)+i];
            auto block_a = tk::load(ctx,a,tile_offset,t_shape);
            auto block_b = tk::load(ctx,b,tile_offset,t_shape);
            auto result  = block_a - block_b;

            tk::store(ctx,out,tile_offset,result);
        }
    }
};
inline auto subtract_kernel = subtract_kernel_t{};

#endif // NMTOOLS_TESTS_KERNELS_SUBTRACT_HPP