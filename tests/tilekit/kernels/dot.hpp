#ifndef TESTS_TILEKIT_KERNEL_DOT_HPP
#define TESTS_TILEKIT_KERNEL_DOT_HPP

#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/profiling.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

using namespace nmtools::literals;

// mat vec multiply
struct dot_kernel_t
{
    template <typename ctx_t, typename out_t, typename lhs_t, typename rhs_t, typename tile_shape_t>
    auto operator()(ctx_t& ctx, out_t& out, const lhs_t& lhs, const rhs_t& rhs, const tile_shape_t tile_shape) const noexcept
    {
        // assume 2d
        // assume properly shaped

        nmtools_tracy_zone_scoped("dot kernel");

        [[maybe_unused]] auto [w_id]   = tk::worker_id(ctx);
        [[maybe_unused]] auto [w_size] = tk::worker_size(ctx);

        auto lhs_shape = tk::shape(lhs);
        auto rhs_shape = tk::shape(rhs);
        auto out_shape = tk::shape(out);

        auto rhs_tshape = nmtools_tuple{nm::at(tile_shape,nm::ct_v<-1>)};
        auto out_tshape = nmtools_tuple{nm::at(tile_shape,nm::ct_v<0>)};

        auto lhs_nditer = tk::nditer(lhs_shape,tile_shape);
        auto rhs_nditer = tk::nditer(rhs_shape,rhs_tshape);
        auto out_nditer = tk::nditer(out_shape,out_tshape);

        auto axis = nm::ct_v<-1>;

        // vertical axis
        auto axis_0_iter = tk::iter_shape(lhs_nditer,0_ct);
        auto axis_1_iter = tk::iter_shape(lhs_nditer,1_ct);

        auto out_dtype = nm::type(out);
        
        // TODO: try to unroll the vertical work axis, probably useful for gcc

        for (nm_size_t i=(w_id); i<(axis_0_iter); i+=w_size) {
            auto acc = nm::Array::zeros(tile_shape,out_dtype,ctx);
            for (nm_size_t j=0; j<axis_1_iter; j++) {
                auto lhs_offset = tk::packed_at(lhs_nditer,i,j);
                auto rhs_offset = tk::packed_at(rhs_nditer,j);

                auto lhs_tile = tk::load(ctx,lhs,lhs_offset,tile_shape);
                auto rhs_tile = tk::load(ctx,rhs,rhs_offset,rhs_tshape).broadcast_to(tile_shape);

                acc = acc + (lhs_tile * rhs_tile);
            }
            auto result = acc.sum(axis);

            auto res_offset = tk::packed_at(out_nditer,i);
            tk::store(ctx,out,res_offset,result);
        }
    }
};

constexpr inline auto dot_kernel = dot_kernel_t {};

#endif // TESTS_TILEKIT_KERNEL_DOT_HPP