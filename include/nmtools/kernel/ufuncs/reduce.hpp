#ifndef NMTOOLS_KERNEL_UFUNCS_REDUCE_HPP
#define NMTOOLS_KERNEL_UFUNCS_REDUCE_HPP

#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/profiling.hpp"

namespace nmtools::kernel
{
    template <typename op_t>
    struct reduce_t
    {
        template <typename ctx_t, typename out_t, typename inp_t, typename tile_shape_t, typename axis_t=ct<-1>>
        auto operator()(ctx_t& ctx, out_t& out, const inp_t& inp, const tile_shape_t tile_shape, axis_t axis=axis_t{}) const noexcept
        {
            // assume 2d, non-2d maybe reshaped by runtime/caller

            namespace tk = nmtools::tilekit;

            nmtools_tracy_zone_scoped("reduce kernel");

            [[maybe_unused]] auto [w_id]   = tk::worker_id(ctx);
            [[maybe_unused]] auto [w_size] = tk::worker_size(ctx);

            auto inp_shape = tk::shape(inp);
            auto out_shape = tk::shape(out);

            auto inp_nditer = tk::moveaxis(
                tk::nditer(inp_shape,tile_shape)
                , axis
                , ct_v<-1>
            );

            auto axis_0_iter = tk::iter_shape(inp_nditer,0);
            auto axis_1_iter = tk::iter_shape(inp_nditer,1);

            auto dtype = type(out);
            using dtype_t = type_t<decltype(dtype)>;

            const auto op = op_t{};
            constexpr auto identity = op_t::template identity<dtype_t>();

            static_assert( has_identity_v<op_t,dtype_t>
                , "expect op_t to have identity" );

            for (nm_size_t i=0; i<axis_0_iter; i++) {
                auto accumulator = Array::full(tile_shape,identity,ctx);
                // TODO: handle composition of axes
                for (nm_size_t j=0; j<axis_1_iter; j++) {
                    auto tile_offset = tk::packed_at(inp_nditer,i,j);
                    auto block  = tk::load(ctx,inp,tile_offset,tile_shape);
                    accumulator = accumulator.ufunc(op,block);
                }

                auto result = accumulator.reduce(op,axis);
                auto out_tile_shape = shape(result);
                auto out_nditer = tk::nditer(out_shape,out_tile_shape);
                auto res_offset = tk::packed_at(out_nditer,i);
                tk::store(ctx,out,res_offset,result);
            }
        }
    };
}

#endif // NMTOOLS_KERNEL_UFUNCS_REDUCE_HPP