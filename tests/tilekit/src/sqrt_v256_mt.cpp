#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/thread_pool.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/array/ufuncs/sqrt.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/sqrt.hpp"

#include <nanobench.h>

#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION (1e-3)

namespace nm = nmtools;
using namespace nmtools::literals;

using ctx_t = tk::thread_pool<tk::vector::context_t<256>>;

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

#define V256_MT_SQRT_CASE(case_name, shape, tile_shape, num_threads) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto inp = nm::random(shape,dtype,gen); \
    auto out = nm::Array::zeros(shape,dtype); \
\
    auto ctx = ctx_t(num_threads); \
    auto worker_size = num_threads; \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            ctx.eval(worker_size,sqrt_kernel,out,inp,tile_shape); \
        }); \
\
    auto expected = nm::sqrt(inp); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

#define V256_MT_SQRT_UTL_CASE(case_name, shape, tile_shape, num_threads) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto inp = nm::random(shape,dtype,gen); \
    auto out = nm::Array::zeros(shape,dtype); \
\
    auto ctx = ctx_t(num_threads); \
    auto worker_size = num_threads; \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            ctx.eval(worker_size,sqrt_utl_kernel,out,inp,tile_shape); \
        }); \
\
    auto expected = nm::sqrt(inp); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

V256_MT_SQRT_CASE(v256_mt.sqrt.8.fp32.4.2,  make_shape(8), tuple{8_ct}, 2 );
V256_MT_SQRT_CASE(v256_mt.sqrt.8.fp32.4.4,  make_shape(8), tuple{8_ct}, 4 );
V256_MT_SQRT_CASE(v256_mt.sqrt.8.fp32.4.8,  make_shape(8), tuple{8_ct}, 8 );
V256_MT_SQRT_CASE(v256_mt.sqrt.8.fp32.4.16,  make_shape(8), tuple{8_ct}, 16 );

V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.8.fp32.4.2,  make_shape(8), tuple{8_ct}, 2 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.8.fp32.4.4,  make_shape(8), tuple{8_ct}, 4 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.8.fp32.4.8,  make_shape(8), tuple{8_ct}, 8 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.8.fp32.4.16,  make_shape(8), tuple{8_ct}, 16 );

V256_MT_SQRT_CASE(v256_mt.sqrt.64.fp32.4.2,  make_shape(64), tuple{8_ct}, 2 );
V256_MT_SQRT_CASE(v256_mt.sqrt.64.fp32.4.4,  make_shape(64), tuple{8_ct}, 4 );
V256_MT_SQRT_CASE(v256_mt.sqrt.64.fp32.4.8,  make_shape(64), tuple{8_ct}, 8 );
V256_MT_SQRT_CASE(v256_mt.sqrt.64.fp32.4.16,  make_shape(64), tuple{8_ct}, 16 );

V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.64.fp32.4.2,  make_shape(64), tuple{8_ct}, 2 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.64.fp32.4.4,  make_shape(64), tuple{8_ct}, 4 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.64.fp32.4.8,  make_shape(64), tuple{8_ct}, 8 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.64.fp32.4.16,  make_shape(64), tuple{8_ct}, 16 );

V256_MT_SQRT_CASE(v256_mt.sqrt.1024.fp32.4.2,  make_shape(1024), tuple{8_ct}, 2 );
V256_MT_SQRT_CASE(v256_mt.sqrt.1024.fp32.4.4,  make_shape(1024), tuple{8_ct}, 4 );
V256_MT_SQRT_CASE(v256_mt.sqrt.1024.fp32.4.8,  make_shape(1024), tuple{8_ct}, 8 );
V256_MT_SQRT_CASE(v256_mt.sqrt.1024.fp32.4.16,  make_shape(1024), tuple{8_ct}, 16 );

V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.1024.fp32.4.2,  make_shape(1024), tuple{8_ct}, 2 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.1024.fp32.4.4,  make_shape(1024), tuple{8_ct}, 4 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.1024.fp32.4.8,  make_shape(1024), tuple{8_ct}, 8 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.1024.fp32.4.16,  make_shape(1024), tuple{8_ct}, 16 );

V256_MT_SQRT_CASE(v256_mt.sqrt.4_256.fp32.2x4.2,  (make_shape(4,256)), (tuple{2_ct,8_ct}), 2 );
V256_MT_SQRT_CASE(v256_mt.sqrt.4_256.fp32.2x4.4,  (make_shape(4,256)), (tuple{2_ct,8_ct}), 4 );
V256_MT_SQRT_CASE(v256_mt.sqrt.4_256.fp32.2x4.8,  (make_shape(4,256)), (tuple{2_ct,8_ct}), 8 );
V256_MT_SQRT_CASE(v256_mt.sqrt.4_256.fp32.2x4.16,  (make_shape(4,256)), (tuple{2_ct,8_ct}), 16 );

