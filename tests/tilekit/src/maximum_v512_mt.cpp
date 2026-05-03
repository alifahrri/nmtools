#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/thread_pool.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/maximum.hpp"

#include <nanobench.h>

namespace nm = nmtools;
using namespace nmtools::literals;

using ctx_t = tk::thread_pool<tk::vector::context_t<512>>;

template <typename shape_0_t, typename...shape_n_t>
constexpr auto make_shape(shape_0_t shape_0, shape_n_t...shape_n)
{
    if constexpr (nm::is_constant_index_v<shape_0_t>
        || (nm::is_constant_index_v<shape_n_t> || ...)
    ) {
        return nmtools_tuple{shape_0,shape_n...};
    } else {
        return nmtools_array{shape_0,shape_n...};
    }
}

#define V512_MT_MAXIMUM_CASE(case_name, shape, tile_shape, num_threads) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto a = nm::random(shape,dtype,gen); \
    auto b = nm::random(shape,dtype,gen); \
    auto c = nm::Array::zeros(shape,dtype); \
\
    auto ctx = ctx_t(num_threads); \
    auto worker_size = num_threads; \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            ctx.eval(worker_size,maximum_kernel,c,a,b,tile_shape); \
        }); \
\
    auto expected = nm::maximum(a,b); \
    NMTOOLS_ASSERT_CLOSE( c, expected ); \
}

// V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_4.fp32.2x16, (make_shape(4,4)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_8.fp32.2x16, (make_shape(4,8)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_16.fp32.2x16, (make_shape(4,16)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_32.fp32.2x16, (make_shape(4,32)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_64.fp32.2x16, (make_shape(4,64)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_128.fp32.2x16, (make_shape(4,128)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_256.fp32.2x16, (make_shape(4,256)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_512.fp32.2x16, (make_shape(4,512)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_1024.fp32.2x16, (make_shape(4,1024)), (tuple{2_ct,16_ct}), 1)

V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_4.fp32.2x16, (make_shape(4,4)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.8_8.fp32.2x16, (make_shape(8,8)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.16_16.fp32.2x16, (make_shape(16,16)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.32_32.fp32.2x16, (make_shape(32,32)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.64_64.fp32.2x16, (make_shape(64,64)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.128_128.fp32.2x16, (make_shape(128,128)), (tuple{2_ct,16_ct}), 2)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.256_256.fp32.2x16, (make_shape(256,256)), (tuple{2_ct,16_ct}), 2)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.512_512.fp32.2x16, (make_shape(512,512)), (tuple{2_ct,16_ct}), 2)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_1024.fp32.2x16, (make_shape(1024,1024)), (tuple{2_ct,16_ct}), 2)

V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_4.fp32.2x16, (make_shape(1024,4)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_8.fp32.2x16, (make_shape(1024,8)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_16.fp32.2x16, (make_shape(1024,16)), (tuple{2_ct,16_ct}), 2)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_32.fp32.2x16, (make_shape(1024,32)), (tuple{2_ct,16_ct}), 2)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_64.fp32.2x16, (make_shape(1024,64)), (tuple{2_ct,16_ct}), 2)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_128.fp32.2x16, (make_shape(1024,128)), (tuple{2_ct,16_ct}), 2)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_256.fp32.2x16, (make_shape(1024,256)), (tuple{2_ct,16_ct}), 2)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_512.fp32.2x16, (make_shape(1024,512)), (tuple{2_ct,16_ct}), 2)
// V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_1024.fp32.2x16, (make_shape(1024,1024)), (tuple{2_ct,16_ct}), 2)

// V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_4.fp32.2x16, (make_shape(4,4)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_ct_8_ct.fp32.2x16, (make_shape(4_ct,8_ct)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_ct_16_ct.fp32.2x16, (make_shape(4_ct,16_ct)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_ct_32_ct.fp32.2x16, (make_shape(4_ct,32_ct)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_ct_64_ct.fp32.2x16, (make_shape(4_ct,64_ct)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_ct_128_ct.fp32.2x16, (make_shape(4_ct,128_ct)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_ct_256_ct.fp32.2x16, (make_shape(4_ct,256_ct)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_ct_512_ct.fp32.2x16, (make_shape(4_ct,512_ct)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_ct_1024_ct.fp32.2x16, (make_shape(4_ct,1024_ct)), (tuple{2_ct,16_ct}), 1)

V512_MT_MAXIMUM_CASE(v512_mt.maximum.4_ct_4_ct.fp32.2x16, (make_shape(4_ct,4_ct)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.8_ct_8_ct.fp32.2x16, (make_shape(8_ct,8_ct)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.16_ct_16_ct.fp32.2x16, (make_shape(16_ct,16_ct)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.32_ct_32_ct.fp32.2x16, (make_shape(32_ct,32_ct)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.64_ct_64_ct.fp32.2x16, (make_shape(64_ct,64_ct)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.128_ct_128_ct.fp32.2x16, (make_shape(128_ct,128_ct)), (tuple{2_ct,16_ct}), 2)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.256_ct_256_ct.fp32.2x16, (make_shape(256_ct,256_ct)), (tuple{2_ct,16_ct}), 2)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.512_ct_512_ct.fp32.2x16, (make_shape(512_ct,512_ct)), (tuple{2_ct,16_ct}), 2)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_ct_1024_ct.fp32.2x16, (make_shape(1024_ct,1024_ct)), (tuple{2_ct,16_ct}), 2)

V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_ct_4_ct.fp32.2x16, (make_shape(1024_ct,4_ct)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_ct_8_ct.fp32.2x16, (make_shape(1024_ct,8_ct)), (tuple{2_ct,16_ct}), 1)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_ct_16_ct.fp32.2x16, (make_shape(1024_ct,16_ct)), (tuple{2_ct,16_ct}), 2)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_ct_32_ct.fp32.2x16, (make_shape(1024_ct,32_ct)), (tuple{2_ct,16_ct}), 2)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_ct_64_ct.fp32.2x16, (make_shape(1024_ct,64_ct)), (tuple{2_ct,16_ct}), 2)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_ct_128_ct.fp32.2x16, (make_shape(1024_ct,128_ct)), (tuple{2_ct,16_ct}), 2)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_ct_256_ct.fp32.2x16, (make_shape(1024_ct,256_ct)), (tuple{2_ct,16_ct}), 2)
V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_ct_512_ct.fp32.2x16, (make_shape(1024_ct,512_ct)), (tuple{2_ct,16_ct}), 2)
// V512_MT_MAXIMUM_CASE(v512_mt.maximum.1024_ct_1024_ct.fp32.2x16, (make_shape(1024_ct,1024_ct)), (tuple{2_ct,16_ct}), 2)
