#ifndef NMTOOLS_TESTS_KERNELS_VAR_HPP
#define NMTOOLS_TESTS_KERNELS_VAR_HPP

#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/profiling.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

struct var_kernel_t
{
    template <typename ctx_t, typename out_t, typename inp_t, typename tile_shape_t, typename axis_t>
    auto operator()(ctx_t& ctx, out_t& out, const inp_t& inp, const tile_shape_t tile_shape, const axis_t axis) const noexcept
    {
        nmtools_tracy_zone_scoped("var kernel");

        const auto [w_id]   = tk::worker_id(ctx);
        const auto [w_size] = tk::worker_size(ctx);

        auto inp_shape = tk::shape(inp);
        [[maybe_unused]]
        auto out_shape = tk::shape(out);

        // TODO: create convinience function/constructor
        using buffer_t = nmtools_array<float,1>;
        using shape_t  = nmtools_tuple<nm::ct<1>>;
        using f32x1_t  = tk::vector::object_t<buffer_t,shape_t>;

        auto num_elements = f32x1_t{};
        num_elements.data()[0] = nm::at(inp_shape,axis);

        auto inp_nditer = tk::moveaxis(
            tk::nditer(inp_shape,tile_shape)
            , axis
            , nm::ct_v<-1>
        );

        auto axis_0_iter = tk::iter_shape(inp_nditer,0);
        auto axis_1_iter = tk::iter_shape(inp_nditer,1);

        [[maybe_unused]]
        auto out_dtype = nm::type(out);

        auto dtype    = nm::None;
        auto initial  = nm::None;
        auto keepdims = nm::True;

        // for (nm_size_t i=(w_id*w_size); i<(axis_0_iter/w_size); i++) {
        for (nm_size_t i=(w_id); i<(axis_0_iter); i+=w_size) {
            auto tile_offset = tk::packed_at(inp_nditer,i,0);
            auto accumulator = tk::load(ctx,inp,tile_offset,tile_shape);
            for (nm_size_t j=1; j<axis_1_iter; j++) {
                tile_offset = tk::packed_at(inp_nditer,i,j);
                auto block  = tk::load(ctx,inp,tile_offset,tile_shape);
                accumulator = accumulator + block;
            }

            auto tmp0 = accumulator.sum(axis,dtype,initial,keepdims);
            auto mean_axis = (tmp0 / num_elements.broadcast_to(tmp0.shape())).broadcast_to(tile_shape);

            tile_offset = tk::packed_at(inp_nditer,i,0);
            auto tmp1   = tk::load(ctx,inp,tile_offset,tile_shape);
            auto tmp2   = tmp1 - mean_axis;
            auto tmp3   = tmp2 * tmp2;
            auto sum_sq_sub = tmp3.sum(axis);
            for (nm_size_t j=1; j<axis_1_iter; j++) {
                tile_offset = tk::packed_at(inp_nditer,i,j);
                auto tmp1   = tk::load(ctx,inp,tile_offset,tile_shape);
                auto tmp2   = tmp1 - mean_axis;
                auto tmp3   = tmp2 * tmp2;
                sum_sq_sub  = sum_sq_sub + tmp3.sum(axis);
            }

            auto result = sum_sq_sub / num_elements.broadcast_to(sum_sq_sub.shape());
            auto out_tile_shape = nm::shape(result);
            auto out_nditer = tk::nditer(out_shape,out_tile_shape);
            auto res_offset = tk::packed_at(out_nditer,i);
            tk::store(ctx,out,res_offset,result);
        }
    }
};

constexpr inline auto var_kernel = var_kernel_t {};

#endif // NMTOOLS_TESTS_KERNELS_VAR_HPP