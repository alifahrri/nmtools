#ifndef NMTOOLS_TESTS_KERNELS_VECTOR_DIVIDE_HPP
#define NMTOOLS_TESTS_KERNELS_VECTOR_DIVIDE_HPP

#include "nmtools/tilekit/tilekit.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;

using nmtools_tuple;
using nmtools_array;
using namespace nmtools::literals;

using nmtools::at, nmtools::shape;

template <typename context_t, typename out_t, typename a_t, typename b_t>
auto vector_divide(context_t&& ctx, out_t& out, const a_t& a, const b_t& b)
{
    auto t_shape  = tuple{4_ct};
    auto [dim0]   = t_shape;
    auto a_shape  = shape(a);
    auto [a_dim0] = a_shape;
    auto n_iter   = a_dim0 / dim0;

    for (nm_size_t i=0; i<n_iter; i++) {
        auto offset  = tuple{i};
        auto block_a = tk::load(ctx,a,offset,t_shape);
        auto block_b = tk::load(ctx,b,offset,t_shape);
        auto result  = block_a / block_b;

        tk::store(ctx,out,offset,result);
    }
}

#endif // NMTOOLS_TESTS_KERNELS_VECTOR_DIVIDE_HPP