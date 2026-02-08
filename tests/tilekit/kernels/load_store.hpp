#ifndef NMTOOLS_TESTS_KERNELS_LOAD_STORE_HPP
#define NMTOOLS_TESTS_KERNELS_LOAD_STORE_HPP

#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/profiling.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

using nmtools_tuple;
using nmtools_array;
using namespace nmtools::literals;

using nmtools::at, nmtools::shape;

struct load_store_t
{
    template <typename tile_shape_t, typename context_t, typename out_t, typename inp_t>
    auto operator()(context_t ctx, out_t& out, const inp_t& inp, const tile_shape_t tile_shape)
    {
        nmtools_tracy_zone_scoped("Load Store");

        auto [t_id]   = tk::worker_id(ctx);
        auto [t_size] = tk::worker_size(ctx);

        auto inp_shape = shape(inp);
        auto offset    = tk::ndoffset(inp_shape,tile_shape);
        auto n_iter    = offset.size() / t_size;
        for (nm_size_t i=0; i<n_iter; i++) {
            auto tile_offset = offset[t_id*n_iter+i];
            auto block = tk::load(ctx,inp,tile_offset,tile_shape);

            tk::store(ctx,out,tile_offset,block);
        }
    }
};
inline auto load_store_kernel = load_store_t{};

#endif // NMTOOLS_TESTS_KERNELS_LOAD_STORE_HPP