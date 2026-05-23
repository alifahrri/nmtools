#ifndef NMTOOLS_TESTS_KERNELS_LAYER_NORM_HPP
#define NMTOOLS_TESTS_KERNELS_LAYER_NORM_HPP

#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/profiling.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

struct layer_norm_kernel_t
{
    template <typename ctx_t, typename out_t, typename inp_t, typename weight_t, typename bias_t, typename tile_shape_t, typename weight_tile_t, typename bias_tile_t, typename axis_t>
    auto operator()(ctx_t& ctx, out_t& out, const inp_t& inp, const weight_t& weight, const bias_t& bias, const tile_shape_t tile_shape, const weight_tile_t weight_tile, const bias_tile_t bias_tile, const axis_t axis) const noexcept
    {
        nmtools_tracy_zone_scoped("layer_norm kernel");

        const auto [w_id]   = tk::worker_id(ctx);
        const auto [w_size] = tk::worker_size(ctx);

        auto inp_shape = tk::shape(inp);
        [[maybe_unused]]
        auto out_shape = tk::shape(out);
        auto weight_shape = tk::shape(weight);
        auto bias_shape   = tk::shape(bias);

        // TODO: create convinience function/constructor
        using buffer_t = nmtools_array<float,1>;
        using shape_t  = nmtools_tuple<nm::ct<1>>;
        using f32x1_t  = tk::vector::object_t<buffer_t,shape_t>;

        auto num_elements = f32x1_t{};
        num_elements.data()[0] = nm::at(inp_shape,axis);

        auto epsilon = f32x1_t{};
        epsilon.data()[0] = 1e-5;

        auto inp_nditer = tk::moveaxis(
            tk::nditer(inp_shape,tile_shape)
            , axis
            , nm::ct_v<-1>
        );
        auto weight_nditer = tk::moveaxis(
            tk::nditer(weight_shape,weight_tile)
            , axis
            , nm::ct_v<-1>
        );
        auto bias_nditer = tk::moveaxis(
            tk::nditer(bias_shape,bias_tile)
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

        for (nm_size_t i=(w_id); i<(axis_0_iter); i+=w_size) {
            // mean
            auto mean_acc = nm::Array::zeros(tile_shape,out_dtype,ctx);
            for (nm_size_t j=0; j<axis_1_iter; j++) {
                auto tile_offset = tk::packed_at(inp_nditer,i,j);
                auto input = tk::load(ctx,inp,tile_offset,tile_shape);
                mean_acc = mean_acc + input;
            }
            auto sum0 = mean_acc.sum(axis,dtype,initial,keepdims);
            auto mean = (sum0 / num_elements.broadcast_to(sum0.shape())).broadcast_to(tile_shape);

            // var
            auto var_acc = nm::Array::zeros(tile_shape,out_dtype,ctx);
            for (nm_size_t j=0; j<axis_1_iter; j++) {
                auto tile_offset = tk::packed_at(inp_nditer,i,j);
                auto input = tk::load(ctx,inp,tile_offset,tile_shape);
                var_acc = var_acc + (input - mean).square();
            }
            // std
            auto sum1 = var_acc.sum(axis,dtype,initial,keepdims);
            auto var  = sum1 / num_elements.broadcast_to(sum1.shape());
            auto std  = (var + epsilon.broadcast_to(var.shape())).sqrt().broadcast_to(tile_shape);

            // shift + norm + multiply + add
            for (nm_size_t j=0; j<axis_1_iter; j++) {
                auto tile_offset = tk::packed_at(inp_nditer,i,j);
                auto input = tk::load(ctx,inp,tile_offset,tile_shape);
                // shift, norm
                auto shift = input - mean;
                auto norm  = shift / std;
                // TODO: deduce weight & bias tile from inp tile shape
                auto weight_offset = tk::packed_at(weight_nditer,j);
                auto bias_offset   = tk::packed_at(bias_nditer,j);
                auto W = tk::load(ctx,weight,weight_offset,weight_tile);
                auto b = tk::load(ctx,bias,bias_offset,bias_tile);
                
                auto result = (norm * W.broadcast_to(tile_shape)) + b.broadcast_to(tile_shape);
                tk::store(ctx,out,tile_offset,result);
            }
        }
    }
};

constexpr inline auto layer_norm_kernel = layer_norm_kernel_t{};

#endif // NMTOOLS_TESTS_KERNELS_LAYER_NORM_HPP