V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.4_256.fp32.2x4.2,  (make_shape(4,256)), (tuple{2_ct,8_ct}), 2 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.4_256.fp32.2x4.4,  (make_shape(4,256)), (tuple{2_ct,8_ct}), 4 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.4_256.fp32.2x4.8,  (make_shape(4,256)), (tuple{2_ct,8_ct}), 8 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.4_256.fp32.2x4.16,  (make_shape(4,256)), (tuple{2_ct,8_ct}), 16 );

V256_MT_SQRT_CASE(v256_mt.sqrt.16_1024.fp32.2x4.2,  (make_shape(16,1024)), (tuple{2_ct,8_ct}), 2 );
V256_MT_SQRT_CASE(v256_mt.sqrt.16_1024.fp32.2x4.4,  (make_shape(16,1024)), (tuple{2_ct,8_ct}), 4 );
V256_MT_SQRT_CASE(v256_mt.sqrt.16_1024.fp32.2x4.8,  (make_shape(16,1024)), (tuple{2_ct,8_ct}), 8 );
V256_MT_SQRT_CASE(v256_mt.sqrt.16_1024.fp32.2x4.16,  (make_shape(16,1024)), (tuple{2_ct,8_ct}), 16 );

V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.16_1024.fp32.2x4.2,  (make_shape(16,1024)), (tuple{2_ct,8_ct}), 2 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.16_1024.fp32.2x4.4,  (make_shape(16,1024)), (tuple{2_ct,8_ct}), 4 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.16_1024.fp32.2x4.8,  (make_shape(16,1024)), (tuple{2_ct,8_ct}), 8 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.16_1024.fp32.2x4.16,  (make_shape(16,1024)), (tuple{2_ct,8_ct}), 16 );

V256_MT_SQRT_CASE(v256_mt.sqrt.64_1024.fp32.2x4.2,  (make_shape(64,1024)), (tuple{2_ct,8_ct}), 2 );
V256_MT_SQRT_CASE(v256_mt.sqrt.64_1024.fp32.2x4.4,  (make_shape(64,1024)), (tuple{2_ct,8_ct}), 4 );
V256_MT_SQRT_CASE(v256_mt.sqrt.64_1024.fp32.2x4.8,  (make_shape(64,1024)), (tuple{2_ct,8_ct}), 8 );
V256_MT_SQRT_CASE(v256_mt.sqrt.64_1024.fp32.2x4.16,  (make_shape(64,1024)), (tuple{2_ct,8_ct}), 16 );

V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.64_1024.fp32.2x4.2,  (make_shape(64,1024)), (tuple{2_ct,8_ct}), 2 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.64_1024.fp32.2x4.4,  (make_shape(64,1024)), (tuple{2_ct,8_ct}), 4 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.64_1024.fp32.2x4.8,  (make_shape(64,1024)), (tuple{2_ct,8_ct}), 8 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.64_1024.fp32.2x4.16,  (make_shape(64,1024)), (tuple{2_ct,8_ct}), 16 );

V256_MT_SQRT_CASE(v256_mt.sqrt.1024_1024.fp32.2x4.2,  (make_shape(1024,1024)), (tuple{2_ct,8_ct}), 2 );
V256_MT_SQRT_CASE(v256_mt.sqrt.1024_1024.fp32.2x4.4,  (make_shape(1024,1024)), (tuple{2_ct,8_ct}), 4 );
V256_MT_SQRT_CASE(v256_mt.sqrt.1024_1024.fp32.2x4.8,  (make_shape(1024,1024)), (tuple{2_ct,8_ct}), 8 );
V256_MT_SQRT_CASE(v256_mt.sqrt.1024_1024.fp32.2x4.16,  (make_shape(1024,1024)), (tuple{2_ct,8_ct}), 16 );

V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.1024_1024.fp32.2x4.2,  (make_shape(1024,1024)), (tuple{2_ct,8_ct}), 2 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.1024_1024.fp32.2x4.4,  (make_shape(1024,1024)), (tuple{2_ct,8_ct}), 4 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.1024_1024.fp32.2x4.8,  (make_shape(1024,1024)), (tuple{2_ct,8_ct}), 8 );
V256_MT_SQRT_UTL_CASE(v256_mt.sqrt_utl.1024_1024.fp32.2x4.16,  (make_shape(1024,1024)), (tuple{2_ct,8_ct}), 16 );
