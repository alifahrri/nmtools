#ifndef NMTOOLS_KERNEL_DIVIDE_HPP
#define NMTOOLS_KERNEL_DIVIDE_HPP

#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/profiling.hpp"

namespace nmtools::kernel
{
    struct divide_t
    {
        template <typename tile_shape_t, typename context_t, typename out_t, typename a_t, typename b_t, typename padding_t=ct<0>>
        auto operator()(context_t ctx, out_t& out, const a_t& a, const b_t& b, const tile_shape_t t_shape, padding_t padding=padding_t{})
        {
            static_assert( is_constant_index_array_v<tile_shape_t> && is_constant_index_v<padding_t>
                , "invalid type for tile shape or padding"
            );
            static_assert( is_ndarray_v<a_t> && is_ndarray_v<b_t>
                , "invalid type for a or b"
            );
            namespace tk = nmtools::tilekit;

            nmtools_tracy_zone_scoped("Divide Kernel");

            auto [t_id]   = tk::worker_id(ctx);
            auto [t_size] = tk::worker_size(ctx);

            // TODO: broadcast
            auto a_shape = shape(a);
            auto offset  = tk::ndoffset(a_shape,t_shape,padding);
            auto n_iter = (offset.size()/t_size);
            for (nm_size_t i=0; i<n_iter; i++) {
                auto tile_offset = offset[(t_id*n_iter)+i];
                auto block_a = tk::load(ctx,a,tile_offset,t_shape,padding);
                auto block_b = tk::load(ctx,b,tile_offset,t_shape,padding);
                auto result  = block_a / block_b;

                tk::store(ctx,out,tile_offset,result,padding);
            }
        }
    };
    inline auto divide = divide_t{};
}

#endif // NMTOOLS_KERNEL_DIVIDE_HPP
