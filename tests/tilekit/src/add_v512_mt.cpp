#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/thread_pool.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/add.hpp"

#include <nanobench.h>

namespace nm = nmtools;
using namespace nmtools::literals;

using v512_mt = tk::thread_pool<tk::vector::context_t<512>>;

template <typename shape_m_t, typename shape_n_t>
constexpr auto make_shape(shape_m_t shape_m, shape_n_t shape_n)
{
    if constexpr (nm::is_constant_index_v<shape_m_t>
        || nm::is_constant_index_v<shape_n_t>
    ) {
        return nmtools_tuple{shape_m,shape_n};
    } else {
        return nmtools_array{shape_m,shape_n};
    }
}

#define V512_MT_ADD_CASE_AFFINITY(case_name, M, N, tile_m, tile_n, num_threads, affinity) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto a_shape = make_shape(M,N); \
    auto b_shape = make_shape(M,N); \
\
    auto a = nm::random(a_shape,dtype,gen); \
    auto b = nm::random(b_shape,dtype,gen); \
    auto c = nm::Array::zeros(make_shape(M,N),dtype); \
\
    auto tile_shape = tuple{tile_m,tile_n}; \
    auto ctx = v512_mt(num_threads, affinity); \
    auto worker_size = num_threads; \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape); \
        }); \
\
    auto expected = nm::add(a,b); \
    NMTOOLS_ASSERT_CLOSE( c, expected ); \
}

#define V512_MT_ADD_CASE(case_name, M, N, tile_m, tile_n, num_threads) \
V512_MT_ADD_CASE_AFFINITY(case_name, M, N, tile_m, tile_n, num_threads, true);

V512_MT_ADD_CASE(v512_mt.add.1024_1024.fp32.1x16.2,  1024, 1024, 1_ct, 16_ct, 2)
V512_MT_ADD_CASE(v512_mt.add.1024_1024.fp32.1x16.4,  1024, 1024, 1_ct, 16_ct, 4)
V512_MT_ADD_CASE(v512_mt.add.1024_1024.fp32.1x16.8,  1024, 1024, 1_ct, 16_ct, 8)
V512_MT_ADD_CASE(v512_mt.add.1024_1024.fp32.1x16.16, 1024, 1024, 1_ct, 16_ct, 16)

V512_MT_ADD_CASE(v512_mt.add.1024_1024_ct.fp32.1x16.2,  1024, 1024_ct, 1_ct, 16_ct, 2)
V512_MT_ADD_CASE(v512_mt.add.1024_1024_ct.fp32.1x16.4,  1024, 1024_ct, 1_ct, 16_ct, 4)
V512_MT_ADD_CASE(v512_mt.add.1024_1024_ct.fp32.1x16.8,  1024, 1024_ct, 1_ct, 16_ct, 8)
V512_MT_ADD_CASE(v512_mt.add.1024_1024_ct.fp32.1x16.16, 1024, 1024_ct, 1_ct, 16_ct, 16)

V512_MT_ADD_CASE(v512_mt.add.1024_ct_1024_ct.fp32.1x16.2,  1024_ct, 1024_ct, 1_ct, 16_ct, 2)
V512_MT_ADD_CASE(v512_mt.add.1024_ct_1024_ct.fp32.1x16.4,  1024_ct, 1024_ct, 1_ct, 16_ct, 4)
V512_MT_ADD_CASE(v512_mt.add.1024_ct_1024_ct.fp32.1x16.8,  1024_ct, 1024_ct, 1_ct, 16_ct, 8)
V512_MT_ADD_CASE(v512_mt.add.1024_ct_1024_ct.fp32.1x16.16, 1024_ct, 1024_ct, 1_ct, 16_ct, 16)

V512_MT_ADD_CASE(v512_mt.add.1024_1024.fp32.1x32.2,  1024, 1024, 1_ct, 32_ct, 2)
V512_MT_ADD_CASE(v512_mt.add.1024_1024.fp32.1x32.4,  1024, 1024, 1_ct, 32_ct, 4)
V512_MT_ADD_CASE(v512_mt.add.1024_1024.fp32.1x32.8,  1024, 1024, 1_ct, 32_ct, 8)
V512_MT_ADD_CASE(v512_mt.add.1024_1024.fp32.1x32.16, 1024, 1024, 1_ct, 32_ct, 16)

V512_MT_ADD_CASE(v512_mt.add.1024_1024_ct.fp32.1x32.2,  1024, 1024_ct, 1_ct, 32_ct, 2)
V512_MT_ADD_CASE(v512_mt.add.1024_1024_ct.fp32.1x32.4,  1024, 1024_ct, 1_ct, 32_ct, 4)
V512_MT_ADD_CASE(v512_mt.add.1024_1024_ct.fp32.1x32.8,  1024, 1024_ct, 1_ct, 32_ct, 8)
V512_MT_ADD_CASE(v512_mt.add.1024_1024_ct.fp32.1x32.16, 1024, 1024_ct, 1_ct, 32_ct, 16)

