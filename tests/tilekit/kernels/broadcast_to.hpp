#ifndef NMTOOLS_TESTS_KERNELS_BROADCAST_TO_HPP
#define NMTOOLS_TESTS_KERNELS_BROADCAST_TO_HPP

#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/profiling.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

using nmtools_array, nmtools_tuple;
using namespace nmtools::literals;

using nmtools::at, nmtools::shape;

struct broadcast_to_kernel_t
{
    template <typename context_t, typename out_t, typename inp_t, typename dst_tile_t, typename src_tile_t>
    auto operator()(context_t ctx, out_t& out, const inp_t& inp, const dst_tile_t dst_tile, const src_tile_t src_tile) const
    {
        nmtools_tracy_zone_scoped("broadcast_to kernel");

        auto [w_id]   = tk::worker_id(ctx);
        auto [w_size] = tk::worker_size(ctx);

        auto inp_shape  = shape(inp);
        auto out_shape  = shape(out);
        auto inp_offset = tk::ndoffset(inp_shape,src_tile);
        auto out_offset = tk::ndoffset(out_shape,dst_tile);
        auto n_iter = (inp_offset.size()/w_size);

        auto num_repeat = out_offset.size() / inp_offset.size();

        for (nm_size_t i=0; i<n_iter; i++) {
            auto inp_t_offset = inp_offset[(w_id*n_iter)+i];

            auto block  = tk::load(ctx,inp,inp_t_offset,src_tile);
            auto result = block.broadcast_to(dst_tile);

            for (nm_size_t j=0; j<num_repeat; j++) {
                auto out_t_offset = out_offset[(w_id*n_iter)+i+(j*inp_offset.size())];
                tk::store(ctx,out,out_t_offset,result);
            }
        }
    };
};

constexpr inline auto broadcast_to_kernel = broadcast_to_kernel_t{};

#endif // NMTOOLS_TESTS_KERNELS_BROADCAST_TO_HPP