#ifndef NMTOOLS_TESTS_KERNELS_MINIMUM_HPP
#define NMTOOLS_TESTS_KERNELS_MINIMUM_HPP

#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/profiling.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

using nmtools_tuple;
using nmtools_array;
using namespace nmtools::literals;

template <auto PADDING=0>
struct maximum_kernel_t
{
    template <typename context_t, typename out_t, typename a_t, typename b_t, typename tile_shape_t>
    auto operator()(context_t ctx, out_t& out, const a_t& a, const b_t& b, const tile_shape_t& tile_shape) const
    {
        nmtools_tracy_zone_scoped("maximum kernel");
        constexpr auto padding = nm::ct_v<PADDING>;

        auto [t_id] = tk::worker_id(ctx);
        auto [t_size] = tk::worker_size(ctx);

        auto a_shape = nm::shape(a);
        auto offset  = tk::ndoffset(a_shape,tile_shape,padding);
        auto n_iter  = offset.size() / t_size;
        for (nm_size_t i=0; i<n_iter; i++) {
            auto tile_offset = offset[(t_id*n_iter)+i];
            auto block_a = tk::load(ctx,a,tile_offset,tile_shape,padding);
            auto block_b = tk::load(ctx,b,tile_offset,tile_shape,padding);
            auto result  = block_a.maximum(block_b);

            tk::store(ctx,out,tile_offset,result,padding);
        }
    }
};

inline auto maximum_kernel = maximum_kernel_t<0>{};
inline auto maximum_padding_kernel = maximum_kernel_t<1>{};

#endif // NMTOOLS_TESTS_KERNELS_MINIMUM_HPP