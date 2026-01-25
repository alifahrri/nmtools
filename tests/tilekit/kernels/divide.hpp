#ifndef NMTOOLS_TESTS_KERNELS_DIVIDE_HPP
#define NMTOOLS_TESTS_KERNELS_DIVIDE_HPP

#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/profiling.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

using nmtools_tuple;
using nmtools_array;
using namespace nmtools::literals;

using nmtools::at, nmtools::shape;

template <auto PADDING=0>
struct divide_kernel_t
{
    template <typename tile_shape_t=tuple<nm::ct<2>,nm::ct<4>>, typename context_t, typename out_t, typename a_t, typename b_t>
    auto operator()(context_t ctx, out_t& out, const a_t& a, const b_t& b, const tile_shape_t t_shape=tile_shape_t{})
    {
        nmtools_tracy_zone_scoped("Divide Kernel");
        constexpr auto padding = nm::ct_v<PADDING>;

        auto [t_id] = tk::worker_id(ctx);
        auto [t_size] = tk::worker_size(ctx);

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
inline auto divide_kernel = divide_kernel_t<0>{};
inline auto divide_padding_kernel = divide_kernel_t<1>{};

#endif // NMTOOLS_TESTS_KERNELS_DIVIDE_HPP