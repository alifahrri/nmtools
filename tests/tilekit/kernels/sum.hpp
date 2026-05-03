#ifndef NMTOOLS_TESTS_TILEKIT_KERNELS_SUM_HPP
#define NMTOOLS_TESTS_TILEKIT_KERNELS_SUM_HPP

#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/profiling.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;
namespace ix = nmtools::index;

using nmtools_tuple;

struct sum_kernel_t
{
    template <typename ctx_t, typename out_t, typename inp_t, typename tile_shape_t, typename axis_t=nm::ct<-1>>
    auto operator()(ctx_t& ctx, out_t& out, const inp_t& inp, const tile_shape_t tile_shape, axis_t axis=axis_t{}) const noexcept
    {
        // assume 2d
        // assume out is properly shaped

        nmtools_tracy_zone_scoped("sum kernel");

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

        auto dtype = nm::type(out);

        for (nm_size_t i=0; i<axis_0_iter; i++) {
            auto accumulator = nm::Array::zeros(tile_shape,dtype,ctx);
            // TODO: handle composition of axes
            for (nm_size_t j=0; j<axis_1_iter; j++) {
                auto tile_offset = tk::packed_at(inp_nditer,i,j);
                auto block  = tk::load(ctx,inp,tile_offset,tile_shape);
                accumulator = accumulator + block;
            }

            auto result = accumulator.sum(axis);
            auto out_tile_shape = nm::shape(result);
            auto out_nditer = tk::nditer(out_shape,out_tile_shape);
            auto res_offset = tk::packed_at(out_nditer,i);
            tk::store(ctx,out,res_offset,result);
        }
    }
};

constexpr inline auto sum_kernel = sum_kernel_t {};

#endif // NMTOOLS_TESTS_TILEKIT_KERNELS_SUM_HPP