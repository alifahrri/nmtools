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
    template <typename ctx_t, typename out_t, typename inp_t, typename tile_shape_t>
    auto operator()(ctx_t& ctx, out_t& out, const inp_t& inp, const tile_shape_t tile_shape) const noexcept
    {
        // assume 2d
        // assume summing over -1 axis
        // assume out is properly shaped

        nmtools_tracy_zone_scoped("sum kernel");

        auto axis = nm::ct_v<-1>;

        [[maybe_unused]] auto [w_id]   = tk::worker_id(ctx);
        [[maybe_unused]] auto [w_size] = tk::worker_size(ctx);

        auto inp_shape = tk::shape(inp);
        auto out_shape = tk::shape(out);

        auto axis_iter = inp_shape / tile_shape;

        const auto [axis_0_iter,axis_1_iter] = axis_iter;

        // TODO: slice
        auto offset = tk::ndoffset(inp_shape,tile_shape);

        auto dtype = nm::type(out);
        auto acc_shape = tile_shape.remove_dims(axis);

        auto v = nm::view::zeros(acc_shape,dtype);
        static_assert( nm::is_index_array_v<decltype(acc_shape)> );
        static_assert( nm::is_view_v<decltype(v)> );
        static_assert( !nm::is_void_v<nm::resolve_optype_t<nm::object_eval_resolver_t<>,decltype(v),nm::none_t>> );

        for (nm_size_t j=0; j<axis_0_iter; j++) {
            auto accumulator = nm::Array::zeros(tile_shape,dtype,ctx);
            // TODO: handle composition of axes
            for (nm_size_t i=0; i<axis_1_iter; i++) {
                auto tile_offset = offset[(j*axis_1_iter)+i];
                auto block  = tk::load(ctx,inp,tile_offset,tile_shape);
                accumulator = accumulator + block;
            }

            // TODO: support runtime single axis
            auto result = accumulator.sum(axis);
            static_assert( nm::is_ndarray_v<decltype(result)> );
            auto out_tile_shape = nm::shape(result);
            auto out_offset = tk::ndoffset(out_shape,out_tile_shape);
            auto res_offset = out_offset[j];
            tk::store(ctx,out,res_offset,result);
        }
    }
};

constexpr inline auto sum_kernel = sum_kernel_t {};

#endif // NMTOOLS_TESTS_TILEKIT_KERNELS_SUM_HPP