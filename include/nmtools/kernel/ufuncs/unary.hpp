#ifndef NMTOOLS_TESTS_KERNELS_COS_HPP
#define NMTOOLS_TESTS_KERNELS_COS_HPP

#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/profiling.hpp"

namespace nmtools::kernel
{
    template <typename op_t>
    struct unary_t
    {
        template <typename tile_shape_t, typename context_t, typename out_t, typename inp_t>
        auto operator()(context_t ctx, out_t& out, const inp_t& inp, const tile_shape_t tile_shape) const
        {
            namespace tk = nmtools::tilekit;
            nmtools_tracy_zone_scoped("exp kernel");

            auto [w_id]   = tk::worker_id(ctx);
            auto [w_size] = tk::worker_size(ctx);

            auto inp_shape  = shape(inp);
            // assume out shape = inp shape
            auto offset = tk::ndoffset(inp_shape,tile_shape);
            auto n_iter = (offset.size()/w_size);

            const auto op = op_t{};

            n_iter = (n_iter ? n_iter : 1);
            for (nm_size_t i=0; i<n_iter; i++) {
                auto tile_offset = offset[(w_id*n_iter)+i];
                auto block  = tk::load(ctx,inp,tile_offset,tile_shape);
                auto result = block.ufunc(op);

                tk::store(ctx,out,tile_offset,result);
            }
        }
    };
}

#endif // NMTOOLS_TESTS_KERNELS_COS_HPP