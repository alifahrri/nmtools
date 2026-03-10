#ifndef NMTOOLS_TESTS_KERNELS_LOG_HPP
#define NMTOOLS_TESTS_KERNELS_LOG_HPP

#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/profiling.hpp"
#include "nmtools/core/math.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;
namespace ops = nmtools::ops;

using nmtools_tuple;
using nmtools_array;
using namespace nmtools::literals;

using nmtools::at, nmtools::shape;

template <bool use_utl=false>
struct log_kernel_t
{
    template <typename tile_shape_t, typename context_t, typename out_t, typename inp_t>
    auto operator()(context_t ctx, out_t& out, const inp_t& inp, const tile_shape_t tile_shape) const
    {
        nmtools_tracy_zone_scoped("log kernel");

        auto [w_id]   = tk::worker_id(ctx);
        auto [w_size] = tk::worker_size(ctx);

        auto inp_shape  = shape(inp);
        // assume out shape = inp shape
        auto offset = tk::ndoffset(inp_shape,tile_shape);
        auto n_iter = (offset.size()/w_size);

        n_iter = (n_iter ? n_iter : 1);
        for (nm_size_t i=0; i<n_iter; i++) {
            auto tile_offset = offset[(w_id*n_iter)+i];
            auto block = tk::load(ctx,inp,tile_offset,tile_shape);
            auto result = [&](){
                if constexpr (use_utl) {
                    return block.ufunc(ops::utl::log);
                } else {
                    return block.log();
                }
            }();

            tk::store(ctx,out,tile_offset,result);
        }
    }
};

constexpr inline auto log_kernel = log_kernel_t{};
constexpr inline auto log_utl_kernel = log_kernel_t<true>{};

#endif // NMTOOLS_TESTS_KERNELS_LOG_HPP