V512_MT_ADD_CASE(v512_mt.add.1024_ct_1024_ct.fp32.1x32.2,  1024_ct, 1024_ct, 1_ct, 32_ct, 2)
V512_MT_ADD_CASE(v512_mt.add.1024_ct_1024_ct.fp32.1x32.4,  1024_ct, 1024_ct, 1_ct, 32_ct, 4)
V512_MT_ADD_CASE(v512_mt.add.1024_ct_1024_ct.fp32.1x32.8,  1024_ct, 1024_ct, 1_ct, 32_ct, 8)
V512_MT_ADD_CASE(v512_mt.add.1024_ct_1024_ct.fp32.1x32.16, 1024_ct, 1024_ct, 1_ct, 32_ct, 16)

V512_MT_ADD_CASE(v512_mt.add.4096_1024.fp32.1x16.2,  4096, 1024, 1_ct, 16_ct, 2)
V512_MT_ADD_CASE(v512_mt.add.4096_1024.fp32.1x16.4,  4096, 1024, 1_ct, 16_ct, 4)
V512_MT_ADD_CASE(v512_mt.add.4096_1024.fp32.1x16.8,  4096, 1024, 1_ct, 16_ct, 8)
V512_MT_ADD_CASE(v512_mt.add.4096_1024.fp32.1x16.16, 4096, 1024, 1_ct, 16_ct, 16)

V512_MT_ADD_CASE(v512_mt.add.4096_1024_ct.fp32.1x16.2,  4096, 1024_ct, 1_ct, 16_ct, 2)
V512_MT_ADD_CASE(v512_mt.add.4096_1024_ct.fp32.1x16.4,  4096, 1024_ct, 1_ct, 16_ct, 4)
V512_MT_ADD_CASE(v512_mt.add.4096_1024_ct.fp32.1x16.8,  4096, 1024_ct, 1_ct, 16_ct, 8)
V512_MT_ADD_CASE(v512_mt.add.4096_1024_ct.fp32.1x16.16, 4096, 1024_ct, 1_ct, 16_ct, 16)

V512_MT_ADD_CASE(v512_mt.add.4096_ct_1024_ct.fp32.1x16.2,  4096_ct, 1024_ct, 1_ct, 16_ct, 2)
V512_MT_ADD_CASE(v512_mt.add.4096_ct_1024_ct.fp32.1x16.4,  4096_ct, 1024_ct, 1_ct, 16_ct, 4)
V512_MT_ADD_CASE(v512_mt.add.4096_ct_1024_ct.fp32.1x16.8,  4096_ct, 1024_ct, 1_ct, 16_ct, 8)
V512_MT_ADD_CASE(v512_mt.add.4096_ct_1024_ct.fp32.1x16.16, 4096_ct, 1024_ct, 1_ct, 16_ct, 16)

V512_MT_ADD_CASE(v512_mt.add.4096_1024.fp32.1x32.2,  4096, 1024, 1_ct, 32_ct, 2)
V512_MT_ADD_CASE(v512_mt.add.4096_1024.fp32.1x32.4,  4096, 1024, 1_ct, 32_ct, 4)
V512_MT_ADD_CASE(v512_mt.add.4096_1024.fp32.1x32.8,  4096, 1024, 1_ct, 32_ct, 8)
V512_MT_ADD_CASE(v512_mt.add.4096_1024.fp32.1x32.16, 4096, 1024, 1_ct, 32_ct, 16)

V512_MT_ADD_CASE(v512_mt.add.4096_1024_ct.fp32.1x32.2,  4096, 1024_ct, 1_ct, 32_ct, 2)
V512_MT_ADD_CASE(v512_mt.add.4096_1024_ct.fp32.1x32.4,  4096, 1024_ct, 1_ct, 32_ct, 4)
V512_MT_ADD_CASE(v512_mt.add.4096_1024_ct.fp32.1x32.8,  4096, 1024_ct, 1_ct, 32_ct, 8)
V512_MT_ADD_CASE(v512_mt.add.4096_1024_ct.fp32.1x32.16, 4096, 1024_ct, 1_ct, 32_ct, 16)

V512_MT_ADD_CASE(v512_mt.add.4096_ct_1024_ct.fp32.1x32.2,  4096_ct, 1024_ct, 1_ct, 32_ct, 2)
V512_MT_ADD_CASE(v512_mt.add.4096_ct_1024_ct.fp32.1x32.4,  4096_ct, 1024_ct, 1_ct, 32_ct, 4)
V512_MT_ADD_CASE(v512_mt.add.4096_ct_1024_ct.fp32.1x32.8,  4096_ct, 1024_ct, 1_ct, 32_ct, 8)
V512_MT_ADD_CASE(v512_mt.add.4096_ct_1024_ct.fp32.1x32.16, 4096_ct, 1024_ct, 1_ct, 32_ct, 16)