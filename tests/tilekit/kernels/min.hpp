#ifndef NMTOOLS_TESTS_TILEKIT_KERNELS_MIN_HPP
#define NMTOOLS_TESTS_TILEKIT_KERNELS_MIN_HPP

#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/profiling.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

using nmtools_tuple;

struct min_kernel_t
{
    template <typename ctx_t, typename out_t, typename inp_t, typename tile_shape_t, typename axis_t>
    auto operator()(ctx_t& ctx, out_t& out, const inp_t& inp, const tile_shape_t tile_shape, axis_t axis) const noexcept
    {
        nmtools_tracy_zone_scoped("min kernel");

        [[maybe_unused]] auto [w_id]   = tk::worker_id(ctx);
        [[maybe_unused]] auto [w_size] = tk::worker_size(ctx);

        auto inp_shape = tk::shape(inp);
        auto out_shape = tk::shape(out);

        auto inp_nditer = tk::moveaxis(
            tk::nditer(inp_shape,tile_shape)
            , axis
            , nm::ct_v<-1>
        );

        auto axis_0_iter = tk::iter_shape(inp_nditer,0);
        auto axis_1_iter = tk::iter_shape(inp_nditer,1);

        // auto dtype = nm::type(out);

        for (nm_size_t i=0; i<axis_0_iter; i++) {
            auto tile_offset = tk::packed_at(inp_nditer,i,0);
            auto accumulator = tk::load(ctx,inp,tile_offset,tile_shape);
            for (nm_size_t j=1; j<axis_1_iter; j++) {
                tile_offset = tk::packed_at(inp_nditer,i,j);
                auto block  = tk::load(ctx,inp,tile_offset,tile_shape);
                accumulator = accumulator.minimum(block);
            }

            auto result = accumulator.min(axis);
            auto out_tile_shape = tk::shape(result);
            auto out_nditer = tk::nditer(out_shape,out_tile_shape);
            auto res_offset = tk::packed_at(out_nditer,i);
            tk::store(ctx,out,res_offset,result);
        }
    }
};

constexpr inline auto min_kernel = min_kernel_t {};

#endif // NMTOOLS_TESTS_TILEKIT_KERNELS_MIN_HPP