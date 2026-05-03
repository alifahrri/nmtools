#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/tilekit/scalar.hpp"
#include "nmtools/profiling.hpp"

#include <nanobench.h>

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

using namespace nm::literals;

struct softmax_kernel_t
{
    template <typename ctx_t, typename out_t, typename inp_t, typename tile_shape_t>
    auto operator()(ctx_t& ctx, out_t& out, const inp_t& inp, const tile_shape_t tile_shape) const noexcept
    {
        nmtools_tracy_zone_scoped("softmax kernel");

        const auto [w_id]   = tk::worker_id(ctx);
        const auto [w_size] = tk::worker_size(ctx);

        // softmax has same inp & out shape
        auto inp_shape = tk::shape(inp);
        [[maybe_unused]]
        auto out_shape = tk::shape(out);

        auto axis = nm::ct_v<-1>;
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

        for (nm_size_t i=(w_id*w_size); i<(axis_0_iter/w_size); i++) {
            auto tile_offset = tk::packed_at(inp_nditer,i,0);
            auto accumulator = tk::load(ctx,inp,tile_offset,tile_shape);
            for (nm_size_t j=1; j<axis_1_iter; j++) {
                tile_offset = tk::packed_at(inp_nditer,i,j);
                auto block  = tk::load(ctx,inp,tile_offset,tile_shape);
                accumulator = accumulator.maximum(block);
            }
            auto max = accumulator.max(axis,dtype,initial,keepdims).broadcast_to(tile_shape);

            // placeholder for sum of exp
            tile_offset  = tk::packed_at(inp_nditer,i,0);
            auto block0  = tk::load(ctx,inp,tile_offset,tile_shape);
            auto result0 = (block0 - max).exp();
            auto exp_acc = result0;
            tk::store(ctx,out,tile_offset,result0);

            // exp(x - x_max)
            for (nm_size_t j=1; j<axis_1_iter; j++) {
                tile_offset = tk::packed_at(inp_nditer,i,j);
                auto block  = tk::load(ctx,inp,tile_offset,tile_shape);
                auto result = (block - max).exp();
                exp_acc = exp_acc + result;
                tk::store(ctx,out,tile_offset,result);
            }
            auto exp_sum = exp_acc.sum(axis,dtype,initial,keepdims).broadcast_to(tile_shape);

            // exp / exp_sum
            tile_offset  = tk::packed_at(inp_nditer,i,0);
            auto block1  = tk::load(ctx,out,tile_offset,tile_shape);
            auto result1 = block1 / exp_sum;
            tk::store(ctx,out,tile_offset,result1);
            for (nm_size_t j=1; j<axis_1_iter; j++) {
                tile_offset = tk::packed_at(inp_nditer,i,j);
                auto block  = tk::load(ctx,out,tile_offset,tile_shape);
                auto result = block / exp_sum;
                tk::store(ctx,out,tile_offset,result);
            }
        }
    }
};

constexpr inline auto softmax_kernel = softmax_kernel_t {};

using scalar_st = tk::scalar_t;

int main(int argc, char**argv)
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    auto shape = nmtools_array{4,1024};

    auto inp = nm::random(shape,dtype,gen);
    auto out = nm::Array::zeros(shape,dtype);

    auto ctx = scalar_st();

    auto min_time = std::chrono::nanoseconds(50'000'000);
    {
        auto tile_shape = nmtools_tuple{2_ct,4_ct};
        ankerl::nanobench::Bench()
            .minEpochTime(min_time)
            .run("softmax.4x1024.2x4",[&](){
                softmax_kernel(ctx,out,inp,tile_shape);
            });
    }
    {
        auto tile_shape = nmtools_tuple{2_ct,8_ct};
        ankerl::nanobench::Bench()
            .minEpochTime(min_time)
            .run("softmax.4x1024.2x8",[&](){
                softmax_kernel(ctx,out,inp,tile_shape);
            });
    }
    {
        auto tile_shape = nmtools_tuple{2_ct,16_ct};
        ankerl::nanobench::Bench()
            .minEpochTime(min_time)
            .run("softmax.4x1024.2x16",[&](){
                softmax_kernel(ctx,out,inp,tile_shape);
            });
    }
    {
        auto tile_shape = nmtools_tuple{1_ct,8_ct};
        ankerl::nanobench::Bench()
            .minEpochTime(min_time)
            .run("softmax.4x1024.1x8",[&](){
                softmax_kernel(ctx,out,inp,tile_shape);
            });
    }
    {
        auto tile_shape = nmtools_tuple{1_ct,16_ct};
        ankerl::nanobench::Bench()
            .minEpochTime(min_time)
            .run("softmax.4x1024.1x16",[&](){
                softmax_kernel(ctx,out,inp,tile_shape);
            });
    }
    {
        auto tile_shape = nmtools_tuple{1_ct,32_ct};
        ankerl::nanobench::Bench()
            .minEpochTime(min_time)
            .run("softmax.4x1024.1x32",[&](){
                softmax_kernel(ctx,out,inp,tile_shape);
            });
    }
    return 0;
}